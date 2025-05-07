import multiprocessing

def increment(shared_counter, lock):
    with lock:
        shared_counter.value += 1

if __name__ == '__main__':
    counter = multiprocessing.Value('i', 0)
    lock = multiprocessing.Lock()
    
    processes = []
    for _ in range(100):
        p = multiprocessing.Process(target=increment, args=(counter, lock))
        p.start()
        processes.append(p)
    
    for p in processes:
        p.join()
    
    print("最终计数:", counter.value)  # 正确输出 100
