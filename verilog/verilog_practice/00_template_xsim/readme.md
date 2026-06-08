调用 vivado 的 xvlog、xelab 和 xsim 对 verilog 代码进行仿真。

需要生成 .vcd 文件的地方，在调用 xsim 时已经通过 --tclbatch 指令用脚本指定了保存到 .vcd，不需要再像使用 iverilog 时在 testbench 里添加：
```Verilog HDL
    initial begin
        $dumpfile("wave/tb_sequence_detect.vcd");
        $dumpvars(0, tb_sequence_detect);
    end
```

#### 仿真并保存波形

1、xsim 仿真，并生成 .wdb 和 .vcd 文件：
```shell
make sim TB=tb_sequence_detect
```


2、xsim 仿真，并只生成 vcd 文件：
```shell
make vcd TB=tb_sequence_detect
```


3、xsim 仿真，并只生成 wdb 文件：
```shell
make wdb TB=tb_sequence_detect
```


---
#### 查看波形

1、 vivado 打开 .wdb 文件：
```shell
make wave_wdb TB=tb_sequence_detect
```


2、gtkwave 打开 .vcd 文件：
```shell
make wave_vcd TB=tb_sequence_detect
```


---

清理：
```shell
make clean
```

