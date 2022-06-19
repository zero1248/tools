import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt

# mpl.rcParams['legend.fontsize'] = 10

# fig = plt.figure()
# ax = fig.gca(projection='3d')
# theta = np.linspace(-4 * np.pi, 4 * np.pi, 100)
# z = np.linspace(-2, 2, 100)
# r = z**2 + 1
# x = r * np.sin(theta)
# y = r * np.cos(theta)
# ax.plot(x, y, z, label='parametric curve')
# ax.legend()

# plt.show()

# 设置标签字体大小
mpl.rcParams['legend.fontsize'] = 10

# 创建一个新图
# fig = plt.figure()
fig = plt.figure(figsize=(9, 6))
# 创建一个子图（也可以创建多个，但一次只能一个）
# 以下两个效果相同
ax = fig.gca(projection = '3d')
# ax = fig.add_subplot(111, projection = '3d') # 111 是子图编号

# 方程的输入使用参数方程的形式（此例相当于使用了柱坐标系的描述方式）
theta = np.linspace(-4 * np.pi, 4 * np.pi, 100)
z = np.linspace(-2, 2, 100)
r = z**2 + 1
x = r * np.sin(theta)
y = r * np.cos(theta)

# 绘制图像
ax.plot(x, y, z, 'g,-', label='parametric curve')
# 添加图像名称标签
ax.legend()
# 添加坐标轴标签
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

# 保存图片，支持png格式（保存要在 show() 之前）
# dpi每英寸长度的点数,画出的三维图是矢量图，可以设置保存的dpi
plt.savefig('pictures/line_plots_3d..png', dpi=200)

# 显示图像
plt.show()