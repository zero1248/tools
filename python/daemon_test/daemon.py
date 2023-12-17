import sys, os, time, atexit
import signal


class Daemon:
    """
    A generic daemon class.

    Usage: subclass the Daemon class and override the run() method
    """
    # def __init__(self, pidfile, stdin='/dev/null', stdout='/dev/null', stderr='/dev/null', args=None):
    def __init__(self, pidfile, stdin='/dev/null', stdout='/home/isaac/tools/python/daemon_test/stdout.log', stderr='/home/isaac/tools/python/daemon_test/stderr.log', args=None):
        self.stdin = stdin
        self.stdout = stdout
        self.stderr = stderr
        self.pidfile = pidfile
        self.args = args

    def daemonize(self):
        """
        do the UNIX double-fork magic, see Stevens' "Advanced
        Programming in the UNIX Environment" for details (ISBN 0201563177)
        http://www.erlenstar.demon.co.uk/unix/faq_2.html#SEC16
        """
        # do first fork
        try:
            # 从父进程fork一个子进程出来
            pid = os.fork()
            # 子进程的pid一定为0，父进程大于0
            if pid > 0:
                # exit first parent
                # 退出父进程
                sys.exit(0)
        except OSError as e:
            sys.stderr.write("fork #1 failed: %d (%s)\n" % (e.errno, e.strerror))
            sys.exit(1)

        # decouple from parent environment
        # 子进程默认继承父进程的工作目录，最好是变更到根目录，否则回影响文件系统的卸载
        os.chdir("/")
        # 让子进程成为新的会话组长和进程组长
        os.setsid()
        # 子进程默认继承父进程的umask（文件权限掩码），重设为0（完全控制），以免影响程序读写文件
        os.umask(0)

        # do second fork
        try:
            pid = os.fork()
            if pid > 0:
                # exit from second parent
                sys.exit(0)
        except OSError as e:
            sys.stderr.write("fork #2 failed: %d (%s)\n" % (e.errno, e.strerror))
            sys.exit(1)

        # 此时，孙子进程已经是守护进程了，接下来重定向标准输入、输出、错误的描述符
        # (是重定向而不是关闭, 这样可以避免程序在 print 的时候出错)

        # 刷新缓冲区
        sys.stdout.flush()
        sys.stderr.flush()

        si = open(self.stdin, 'r')
        so = open(self.stdout, 'a+')
        se = open(self.stderr, 'a+')
 
        os.dup2(si.fileno(), sys.stdin.fileno())         
        os.dup2(so.fileno(), sys.stdout.fileno())
        os.dup2(se.fileno(), sys.stderr.fileno())

        signal.signal(signal.SIGTERM, self._handle_sigterm)

        # 写入pid文件
        if self.pidfile:
            with open(self.pidfile, 'w+') as f:
                f.write(str(os.getpid()))
        
        # 注册退出函数，进程异常退出时移除pid文件
        atexit.register(self._atexit_cleanup)

    def _handle_sigterm(self, signo, frame):
        sys.exit(0)

    def _atexit_cleanup(self):
        os.remove(self.pidfile)

    def start(self):
        """
        Start the daemon
        """
        # Check for a pidfile to see if the daemon already runs
        try:
            with open(self.pidfile,'r') as pf:
                pid = int(pf.read().strip())
        except IOError:
            pid = None

        if pid:
            message = "pidfile %s already exist. Daemon already running?\n"
            sys.stderr.write(message.format(self.pidfile))
            sys.exit(1)

        # Start the daemon
        self.daemonize()
        self.run()

    def stop(self):
        """
        Stop the daemon
        """
        # Get the pid from the pidfile
        try:
            with open(self.pidfile,'r') as pf:
                pid = int(pf.read().strip())
        except IOError:
            pid = None

        if not pid:
            message = "pidfile %s does not exist. Daemon not running?\n"
            sys.stderr.write(message % self.pidfile)
            return # not an error in a restart

        # Try killing the daemon process
        try:
            while 1:
                os.kill(pid, signal.SIGTERM)
                time.sleep(0.1)
        except OSError as err:
            err = str(err)
            if err.find("No such process") > 0:
                if os.path.exists(self.pidfile):
                    os.remove(self.pidfile)
            else:
                print(str(err))
                sys.exit(1)

    def restart(self):
        """
        Restart the daemon
        """
        self.stop()
        self.start()

    def run(self):
        """
        You should override this method when you subclass Daemon. It will be called after the process has been
        daemonized by start() or restart().
        """


if __name__ == "__main__":
    print("main function")