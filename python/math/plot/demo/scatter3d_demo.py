'''
==============
3D scatterplot
==============

Demonstration of a basic scatterplot in 3D.
'''

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np


def randrange(n, vmin, vmax):
    '''
    Helper function to make an array of random numbers having shape (n, )
    with each number distributed Uniform(vmin, vmax).
    '''
    return (vmax - vmin)*np.random.rand(n) + vmin

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

n = 100

# For each set of style and range settings, plot n random points in the box
# defined by x in [23, 32], y in [0, 100], z in [zlow, zhigh].
for c, m, zlow, zhigh in [('r', 'o', -50, -25), ('b', '^', -30, -5)]:
    xs = randrange(n, 23, 32)
    ys = randrange(n, 0, 100)
    zs = randrange(n, zlow, zhigh)
    ax.scatter(xs, ys, zs, c=c, marker=m)

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show()



# 导入三维工具 mplot3d 才能在 add_subplot 时添加参数
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np


# 生成伪随机数
def randrange(n, vmin, vmax):
    '''
    Helper function to make an array of random numbers having shape (n, )
    with each number distributed Uniform(vmin, vmax).
    '''
    return (vmax - vmin)*np.random.rand(n) + vmin

# 创建一个新图
# fig = plt.figure()
fig = plt.figure(figsize = (9, 6))
# 创建一个子图（也可以创建多个，但一次只能一个）
# 以下两个效果相同
ax = fig.gca(projection = '3d')
# ax = fig.add_subplot(111, projection='3d')

n = 100

# 对于每一组样式和范围设置，在框中绘制n个随机点
# x in [23, 32], y in [0, 100], z in [zlow, zhigh]
# 循环两次，每次生成 100 个点
for c, m, zlow, zhigh in [('r', 'o', -50, -25), ('b', '^', -30, -5)]:
    # 获取 100 组三维坐标
    xs = randrange(n, 23, 32)
    ys = randrange(n, 0, 100)
    zs = randrange(n, zlow, zhigh)
    # 绘制图像
    ax.scatter(xs, ys, zs, c = c, marker = m)

# 添加坐标轴标签
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

# 保存图片，支持png格式（保存要在 show() 之前）
# dpi 每英寸长度的点数，画出的三维图是矢量图，可以设置保存的 dpi
plt.savefig("picture/scatter_plots_3d.png", dpi = 200)

# 显示图像
plt.show()