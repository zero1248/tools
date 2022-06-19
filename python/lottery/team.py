import random
import datetime

name_list = [
    ['personA', 0.], 
    ['personA', 0.], 
    ['personA', 0.], 
    ['personA', 0.],
    ['personA', 0.], 
    ['personA', 0.], 
    ['personA', 0.], 
    ['personA', 0.],
    ['personA', 0.], 
    ['personA', 0.], 
    ['personA', 0.], 
    ['personA', 0.],
    ['personA', 0.], 
    ['personA', 0.]
    ]

print("生成随机数：")
for name in name_list:
    name[1] = random.random()
    print('{} : {}'.format(name[0], name[1]))
print('')

print("排序后：")
name_list.sort(key=lambda x: x[1], reverse=True)
for name in name_list:
    print('{} : {}'.format(name[0], name[1]))
print('')

print('让我们恭喜{}同学成为组长！他的分数为{}！'.format(name_list[0][0], name_list[0][1]))

now = datetime.datetime.now()
print("时间戳:", now)
