00_template_iverilog:

使用 iverilog + gtkwave 做 verilog 仿真，生成 vcd 文件。




00_template_tcl

使用 vivado 非工程模式做 verilog 仿真，生成 vcd 文件。

目前生成的 wdb 文件打开之后没有波形。



00_template_xsim:

使用 vivado 自带的  xvlog、xelab 和 xsim 对 verilog 代码进行仿真.

可以通过make 命令选择生成 vcd、wdb 或者两者皆有。



01_sequence_detect:

序列检测，检测 1011 序列，支持重叠检测。

使用了 Moore 型三段式状态机。