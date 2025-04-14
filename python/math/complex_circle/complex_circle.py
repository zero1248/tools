import numpy as np
import matplotlib.pyplot as plt

# 1. 生成数据
# 生成128个等分角度（0到2π，不包括2π）
theta = np.linspace(0, 2 * np.pi, 128, endpoint=False)
# 计算x和y坐标，并转换为32位浮点数
x = np.cos(theta).astype(np.float32)
y = np.sin(theta).astype(np.float32)
# 合并为二维数组（每行包含x和y）
coordinates = np.column_stack((x, y))

# 2. 保存数据
# 保存到文件，每行格式为x y（空格分隔），小数点后保留六位。
np.savetxt('unit_circle_points.txt', coordinates, fmt='%.6f %.6f')
# 提取数据
# data = np.loadtxt('unit_circle_points.txt')  # 从文件读取数据
# x, y = data[:, 0], data[:, 1]                 # 提取x和y坐标

# 3. 绘制散点图（生成的128个点）
plt.figure(figsize=(8, 8))                   # 设置画布大小
plt.scatter(x, y, color='red', s=20, label='Generated Points (128 points)')

# 4. 绘制理想化的单位圆（用于参考）
theta = np.linspace(0, 2*np.pi, 1000)        # 生成足够多的点使圆平滑
ideal_x = np.cos(theta)
ideal_y = np.sin(theta)
plt.plot(ideal_x, ideal_y, color='blue', linestyle='--', linewidth=1, label='Ideal Unit Circle')

# 5. 图形美化
plt.title("Unit Circle Generated Points", fontsize=14)
plt.xlabel("X-axis", fontsize=12)
plt.ylabel("Y-axis", fontsize=12)
plt.axis('equal')                            # 确保坐标轴比例一致，圆不变形
plt.grid(True, linestyle='--', alpha=0.5)    # 添加虚线网格
plt.legend()                                 # 显示图例

# 显示图形
plt.show()


# 6. 将小数转换为整数（乘以1e8后取整）
x_int = (x * 10**8).astype(np.int32)
y_int = (y * 10**8).astype(np.int32)
# 合并为二维数组（每行包含两个整数）
coordinates = np.column_stack((x_int, y_int))
# 保存到文件，格式为整数
np.savetxt('unit_circle_points_int.txt', coordinates, fmt='%d %d')


