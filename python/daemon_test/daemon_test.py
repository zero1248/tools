import os, sys, time
from daemon import Daemon

 
class TestDaemon(Daemon):
    
    def __init__(self, dir):
        super().__init__(dir + '/testDaemon.pid')
        self.dir = dir
    
    '''
    测试类
    测试守护进程是否可以正常运行
    '''
    def run(self):
        while True:
            # sys.stdout.write(os.getcwd() + ':%s:hello world\n' % (time.ctime(),))  # 当前目录是 /
            # sys.stdout.flush()
            # time.sleep(1)
            with open(self.dir + '/log.txt', 'a+') as f:
                f.write(time.ctime() + '\n')
            time.sleep(1)


if __name__ == '__main__':
    '''
    在终端中输入 python testDaemon.py start/stop/restart 来控制守护进程。
    '''
    cur_dir = os.getcwd()
    daemon = TestDaemon(cur_dir) # 实例化对象
    
    if len(sys.argv) == 2:
        if 'start' == sys.argv[1]:
            print("Starting daemon...")
            daemon.start()
        elif 'stop' == sys.argv[1]:
            print("Stopping daemon...")
            daemon.stop()
        elif 'restart' == sys.argv[1]:
            print("Restarting daemon...")
            daemon.restart()
        else:
            print("Unknown command")
            sys.exit(2)
        sys.exit(0)
    else:
        print("usage: {0} start|stop|restart".format(sys.argv[0]))
        sys.exit(2)

