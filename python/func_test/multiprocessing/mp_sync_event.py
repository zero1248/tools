import multiprocessing

def wait_for_event(e):
    print("等待事件触发...")
    e.wait()
    print("事件已触发")

if __name__ == '__main__':
    event = multiprocessing.Event()
    
    p = multiprocessing.Process(target=wait_for_event, args=(event,))
    p.start()
    
    input("按回车触发事件\n")
    event.set()
    
    p.join()

