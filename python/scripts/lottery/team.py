#!/usr/bin/env python
'''
Author: gaoy
Date: 2022-06-20 05:08:03
LastEditors: gaoy
LastEditTime: 2022-07-02 23:00:38
Description: file content
'''
import random
import datetime

name_list = [
    ['personA', 0.], 
    ['personB', 0.], 
    ['personC', 0.], 
    ['personD', 0.],
    ['personE', 0.], 
    ['personF', 0.], 
    ['personG', 0.], 
    ['personH', 0.],
    ['personI', 0.], 
    ['personJ', 0.], 
    ['personK', 0.], 
    ['personL', 0.],
    ['personM', 0.], 
    ['personN', 0.]
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
input("Press Enter key to exit.")
