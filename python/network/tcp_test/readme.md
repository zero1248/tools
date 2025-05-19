tcp socket 测试

- client_test.py
- server_test.py

client 发给 server 的信息，加上时间戳再返回。

server 必须先运行。如果在同一台 linux 设备上运行，可以让 server 后台运行：

./server_test.py &

如果需要关闭，就 ps 查看进程号，然后 kill 掉。