/*
 * @Author: gaoy
 * @Date: 2025-02-28 17:48:13
 * @LastEditors: gaoy
 * @LastEditTime: 2025-03-02 21:48:48
 * @Description: file content
 */
/************************************
/* FileName : socket_send.cpp
/* CreatTime: 2025-02-28 17:47:41
/* Create by: Isaac
/************************************/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <iostream>


const int local_port = 4097;        // 监听端口号

void print_usage(const char* prog_name) {
    std::cerr << "Usage: " << prog_name << std::endl
              << " <IP address> <Port number> <Message>\n"
              << "E.g.: " << prog_name  << std::endl
              << " 127.0.0.1 12345 \"123abc123abc\"\n";
}


int main(int argc, char* argv[]) {

    if (argc != 4) {
        print_usage(argv[0]);
        return 1;
    }

    const char* dest_ip = argv[1];
    const char* msg = argv[3];

    // check port number
    char* end;
    long dest_port = strtol(argv[2], &end, 10);
    if (*end != '\0' || dest_port < 1 || dest_port > 65535) {
        std::cerr << "Error: invalid port number (1-65535)\n";
        return 2;
    }

    // create UDP socket 
    int sockfd = socket(AF_INET,     // IPv4
                       SOCK_DGRAM,   // UDP
                       0);           // auto select protocal
    if (sockfd < 0) {
        std::cerr << "Create socket failed\n";
        return 3;
    }

    // // bind local port
    // // if not, OS will random assign a port
    // struct sockaddr_in local_addr;
    // memset(&local_addr, 0, sizeof(local_addr));
    // // local_addr.sin_family = AF_INET;
    // // local_addr.sin_port = htons(local_port);    // set local port
    // // local_addr.sin_addr.s_addr = INADDR_ANY;    // bind to any IP
    // if (bind(sockfd, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0) {
    //     std::cerr << "Bind local addr failed: " << strerror(errno) << "\n";
    //     close(sockfd);
    //     return 3;
    // }
   
    // config dest addr
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(dest_port);
    inet_pton(AF_INET, dest_ip, &dest_addr.sin_addr);

    // send msg
    ssize_t sent = sendto(sockfd, msg, strlen(msg), 0,
                         (struct sockaddr*)&dest_addr, sizeof(dest_addr));
    if (sent < 0) {
        std::cerr << "Send failed: " << strerror(errno) << "\n";
    } 
    else {
        std::cout << " Send " << sent << " bytes\n" << std::endl;
    }
    
    close(sockfd);   // release socket
    return 0;
}