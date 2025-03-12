### 0、cpp_test

用于测试，没什么用。



### 1、gen_data

用于测试数据相关的小工具。例如生成数据，比较两个文件。



### 2、sort

用 C++ 实现的排序算法简单示例。



### 3、print_ascii

打印 32-127 对应的 ASCII 码，方便查询。



### 4、print_color

打印 printf 可使用的各种颜色，方便查询。



### 5、print_cpu

打印 CPU 信息。



### 6、print_format

打印 printf 的格式化参数，方便查询。



### 7、hexcalc

简单的十六进制减法计算器。



### 8、read_config

读取 config 文件（可以含空白符），内容类似于：

para1 = abc

para2 = 123



### 9、rw_json

读取 JSON 文件。



### 10、get_dir_files

获取指定目录下（不含子目录）的文件名或目录名。

可以获取所有类型，也可以指定文件类型。



### 11、get_ip_host

获取本机的 IP 和 Hostname。



#### 12、game

命令行游戏。

目前颜色显示有问题。



#### 13、backup

用于备份基本不可能再用的代码。


#### 14、common

公共库，需要用 common_test 测试一下，修改 makefile。

#### 15、common_test

用于测试 common 库。

#### 16、socket

socket 相关的测试。从一个端口读出来帧，把数据写到文件里。
分为发送和接收两个程序。
