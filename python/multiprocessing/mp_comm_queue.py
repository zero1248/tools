import multiprocessing

def producer(q):
    for i in range(5):
        q.put(i)
        print(f"生产: {i}")

def consumer(q):
    while True:
        item = q.get()
        if item is None:  # 终止信号
            break
        print(f"消费: {item}")

if __name__ == '__main__':
    q = multiprocessing.Queue()
    
    p1 = multiprocessing.Process(target=producer, args=(q,))
    p2 = multiprocessing.Process(target=consumer, args=(q,))
    
    p1.start()
    p2.start()
    
    p1.join()
    q.put(None)  # 发送终止信号
    p2.join()

