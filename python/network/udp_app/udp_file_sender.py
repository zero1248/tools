#!/usr/bin/env python

from socket

# 读取数据文件
def read_numbers_file(filename):
    result = []
    with open(filename, 'r') as f:
        for line in f:
            # 去除首尾空白并分割数字
            numbers = line.strip().split()
            # 转换为整数并存入列表
            result.append([int(num) for num in numbers])
    return result

data = read_numbers_file('qi_int64.txt')             # 1024 * 5
# 转置
transposed_data = [list(row) for row in zip(*data)]  # 5 * 1024



def send_list_udp(data_list, host='127.0.0.1', port=4096):
    ADDR = (HOST, PORT)
    udpCliSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udpCliSock.sendto(transposed_data[0].encode("utf-8"), ADDR)
    udpCliSock.close()



HOST = "127.0.0.1"  # or "localhost"
PORT = 4096




