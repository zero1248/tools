import socket
import json
import pickle

def receive_list_udp(port=4096, serializer='json', buffer_size=65535):
    """
    接收UDP列表数据
    参数：
    - port: 监听端口
    - serializer: 反序列化方式（需与发送端一致）
    - buffer_size: 接收缓冲区大小
    """
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        sock.bind(('0.0.0.0', port))
        print(f"监听端口 {port}...")
        
        while True:
            data, addr = sock.recvfrom(buffer_size)
            print(f"\n收到来自 {addr} 的数据包")
            
            try:
                # 反序列化数据
                if serializer == 'json':
                    decoded = json.loads(data.decode('utf-8'))
                elif serializer == 'pickle':
                    decoded = pickle.loads(data)
                else:
                    raise ValueError("不支持的序列化方式")
                
                print(f"接收到的列表: {decoded}")
                print(f"数据类型: {type(decoded)}")
                
            except Exception as e:
                print(f"数据解析失败: {str(e)}")
                
    except KeyboardInterrupt:
        print("\n停止接收")
    finally:
        sock.close()

# 示例使用
if __name__ == '__main__':
    receive_list_udp(serializer='json')  # 需与发送端序列化方式一致