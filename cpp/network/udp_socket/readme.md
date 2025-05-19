socket_send 和 socket_recv 配合使用。编译出来两个可执行文件：
socket_send - 发送 socket
socket_recv - 接收 socket 并存到文件


发送：
./socket_send 172.29.10.106 4096 123abc123abc 

接收：
./socket_recv
没有设置参数，buffer 大小、监听端口和文件名均设为默认值。



