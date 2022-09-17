1、echo_info

显示信息



2、xiu

用于把给定的第一个参数的文件拷贝到 ~/scripts 目录下。

目前由用户保证参数的正确。



3、inpath

判断给定的第一个参数的文件是否在 PATH 路径列表中。



4、gohome

cd 到 某个特定的目录，这里因为用 windows 的 wsl 刚登录进来的目录不是 home，所以需要这样一个脚本。

- mastercode.sh 用于给 gohome 起别名



5、touchc

创建 .c 和 .h 文件。



6、touchcpp

创建 .cpp 和 .h 文件。



7、cpmf

用于复制 ~/scripts 中已有 makefile 到当前目录下。