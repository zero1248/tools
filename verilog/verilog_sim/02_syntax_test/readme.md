tb_unblocking0

单条非阻塞赋值

1）阻塞赋值相当于 RHS 计算的输出和 LHS 赋值的输入直接通过导线连了起来

2）非阻塞赋值相当于 RHS 计算的输出和 LHS 赋值的输入通过一个 触发器进行了隔离，因此就有新值和旧值之分，不会出现阻塞赋值中出现的竞争问题。

tb_unblocking1

某语句的 RHS 含块内其他语句的 LHS

会不会产生延迟，取决于路径中产生了几级触发器。如果某个变量所在的数据路径中只有一级触发器，则无论数据早于时钟上升沿变化，
还是数据与时钟上升沿同步变化，都不会产生延迟，数据会立即更新（只是后者的 RHS 中的计算不能太复杂，否则可能建立/保持时间不满足）。
而如果某变量所在的数据路径中有两级触发器，则会产生一个周期的延迟，因为触发器每一拍只能传递一级。

tb_unblocking2

连续级联赋值

由于 out1 所在的链路中，存在 4 级触发器，因此 out1 的输出相比 a、b、c 的输入延迟了 3 个周期。

--

tb_unblocking_lock

验证时序逻辑块必须用非阻塞赋值，否则在交换取值时会锁死。

--

tb_unblocking_ifelse0

简单 if-else，条件为外部输入 wire。

简单的 if-else 语句不会造成输出延迟。

tb_unblocking_ifelse1

条件中含 reg 变量。

MUX 控制端多了一级触发器，输出产生一个周期的时延。

tb_unblocking_ifelse2

条件表达式中含 reg 变量。

MUX 之后产生触发器，输出产生一个周期的时延。

--

tb_generate_for

测试 generate-for 语句。

dut 是用 adder1b 模块通过 generate-for 生成了一个 4b 位宽的 adder4b 模块。

---

tb_dynamic_slice

测试动态切片语法。

---

tb_delay

测试在 testbench 中延时用 # 和 @(posedge clk) 的区别。

使用一个简单的半加器 adder4b_half 作为测试模块。

