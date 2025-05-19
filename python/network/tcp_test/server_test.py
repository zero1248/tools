#!/usr/bin/env python

from socket import *
from time import ctime

HOST = ""
PORT = 4096
BUFSIZ = 4096
ADDR = (HOST, PORT)


tcpSerSock = socket(AF_INET, SOCK_STREAM)
tcpSerSock.bind(ADDR)
tcpSerSock.listen(5)

while True:
	print ("waiting for connection...")
	tcpCliSock, addr = tcpSerSock.accept()
	print ("...connected from:", addr)

	while True:
		# data = tcpCliSock.recv(BUFSIZi) # client prints bytes data
		data = tcpCliSock.recv(BUFSIZ).decode("utf-8") # client prints str data
		if not data:
			break
		tcpCliSock.send(("[%s] %s"% (
				ctime(), data)).encode("utf-8") )
		
	tcpCliSock.close()
tcpSerSock.close()







