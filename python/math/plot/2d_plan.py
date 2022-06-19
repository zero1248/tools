# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np


# x = np.linspace(0, 2 * np.pi, 100)
# plt.plot(x, np.sin(x))               # 如果没有第一个参数 x，图形的 x 坐标默认为数组的索引
# plt.show()                           # 显示图形


# x = np.linspace(0, 2 * np.pi, 50)
# plt.plot(x, np.sin(x),
#          x, np.sin(2 * x),
#          x, np.sin(3 * x))
# plt.show()


# # 自定义曲线的外观
# x = np.linspace(0, 2 * np.pi, 50)
# plt.plot(x, np.sin(x), 'r-o',
#         x, np.cos(x), 'g--')
# plt.show()


# # 使用子图
# x = np.linspace(0, 2 * np.pi, 50)
# plt.subplot(2, 1, 1) # （行，列，活跃区）
# plt.plot(x, np.sin(x), 'r')
# plt.subplot(2, 1, 2)
# plt.plot(x, np.cos(x), 'g')
# plt.show()


# # 简单的散点图
# x = np.linspace(0, 2 * np.pi, 50)
# y = np.sin(x)
# plt.scatter(x,y)
# plt.show()


# # 柱状图
# size = 5
# x = np.arange(size)
# a = np.random.random(size)
# b = np.random.random(size)
# c = np.random.random(size)
#
# total_width, n = 0.8, 3
# width = total_width / n
# x = x - (total_width - width) / 2
#
# plt.bar(x, a,  width=width, label='a')
# plt.bar(x + width, b, width=width, label='b')
# plt.bar(x + 2 * width, c, width=width, label='c')
# plt.legend()
# plt.show()


# # 彩色映射散点图
# x = np.random.rand(1000)
# y = np.random.rand(1000)
# size = np.random.rand(1000) * 50
# colour = np.random.rand(1000)
# plt.scatter(x, y, size, colour)
# plt.colorbar()
# plt.show()


# 直方图
# x = np.random.randn(1000)
# plt.hist(x, 50)
# plt.show()


# 添加标题，坐标轴标记和图例
# 打印 sinx 和 cosx
# x = np.linspace(0, 2 * np.pi, 50)
# plt.plot(x, np.sin(x), 'r-x', label='Sin(x)')
# plt.plot(x, np.cos(x), 'g-^', label='Cos(x)')
# plt.legend() # 展示图例
# plt.xlabel('x') # 给 x 轴添加标签
# plt.ylabel('y') # 给 y 轴添加标签
# plt.title('Sin and Cos Waves') # 添加图形标题
# plt.show()


# # 添加标题，坐标轴标记和图例
# # 打印 sin(sinx) 和 cos(cosx)
# x = np.linspace(0, 0.5 * np.pi, 50)
# plt.plot(x, np.sin(np.sin(x)), 'r-x', label='sin(sinx)')
# plt.plot(x, np.cos(np.cos(x)), 'g-^', label='cos(cosx)')
# plt.legend() # 展示图例
# # plt.xlabel('x') # 给 x 轴添加标签
# # plt.ylabel('y') # 给 y 轴添加标签
# # plt.title('Sin and Cos Waves') # 添加图形标题
# plt.show()


# # 添加标题，坐标轴标记和图例
# # 打印 sinx 和 x
# # x = np.linspace(0, 1, 50)
# x = np.linspace(0, 2 * np.pi, 50)
# plt.plot(x, np.sin(x), 'r-x', label='y=sin(x)')
# plt.plot(x, x, 'g-^', label='y=x')
# plt.legend() # 展示图例
# plt.xlabel('x') # 给 x 轴添加标签
# plt.ylabel('y') # 给 y 轴添加标签
# plt.title('y=sinx and y=x Waves') # 添加图形标题
# plt.show()

# 1.27-1.31 新型肺炎情况
x = np.linspace(1.27, 1.31, 5)
y = [1771, 1459, 1727, 1982, 2102]
plt.plot(x, y, 'r-x', label='increment')
plt.legend() # 展示图例
plt.xlabel('x') # 给 x 轴添加标签
plt.ylabel('y') # 给 y 轴添加标签
plt.title('1.27-1.31') # 添加图形标题
plt.show()