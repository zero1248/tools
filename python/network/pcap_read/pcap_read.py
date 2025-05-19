"""
用 scapy 包读取 pcap 文件中的数据
只用于未接入真实环境时的前期测试
真实环境中，数据直接来源于 UDP 包
"""


from scapy.all import rdpcap
import numpy as np

data_array = []

# 读取 pcap 文件
packets = rdpcap("traffic.pcap")




# 遍历每个数据包
for pkt in packets:
    # 提取基本信息
    if pkt.haslayer("IP"):
        src_ip = pkt["IP"].src
        dst_ip = pkt["IP"].dst
         # 检查是否包含 TCP/UDP 层
        if pkt.haslayer("TCP"):
            protocol_name = "TCP"
        elif pkt.haslayer("UDP"):
            protocol_name = "UDP"
        else:
            # 其他协议（如 ICMP），显示协议号
            protocol_num = pkt["IP"].proto   # 6=TCP, 17=UDP, 58=IPv6-ICMP
            protocol_name = f"Other ({protocol_num})"
        print(f"IP Packet: {src_ip} -> {dst_ip} (Proto {protocol_name})")
        
    # 提取 TCP/UDP 层数据
    # if pkt.haslayer("TCP"):
    #     tcp_payload = bytes(pkt["TCP"].payload)  # 应用层数据（如HTTP）
    #     print(f"TCP Payload (len={len(tcp_payload)}): {tcp_payload[:16]}...")
    if pkt.haslayer("UDP"):
        udp_payload = bytes(pkt["UDP"].payload)
        print(f"UDP Payload (len={len(udp_payload)}): {udp_payload[:16]}...")
    data_array.append(bytearray(udp_payload))
    # break # 只处理一个包

# 以上将 5 个包的数据读到了 datarray list 中

# idx = 488
idx = 5
i = np.zeros((1024, idx))
q = np.zeros((1024, idx))

for k in range(idx):
    spec_data = np.frombuffer(data_array[k], dtype = '<i')
    i[:, k] = spec_data[0::2][0:1024]   #! 从 0 开始，步长为 2，取 1024 个元素
    q[:, k] = spec_data[1::2][0:1024]   #! 从 1 开始，步长为 2，取 1024 个元素



print(i)

# # 保存为 CSV（逗号分隔）
# np.savetxt("int32_matrix.csv", matrix, fmt="%d", delimiter=",")
# 保存 i 为空格分隔的文本
np.savetxt("i_int32.txt", i, fmt="%d")

mix_data = np.zeros((1024, idx))
for k in range(idx):
    spec_data = np.frombuffer(data_array[k], dtype = '<i8')
    i[:, k] = spec_data[0:1024]   #! 从 0 开始，步长为 2，取 1024 个元素

np.savetxt("qi_int64.txt", i, fmt="%ld")

