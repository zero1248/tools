1、gen_data

用于生成数据的工具。


2、print_ascii

输出 ascii 码表。


3、print_color

打印 printf 可使用的各种颜色，方便查询。


4、print_cpu

输出 CPU 信息，需要保留工程目录中的 obj 和 bin 空目录，否则 make 会报错。

todo：修改 makefile 执行 mkdir -f 创建 obj 和 bin 目录。


5、print_format

打印 printf 的格式化参数，方便查询。


6、get_dir_files

获取指定目录下（不含子目录）的文件名或目录名。

可以获取所有类型，也可以指定文件类型。


7、rw_json

读取 JSON 文件。


8、get_ip_host

获取本机的 IP 和 Hostname。


9、read_config

读取 config 文件（可以含空白符），内容类似于：

```JSON
para1 = abc
para2 = 123
```




