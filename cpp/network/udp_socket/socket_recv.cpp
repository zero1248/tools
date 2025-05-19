/*
 * @Author: gaoy
 * @Date: 2025-02-28 17:27:40
 * @LastEditors: gaoy
 * @LastEditTime: 2025-03-02 21:30:25
 * @Description: file content
 */
/************************************
/* FileName : socket_test.cpp
/* CreatTime: 2025-02-28 17:26:25
/* Create by: Isaac
/************************************/

#include <iostream>
#include "socket_test.h"
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;


const int BUFFER_SIZE = 4096;  // The maximum size of a UDP packet is 65,535 bytes. 
const int listen_port = 4096;        // 监听端口号
const char* OUTPUT_FILE = "udp_data.bin"; // 输出文件名

int main(int argc, char* argv[]) {

    struct sockaddr_in listen_addr, cliaddr;
    socklen_t cliaddr_len = sizeof(cliaddr);
    char buffer[BUFFER_SIZE];

    // create UDP socket
    int sockfd = socket(AF_INET,    // IPv4
                    SOCK_DGRAM,     // UDP
                    0);             // auto select protocal
    if (sockfd < 0) {
        std::cerr << "Create socket failed\n";
        return 1;
    }

    // bind listen addr and port
    memset(&listen_addr, 0, sizeof(listen_addr));
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = INADDR_ANY;
    listen_addr.sin_port = htons(listen_port);

    if (bind(sockfd, (const struct sockaddr*)&listen_addr, sizeof(listen_addr)) < 0) {
        perror("bind listen addr failed");
        close(sockfd);
        return 2;
    }

    // open output file（append binary mode）
    std::ofstream outfile(OUTPUT_FILE, std::ios::binary | std::ios::app);
    if (!outfile.is_open()) {
        std::cerr << "Cannot open output file: " << OUTPUT_FILE << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Listening UDP port " << listen_port << ", data will be saved to " << OUTPUT_FILE << std::endl;

    while (true) {
        // receive data
        ssize_t recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                   (struct sockaddr*)&cliaddr, &cliaddr_len);
        
        if (recv_len < 0) {
            perror("Receive failed");
            continue;
        }

        // save data to file
        outfile.write(buffer, recv_len);
        if (!outfile) {
            std::cerr << "File write failed!" << std::endl;
            break;
        }

        // flush buffer to ensure data persistence
        outfile.flush(); 

        // show the received data
        std::cout << "Receive " << recv_len << " bytes from: " 
                  << inet_ntoa(cliaddr.sin_addr) << ":" 
                  << ntohs(cliaddr.sin_port) << std::endl;
    }

    // release resource
    outfile.close();
    close(sockfd);
    return 0;
}

