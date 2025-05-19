1、socket

TCP socket 收发测试。


2、UDPReceiver

UDPReceiver 是把 socket_recv 封装成了一个 UDP 接收的类，收到的数据存到buffer而不是文件。

test_UDPReceiver.cpp 用于测试 UDPReceiver,接收数据并显示，也可以保存到文件（可选）。 
./test_UDPReceiver <port> [file_name]

