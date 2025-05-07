"""
基础进程创建
"""

import multiprocessing
import os

def worker():
    print(f"进程ID: {multiprocessing.current_process().pid}")
    print(f"进程名称: {multiprocessing.current_process().name}")
    print(f"子进程ID: {os.getpid()}, 父进程ID: {os.getppid()}")


if __name__ == '__main__':
    # 创建进程对象
    p = multiprocessing.Process(target=worker, name="自定义进程")
    
    # 启动进程
    p.start()
    
    # 等待进程结束
    p.join()
    
    print("主进程结束")