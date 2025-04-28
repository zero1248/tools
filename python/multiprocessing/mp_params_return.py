"""
进程函数带参数和返回值
返回值也通过参数来实现
"""

import multiprocessing

def square(number, result):
    result.value = number ** 2  # 通过共享内存返回结果

if __name__ == '__main__':
    number = 5
    # 共享内存只支持两种数据结构 Value 和 Array
    result = multiprocessing.Value('d', 0.0)  # 'd' 表示双精度浮点
    
    p = multiprocessing.Process(target=square, args=(number, result))
    p.start()
    p.join()
    
    print(f"{number} 的平方是 {result.value}")

