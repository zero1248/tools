import numpy as np
import matplotlib.pyplot as plt

# 提取数据
data = np.loadtxt('test_out.txt')  # 从文件读取数据
x, y = data[:, 0], data[:, 1]                 # 提取x和y坐标

# 绘制散点图（生成的128个点）
plt.figure(figsize=(8, 8))                   # 设置画布大小
plt.scatter(x, y, color='red', s=20, label='Generated Points (128 points)')

# # 4. 绘制理想化的单位圆（用于参考）
# theta = np.linspace(0, 2*np.pi, 1000)        # 生成足够多的点使圆平滑
# ideal_x = np.cos(theta)
# ideal_y = np.sin(theta)
# plt.plot(ideal_x, ideal_y, color='blue', linestyle='--', linewidth=1, label='Ideal Unit Circle')

# 5. 图形美化
plt.title("Unit Circle Generated Points", fontsize=14)
plt.xlabel("X-axis", fontsize=12)
plt.ylabel("Y-axis", fontsize=12)
plt.axis('equal')                            # 确保坐标轴比例一致，圆不变形
plt.grid(True, linestyle='--', alpha=0.5)    # 添加虚线网格
plt.legend()                                 # 显示图例

# 显示图形
plt.show()

