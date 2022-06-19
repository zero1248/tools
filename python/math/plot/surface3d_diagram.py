# -*- coding: utf-8 -*-

# 导入三维工具 mplot3d 才能在 add_subplot 时添加参数
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np


# # 创建一个新图
# # fig = plt.figure()
# fig = plt.figure(figsize = (9, 6))
# # 创建一个子图（也可以创建多个，但一次只能一个）
# # 以下两个效果相同
# ax = fig.gca(projection = '3d')
# # ax = fig.add_subplot(111, projection = '3d') # 111 是子图编号
#
# # z = sin(sqrt(x^2+y^2))
# # 方程的输入使用参数方程的形式
# X = np.arange(-5, 5, 0.05)
# Y = np.arange(-5, 5, 0.05)
# # 由坐标向量 X，Y 返回坐标矩阵
# X, Y = np.meshgrid(X, Y)
# R = np.sqrt(X**2 + Y**2)
# Z = np.sin(R)
#
# # 绘制曲面图像
# surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm,
#                        linewidth=0, antialiased=False)
#
# # 定制 z 轴
# ax.set_zlim(-1.01, 1.01)
# ax.zaxis.set_major_locator(LinearLocator(10))
# ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))
# # 添加坐标轴标签(交换 x、y 轴)
# ax.set_xlabel('Y Label')
# ax.set_ylabel('X Label')
# ax.set_zlabel('Z Label')
#
# # Add a color bar which maps values to colors.
# fig.colorbar(surf, shrink=0.5, aspect=5)
#
# # # 保存图片，支持png格式（保存要在 show() 之前）
# # # dpi每英寸长度的点数,画出的三维图是矢量图，可以设置保存的dpi
# # plt.savefig('pictures/line_plots_3d..png', dpi=200)
#
# # 显示图像
# plt.show()



# # 球体
# fig = plt.figure(figsize = (9, 9))
# ax = fig.add_subplot(111, projection='3d')
#
# # Make data
# u = np.linspace(0, 2 * np.pi, 101)
# v = np.linspace(0, np.pi, 101)
# a = 10
# x = a * np.outer(np.cos(u), np.sin(v))
# y = a * np.outer(np.sin(u), np.sin(v))
# z = a * np.outer(np.ones(np.size(u)), np.cos(v))
#
# # Plot the surface
# ax.plot_surface(x, y, z, color='b')
#
# ax.set_xlabel('Y Label')
# ax.set_ylabel('X Label')
# ax.set_zlabel('Z Label')
#
# plt.show()


# # z = x*y
# # 创建一个新图
# # fig = plt.figure()
# fig = plt.figure(figsize = (12, 9))
# # 创建一个子图（也可以创建多个，但一次只能一个）
# # 以下两个效果相同
# ax = fig.gca(projection = '3d')
# # ax = fig.add_subplot(111, projection = '3d') # 111 是子图编号
#
# # z = sin(sqrt(x^2+y^2))
# # 方程的输入使用参数方程的形式
# u = np.linspace(-1, 1, 101)
#
# # 由坐标向量 X，Y 返回坐标矩阵
# X, Y = np.meshgrid(u, u)
# Z = X * Y
# v = np.linspace(0, 0, 101)
# X2, Y2 = np.meshgrid(v, v)
# Z2 = X2 * Y2
# print(Z)
# print(X2)
# print(Z2)
#
# # 绘制曲面图像
# surf = ax.plot_surface(X, Y, Z, cmap=cm.jet,
#                        linewidth=0, antialiased=False)
# surf = ax.plot_surface(X, Y, Z2, cmap=cm.coolwarm,
#                        linewidth=0, antialiased=False)
#
# # 定制 z 轴
# ax.set_zlim(-1.00, 1.00)
# ax.zaxis.set_major_locator(LinearLocator(10))
# ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))
# # 添加坐标轴标签(交换 x、y 轴)
# ax.set_xlabel('Y Label')
# ax.set_ylabel('X Label')
# ax.set_zlabel('Z Label')
#
# # Add a color bar which maps values to colors.
# fig.colorbar(surf, shrink=0.5, aspect=5)
#
# # # 保存图片，支持png格式（保存要在 show() 之前）
# # # dpi每英寸长度的点数,画出的三维图是矢量图，可以设置保存的dpi
# # plt.savefig('pictures/line_plots_3d..png', dpi=200)
#
# # 显示图像
# plt.show()










# # z = x*y
# # 创建一个新图
# # fig = plt.figure()
# fig = plt.figure(figsize = (12, 9))
# # 创建一个子图（也可以创建多个，但一次只能一个）
# # 以下两个效果相同
# ax = fig.gca(projection = '3d')
# # ax = fig.add_subplot(111, projection = '3d') # 111 是子图编号
#
# # z = sin(sqrt(x^2+y^2))
# # 方程的输入使用参数方程的形式
# u = np.linspace(0, 1, 9)
# w = np.linspace(0, 1, 3)
# xyz = np.linspace(0, 1, 6)
#
# # 由坐标向量 X，Y 返回坐标矩阵
# X, Y = np.meshgrid(u, w)
# Z = X * Y
#
# print(xyz)
# print(xyz**2)
#
#
# # print(X)
# # print(Y)
# # print(Z)
# # print(type(X))
# # print(type(Y))
# # print(type(Z))
#
# v = np.linspace(0, 0, 6)
# X2, Y2 = np.meshgrid(v, v)
# Z2 = X2 * Y2
# # print(Z)
# # print(X2)
# # print(Z2)
#
# # 绘制曲面图像
# surf = ax.plot_surface(X, Y, Z, cmap=cm.jet,
#                        linewidth=0, antialiased=False)
# # surf = ax.plot_surface(X, Y, Z2, cmap=cm.coolwarm,
# #                        linewidth=0, antialiased=False)
#
# # 定制 z 轴
# ax.set_zlim(-1.00, 1.00)
# ax.zaxis.set_major_locator(LinearLocator(10))
# ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))
# # 添加坐标轴标签(交换 x、y 轴)
# ax.set_xlabel('Y Label')
# ax.set_ylabel('X Label')
# ax.set_zlabel('Z Label')
#
# # Add a color bar which maps values to colors.
# fig.colorbar(surf, shrink=0.5, aspect=5)
#
# # # 保存图片，支持png格式（保存要在 show() 之前）
# # # dpi每英寸长度的点数,画出的三维图是矢量图，可以设置保存的dpi
# # plt.savefig('pictures/line_plots_3d..png', dpi=200)
#
# # 显示图像
# # plt.show()

#
# a = np.array([1, 2])
# b = np.mat([1, 2])
#
# c = np.array([[1, 2],
#               [3, 4]])
# d = np.mat([[1, 2],
#            [3, 4]])
# e = np.array([[1, 2, 3],
#               [4, 5, 6],
#               [7, 8, 9]])
# f = np.mat([[1, 2, 3],
#             [4, 5, 6],
#             [7, 8, 9]])


a = np.mat([[1, 2],
            [3, 4]])
b = np.mat([[1, 1],
           [2, 2]])
c = a*b
d = np.outer(a, b)
print(c)
print(d)
print(type(d))