由于系统任务是在仿真时使用，所以这里基本都是只有仿真代码。

部分测试需要一些变化的数据，因此在 src 目录下建了一个简单的加法模块方便测试。

---


tb_fread.v

fread 以大端模式读出数据。读出的数据用 fdisplay 显示时与原始文本顺序一致。

tb_monitor.v / tb_multi_block_monitor.v / tb_multi_monitor.v

测试多个 $monitor 语句的情况，只能后一个起作用。

tb_monitor_topmodule.v

测试多个子模块中各自调用 $monitor 的情况。

$monitor 在仿真全局中只能有一个生效，后执行的会覆盖前一个。因此结果中只能看到最后定义的模块中的 monitor 的输出。

tb_readmem.v

测试 $readmemh。

$readmemh 只允许读取十六进制字符：0~9、a~f、A~F，其他都算非法字符。

每次读一行，读到换行或者空格结束。遇到非法字符也结束。

tb_string_options.v

$swrite 每次都会覆盖。

$sformat 可以格式化生成字符串，但不能拼接。

tb_test_plusargs.v

需要在 vvp 调用时加参数：
```
vvp sim/tb_test_plusargs.out +TESTNAME=case1 +HELLO
```

可以修改 makefile：
```
PLUSARGS ?=

sim:
	mkdir -p $(SIM_DIR) $(WAVE_DIR)
	$(IVERILOG) $(SV_FLAG) -s $(TOP) $(IVERILOG_FLAGS) -o $(OUT) -I$(COMMON_DIR) $(RTL) $(TOP_FILE)
	$(VVP) $(OUT) $(PLUSARGS)
```
这样就可以用 make 传参
```
make sim TOP=tb_test_plusargs PLUSARGS="+TESTNAME=case1 +HELLO"
```



