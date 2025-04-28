import multiprocessing
import time

def worker(sem, i):
    with sem:
        print(f"进程 {i} 获取信号量")
        time.sleep(2)

if __name__ == '__main__':
    sem = multiprocessing.Semaphore(2)  # 允许同时2个进程访问
    
    processes = [multiprocessing.Process(target=worker, args=(sem, i)) 
                for i in range(5)]
    
    for p in processes:
        p.start()
    
    for p in processes:
        p.join()

