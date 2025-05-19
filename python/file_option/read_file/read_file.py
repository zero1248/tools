def read_numbers_file(filename):
    result = []
    with open(filename, 'r') as f:
        for line in f:
            # 去除首尾空白并分割数字
            numbers = line.strip().split()
            # 转换为整数并存入列表
            result.append([int(num) for num in numbers])
    return result

# 使用示例
data = read_numbers_file('qi_int64.txt')
transposed_data = [list(row) for row in zip(*data)]

# 验证读取结果
for row in transposed_data[:5]:
    print(transposed_data)

print(len(transposed_data))
print(len(transposed_data[0]))

# # 如果希望合并所有数字到一个一维列表
# def read_all_numbers(filename):
#     result = []
#     with open(filename, 'r') as f:
#         for line in f:
#             result.extend(map(int, line.strip().split()))
#     return result

# # 使用示例
# all_numbers = read_all_numbers('data.txt')
# print("\n合并后的前20个数字：", all_numbers[:20])


