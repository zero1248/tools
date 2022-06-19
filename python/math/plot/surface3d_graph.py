# -*- coding: utf-8 -*-

# 导入三维工具 mplot3d 才能在 add_subplot 时添加参数
from mpl_toolkits.mplot3d import Axes3D
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

# x^2 + y^2 = (z^2 + 1)^2
# 设置标签字体大小
mpl.rcParams['legend.fontsize'] = 10

# 创建一个新图
# fig = plt.figure()
fig = plt.figure(figsize = (9, 6))
# 创建一个子图（也可以创建多个，但一次只能一个）
# 以下两个效果相同
ax = fig.gca(projection = '3d')
# ax = fig.add_subplot(111, projection = '3d') # 111 是子图编号

# 方程的输入使用参数方程的形式（此例相当于使用了柱坐标系的描述方式）
theta = np.linspace(-4 * np.pi, 4 * np.pi, 100)
z = np.linspace(-2, 2, 100)
r = z**2 + 1
# 初始 x、y 轴的位置与数学中常用的位置刚好相反，因此用 x = r*sin 来交换两个轴
x = r * np.sin(theta)
y = r * np.cos(theta)

# 绘制图像
ax.plot(x, y, z, 'g,-', label='parametric curve')
# 添加图像名称标签
ax.legend()
# 添加坐标轴标签(交换 x、y 轴)
ax.set_xlabel('Y Label')
ax.set_ylabel('X Label')
ax.set_zlabel('Z Label')

# 保存图片，支持png格式（保存要在 show() 之前）
# dpi每英寸长度的点数,画出的三维图是矢量图，可以设置保存的dpi
plt.savefig('pictures/line_plots_3d..png', dpi=200)

# 显示图像
plt.show()




# # x^2 + y^2 = 1 柱面上的螺旋线，每转一圈，z 值加1
# # x = cos(2*pi*z)
# # y = sin(2*pi*z)
# fig = plt.figure(figsize=(9, 6))
# # 添加参数 projection
# ax = fig.add_subplot(111, projection = '3d')
#
# z = np.linspace(0, 6, 1000)
# r = 1
# x = r * np.cos(np.pi*2*z)
# y = r * np.sin(np.pi*2*z)
# ax.plot(x, y, z, 'r-', label = 'x = cos(2*pi*z) y = sin(2*pi*z)')
# ax.legend()
# # plt.savefig('3d_line_plots.png', dpi=200)
# plt.show()

