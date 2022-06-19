# 使用ployfit进行曲线拟合
import numpy as np
import matplotlib.pyplot as plt

# 定义x、y散点坐标

x = np.arange(3200, 35000, 3200)
num1 = [0.472,0.469,0.447,0.433,0.418,0.418,0.418,0.418,0.418,0.418]
num2 = [0.337,0.327,0.325,0.316,0.312,0.311,0.308,0.305,0.295,0.290]
y1 = np.array(num1)
y2 = np.array(num2)


# 用3次多项式拟合
f1 = np.polyfit(x, y1, 3)
p1 = np.poly1d(f1)
print(p1)  # 打印出拟合函数
yvals1 = p1(x)  # 拟合y值

f2 = np.polyfit(x, y2, 3)
p2 = np.poly1d(f2)
print(p2)
# 也可使用yvals=np.polyval(f1, x)
yvals2 = p2(x)

# 绘图
plot1 = plt.plot(x, y1, 's', label='original values')
plot2 = plt.plot(x, yvals1, 'r', label='polyfit values')
plot3 = plt.plot(x, y2, 's', label='original values2')
plot4 = plt.plot(x, yvals2, 'r', label='polyfit values2')

plt.xlabel('x')
plt.ylabel('y')
plt.legend(loc=2, bbox_to_anchor=(1.05, 1.0), borderaxespad=0.)
plt.title('polyfitting')
plt.savefig('nihe1.png')
plt.show()




# # 使用 curve_fit 进行曲线拟合
# import numpy as np
# import matplotlib.pyplot as plt
# from scipy.optimize import curve_fit
#
#
# def func(x, a, b, c):
#     return a * x ** 2 + b * x + c
#
#
# # 定义x、y散点坐标
# x = np.arange(3200, 35000, 3200)
# num1 = [0.472, 0.469, 0.447, 0.433, 0.418, 0.418, 0.418, 0.418, 0.418, 0.418]
# y1 = np.array(num1)
#
# # 绘图
# plot1 = plt.plot(x, y1, 'ms', label='orig1')
#
# popt, pcov = curve_fit(func, x, y1)
# yy2 = [func(i, popt[0], popt[1], popt[2]) for i in x]
# plt.plot(x, yy2, 'r-', label='fit')
#
# print
# var = u'系数a:', popt[0]
# print
# u'系数b:', popt[1]
# print
# u'系数c:', popt[2]
#
# plt.xlabel('x')
# plt.ylabel('y')
# plt.legend(loc=2, bbox_to_anchor=(1.05, 1.0), borderaxespad=0.)
# plt.title('polyfitting')
# plt.subplots_adjust(right=0.75)
# plt.savefig('test3.png', frameon=True, figsize=(18.5, 10.5), dpi=100)
# plt.show()

