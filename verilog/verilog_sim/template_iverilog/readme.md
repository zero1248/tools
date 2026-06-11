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
make sim TB=tb_sequence_detect
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
