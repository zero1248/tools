#include "get_ip_host.h"
#include <iostream>
#include <unistd.h>     // hostname
#include <ifaddrs.h>    // ip addr
#include <arpa/inet.h>  // ip addr
#include <string> 
#include <vector>



#define MAX_HOST_NAME 256

using std::cout;
using std::endl;



extern void get_hostname(std::string & hostname) {

    char host[MAX_HOST_NAME];
    gethostname(host, MAX_HOST_NAME - 1); //Get host name
    hostname = std::string(host);
}



// todo: 改成传参使用的，保存在 vector 中或者结构体/类中
// todo: 最好写成按网卡存储信息
extern void get_ip() {

    struct ifaddrs* ifAddrStruct = NULL;
    void * tmpAddrPtr = NULL;

    getifaddrs(&ifAddrStruct);

    while (ifAddrStruct != NULL) {
        if (ifAddrStruct -> ifa_addr -> sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct -> ifa_addr) -> sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            cout << ifAddrStruct->ifa_name << " IPv4 Addr: " << addressBuffer << endl;
        } 
        else if (ifAddrStruct -> ifa_addr -> sa_family == AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct -> ifa_addr) -> sin_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            cout << ifAddrStruct->ifa_name << " IPv6 Addr: " << addressBuffer << endl;
        } 
    
        ifAddrStruct = ifAddrStruct -> ifa_next;
    }
}


int main(int argc,char *argv[]) {

    std::string hostname;
    get_hostname(hostname);
    cout << "hostname: " << hostname << endl;

    get_ip();
	return 0;
}


