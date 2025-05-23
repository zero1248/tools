Python 默认的 threading 模块使用 线程 进行并发，但由于 GIL（全局解释器锁）的存在，多线程无法真正实现 CPU 级别的并行计算，适用于 I/O 密集型任务（如文件读写、网络请求）。

multiprocessing 创建多个进程，每个进程有独立的 Python 解释器，能够真正实现并行计算，适用于 CPU 密集型任务（如数学计算、数据处理、图像渲染）。

                        
---

由于 python 的 GIL（全局解释器锁）的限制，在任何时间点都只能有一个线程处于执行状态，使用 threading 模块实现的多线程，并不能充分利用 CPU 中的多个核。

使用 multiprocessing 模块，可以通过多进程的方式，利用 CPU 的多个核。

但是当进程数超过核数之后，只能分时间片切换进程，由于进程的切换开销比线程切换大，因此不适合开太多进程。