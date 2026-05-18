1、tb_axi_lite.v

用于仿真 axi-lite 总线的 testbench。

2、tb_gzip_ip

仿真从 Vitis Library 导出的 gzip IP 核的 testbench。
输入数据由文件读入，输出数据也写入文件。

仿真中的文件当前目录是 <>.sim\sim_1\behav\xsim\，所以如果输出文件设为 "."，就会被输出到这里，输入文件最好不要放在这里，因为在 Vivado 中复位仿真时，会把这个文件夹全部清除，可以放在上一级目录中，即 <>.sim\sim_1\behav\ 这里。

