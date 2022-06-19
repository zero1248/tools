from os import path
import os
import chardet

# 将要修改编码格式的文件放在 /data 目录下
# 将本脚本与 /data 目录放在同一级

# 需要转换到的编码格式
transTo = 'utf-8'

cur_path = path.dirname(__file__)  # 获取当前脚本路径
cur_process_path = cur_path + '/data'

print(cur_process_path)
filenames = os.listdir(cur_process_path)
print('files:')
print(filenames)
print("total files: " + str(len(filenames)))
print('')

for filename in filenames:
    filename = cur_process_path + '/' + filename
    with open(filename, 'rb+') as F:
        content = F.read()
        # 判断编码格式
        encoding = chardet.detect(content)['encoding']
        print(encoding)
        if encoding != None:
            # 格式转换
            content = content.decode(encoding).encode(transTo)
            # 写回文件
            F.seek(0)
            F.write(content)
        else:
            print("The encoding of file {} is None".format(filename))
