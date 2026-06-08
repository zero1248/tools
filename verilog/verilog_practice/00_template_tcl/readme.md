通过 tcl 文件，以非工程模式调用 vivado 进行仿真。

目前只能将波形文件保存成 .vcd 文件，用 gtkwave 查看。

运行仿真：
```shell
vivado -mode batch -source run_sim.tcl -tclargs tb_sequence_detect xcku5p-ffvb676-2-e 1000ns
```

查看波形：
```shell
gtkwave wave/tb_sequence_detect.vcd
```


