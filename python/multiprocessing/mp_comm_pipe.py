import multiprocessing


def sender(conn):
    conn.send("Hello from sender")
    conn.close()

def receiver(conn):
    msg = conn.recv()
    print("收到消息:", msg)
    conn.close()

if __name__ == '__main__':
    parent_conn, child_conn = multiprocessing.Pipe()
    
    p = multiprocessing.Process(target=sender, args=(child_conn,))
    p.start()
    
    receiver(parent_conn)
    p.join()
