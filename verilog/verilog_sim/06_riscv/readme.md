
1、rv32_alu.v

ALU 模块，负责算术和逻辑运算（整数）。

2、rv32_immgen.v

立即数拼接，从指令中将立即数提取出来，扩展为32位。


3、rv32_regfile.v

寄存器组读写，共 32 个寄存器。

4、rv32_decoder.v

译码器实现。

不只按 7-bit opcode 译码。`funct3/funct7` 的保留组合也必须标为非法，例如当前阶段
的 `MUL` 编码不能误当成 `ADD`。译码输出分为：

- 数据通路控制：ALU 输入、ALU 操作、写回选择；
- 访存控制：load/store；
- 控制流：branch/jump/JALR；
- 立即数类型；
- 合法性。


5、rv32_core_singlecycle.v

后续流水线的“硬件参考模型”。它完成：

-  `PC -> imem -> decode -> regfile -> ALU -> dmem -> writeback`；
-  所有 RV32I 整数 ALU 指令；
-  六种条件分支以及 JAL/JALR；
-  LB/LBU/LH/LHU/LW 与 SB/SH/SW；
-  指令地址和数据地址对齐检查；
-  非法指令锁存 `trap` 和 `trap_pc`。

关键检查：

- JALR 目标地址 bit 0 清零；
- RV32I 未加入 C 时，跳转目标必须 4 字节对齐；
- byte/halfword store 的 strobe 和 wdata 必须同时按地址低两位移动；
- signed load 在移动目标字节/半字后再符号扩展；
- 发生 fault 的同一周期不得写寄存器或存储器。

6、sw

简单的 CPU 代码。

需要安装 riscv64-unknown-elf-gcc 这个工具：
```
sudo apt update
sudo apt install gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf
riscv64-unknown-elf-gcc --version
```

sw 目录下有 makefile，直接 make 即可。

---


使用 iverilog + gtkwave 做 verilog 仿真，主要是语法练习和模块练习。

iverilog 默认只支持 verilog，不支持 SystemVerilog。

iverilog: 用于编译 verilog 和 vhdl 文件，进行语法检查，生成可执行文件

vvp：根据可执行文件，生成仿真波形文件

gtkwave：用于打开仿真波形文件，图形化显示波形

---
### 仿真命令

#### 执行仿真

```shell
# 使用 makefile 中的默认 testbench 文件（适合单个 tb 的情况）
make sim

# 指定 tb 目录下的 testbench 文件（适合多个 tb 的情况）
make sim TOP=tb_sequence_detect
```


#### 查看波形
```shell
# 查看 .vcd
make wave

# 将 .vcd 转成 .fst 再查看，适合仿真结果较大的情况
make fst
```


#### 其他
```shell
# 列出 tb 目录下的 testbench 文件
make list

#清理
make clean
```

---

### 仿真设置

#### 1、testbench 写法

在 testbench 的 initial 块的一开始，要写打开波形文件，和波形文件中放入的模块：
```
initial begin
    //! 这里的当前目录是 makefile 所在目录，所以不需要加 ../
    $dumpfile("wave/<tb_module_name>.vcd");
    $dumpvars(0, <tb_module_name>);
end
```
$dumpvars(0, tb_fsm) 的 第二个参数是要放入波形图的模块名称，第一个参数是要放入的层级：

0 —— 该模块及所有子模块（常用）；

1 —— 该模块本身；

2 —— 该模块 + 一层子模块。


#### 2、开启 SystemVerilog 支持

iverilog -g2012 -o sim/sim.out src/fsm.v tb/tb_fsm.v

iverilog 对 SystemVerilog 的支持有限，不适合长期练习。


#### 3、仿真规模较大

可以将 .vcd 转为 .fst 文件，执行 make fst，而非 make wave。


#### 4、iverilog 指定头文件目录

可以参考 makefile 中的写法：
```
COMMON_DIR = "../common"
$(IVERILOG) -v -o $(OUT) -I$(COMMON_DIR) $(RTL) $(TB_FILE) 
```

注意 -I$(COMMON_DIR) 要写在 $(RTL) $(TB_FILE)  之前
