#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <mutex>
#include <thread>

class UDPReceiver {
public:
    UDPReceiver(int port, int buffer_size = 4096)
        : listen_port_(port), 
          BUFFER_SIZE_(buffer_size),
          running_(false) {
        // 创建socket
        sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd_ < 0) {
            throw std::runtime_error("Create socket failed: " + std::string(strerror(errno)));
        }

        // 配置监听地址
        memset(&listen_addr_, 0, sizeof(listen_addr_));
        listen_addr_.sin_family = AF_INET;
        listen_addr_.sin_addr.s_addr = INADDR_ANY;
        listen_addr_.sin_port = htons(listen_port_);

        // 绑定socket
        if (bind(sockfd_, (const struct sockaddr*)&listen_addr_, sizeof(listen_addr_)) < 0) {
            close(sockfd_);
            throw std::runtime_error("Bind failed: " + std::string(strerror(errno)));
        }

        std::cout << "Listening UDP port " << listen_port_ << std::endl;
    }

    ~UDPReceiver() {
        Stop();
        if (sockfd_ != -1) {
            close(sockfd_);
        }
    }

    void Start() {
        running_ = true;
        receiver_thread_ = std::thread(&UDPReceiver::ReceiveLoop, this);
    }

    void Stop() {
        running_ = false;
        if (receiver_thread_.joinable()) {
            receiver_thread_.join();
        }
    }

    std::vector<uint8_t> GetData() {
        std::lock_guard<std::mutex> lock(buffer_mutex_);
        return std::move(receive_buffer_);
    }

private:
    void ReceiveLoop() {
        char temp_buffer[BUFFER_SIZE_];
        struct sockaddr_in cliaddr;
        socklen_t cliaddr_len = sizeof(cliaddr);

        while (running_) {
            ssize_t recv_len = recvfrom(
                sockfd_, temp_buffer, BUFFER_SIZE_, 0,
                (struct sockaddr*)&cliaddr, &cliaddr_len
            );

            if (recv_len <= 0) {
                if (errno != EAGAIN && errno != EWOULDBLOCK) {
                    perror("Receive failed");
                }
                continue;
            }

            // 将数据存入缓冲区
            {
                std::lock_guard<std::mutex> lock(buffer_mutex_);
                receive_buffer_.insert(receive_buffer_.end(), 
                                     temp_buffer, 
                                     temp_buffer + recv_len);
            }

            // 打印接收信息
            std::cout << "Received " << recv_len << " bytes from "
                      << inet_ntoa(cliaddr.sin_addr) << ":"
                      << ntohs(cliaddr.sin_port) << std::endl;
        }
    }

    int listen_port_;
    const int BUFFER_SIZE_;
    
    int sockfd_ = -1;
    struct sockaddr_in listen_addr_;
    
    std::vector<uint8_t> receive_buffer_;
    std::mutex buffer_mutex_;
    bool running_;
    std::thread receiver_thread_;
};


