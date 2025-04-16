1、template.v

提供 testbench 的常用模板，包括时钟、复位等。

2、tb_axi_lite.v

用于仿真 axi-lite 总线的 testbench。

3、file_io.v

从文件读写测试数据和结果的示例，有时间再优化一下。

仿真中的文件当前目录是 <>.sim\sim_1\behav\xsim\，所以如果输出文件设为 "."，就会被输出到这里，输入文件最好不要放在这里，因为在 Vivado 中复位仿真时，会把这个文件夹全部清除，可以放在上一级目录中，即 <>.sim\sim_1\behav\ 这里。

todo:
function 和 task、系统任务。