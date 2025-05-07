from os import path
import os


# 将要修改编码格式的文件放在 /data 目录下
# 将本脚本与 /data 目录放在同一级
# 所有文件将改为统一的 modify_name+i.txt

# 下一行的 modify_name 改为要改成的名字，suffix 改为要改成的尾缀
modify_name = 'biubiubiu'
suffix = '.txt'

cur_path = path.dirname(__file__)  # 获取当前脚本路径
cur_process_path = cur_path + '/' + 'data/'


print(cur_process_path)
filenames = os.listdir(cur_process_path)
print('files:')
print(filenames)
print("total files: " + str(len(filenames)))
print('')

i = 0
for filename in filenames:
    i += 1
    filename = cur_process_path + '/' + filename
    modifyname = cur_process_path + '/' + modify_name + str(i) + suffix
    os.rename(filename, modifyname)
