import multiprocessing
import time

def daemon_task():
    while True:
        print("守护进程运行中...")
        time.sleep(1)

if __name__ == '__main__':
    p = multiprocessing.Process(target=daemon_task)
    p.daemon = True  # 设置为守护进程
    p.start()
    
    time.sleep(3)  # 主进程结束后守护进程会自动终止

