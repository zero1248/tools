"""
当需要 大量进程 时，直接创建多个 Process 可能导致 资源消耗过大。Pool 允许我们 控制进程的数量，避免创建过多进程。
"""

import multiprocessing
import time

def task(n):
    print(f"处理任务 {n}")
    time.sleep(1)
    return n * n

if __name__ == '__main__':
    with multiprocessing.Pool(processes=4) as pool:
        # 方法1: map
        results = pool.map(task, range(10))
        print(results)
        
        # 方法2: apply_async
        async_results = [pool.apply_async(task, (x,)) for x in range(5)]
        print([res.get() for res in async_results])