#### 模板

template_iverilog:

使用 iverilog + gtkwave 做 verilog 仿真，生成 vcd 文件。

template_tcl:

使用 vivado 非工程模式做 verilog 仿真，生成 vcd 文件。

目前生成的 wdb 文件打开之后没有波形。

template_xsim:

使用 vivado 自带的  xvlog、xelab 和 xsim 对 verilog 代码进行仿真.

可以通过make 命令选择生成 vcd、wdb 或者两者皆有。

---

#### 01_sequence_detect:

序列检测，检测 1011 序列，支持重叠检测。

使用了 Moore 型三段式状态机。

---

#### 02_assignment_statement:

用于测试赋值语句。

system_task 用于测试系统任务与函数。

generate_test 用于测试各种 generate 语句。

syntax_test 用于语法测试。

axi_beat 用于测试 AXI 握手打拍。

---

#### 03_axi_test

用于测试 axi 协议。

---

#### 04_system_task

用于测试 verilog 内置 system task。

---

#### 05_fifo

测试异步 fifo、跨时钟域等问题。


#### 06_riscv

riscv CPU




