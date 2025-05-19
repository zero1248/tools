import socket
import json
import pickle

def send_list_udp(data_list, host='127.0.0.1', port=4096, serializer='json'):
    """
    通过UDP发送列表数据
    参数：
    - data_list: 要发送的列表
    - host: 目标主机地址
    - port: 目标端口
    - serializer: 序列化方式（json/pickle）
    """
    try:
        # 创建UDP socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        
        # 序列化数据
        if serializer == 'json':
            serialized = json.dumps(data_list).encode('utf-8')
        elif serializer == 'pickle':
            serialized = pickle.dumps(data_list)
        else:
            raise ValueError("不支持的序列化方式")
        
        # 发送数据
        sock.sendto(serialized, (host, port))
        print(f"已发送 {len(serialized)} 字节数据")
        
    except Exception as e:
        print(f"发送错误: {str(e)}")
    finally:
        sock.close()

# 示例使用
if __name__ == '__main__':
    sample_list = [1, 2, 3, "测试数据", {"key": "value"}, 3.14]
    send_list_udp(sample_list, '127.0.0.1', 4096, 'json')          # 使用 JSON 序列化
    # send_list_udp(sample_list, serializer='pickle')      # 使用 pickle 序列化



