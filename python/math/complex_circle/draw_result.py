import numpy as np
import matplotlib.pyplot as plt

def plot_points_with_highlights(input_file, highlight_indices=None, 
                                save_output=None, dpi=200, margin=0.1):
    """
    绘制数据点并突出显示特定点，根据实际数据范围设置坐标轴
    
    参数:
    input_file -- 包含坐标数据的文件名
    highlight_indices -- 要突出显示的点的索引列表
    save_output -- 保存图片的文件名（可选）
    dpi -- 图片分辨率
    margin -- 数据点与坐标轴边缘的边距比例
    """
    # 1. 加载数据
    data = np.loadtxt(input_file)
    if data.shape[1] < 2:
        raise ValueError("数据文件应至少包含两列坐标值")
        
    x, y = data[:, 0], data[:, 1]
    
    # 2. 创建图形
    plt.figure(figsize=(8, 8))
    
    # 3. 绘制所有点
    plt.scatter(x, y, color='red', s=20, alpha=0.7, label=f'Generated Points ({len(x)} points)')
    
    # 4. 突出显示特定点
    if highlight_indices is None:
        # 默认不突出显示任何点
        highlight_indices = []
    elif isinstance(highlight_indices, int):
        highlight_indices = [highlight_indices]
    
    if highlight_indices:
        # 确保索引在有效范围内
        valid_indices = [i for i in highlight_indices if i < len(x)]
        highlight_x = x[valid_indices]
        highlight_y = y[valid_indices]
        
        # 用不同样式绘制突出点
        plt.scatter(highlight_x, highlight_y, 
                    s=100, 
                    color='blue', 
                    marker='D',
                    edgecolor='gold',
                    linewidths=1.5,
                    zorder=10,
                    label=f'Highlighted Points ({len(valid_indices)} points)')
        
        # 添加文字标签（根据数据动态调整偏移量）
        x_range = np.ptp(x)  # 计算x轴的值范围
        y_range = np.ptp(y)  # 计算y轴的值范围
        offset_x = x_range * 0.03
        offset_y = y_range * 0.03
        
        for i, (px, py) in enumerate(zip(highlight_x, highlight_y)):
            plt.text(px + offset_x * (1 if px >= 0 else -1), 
                     py + offset_y * (1 if py >= 0 else -1), 
                     f'P{valid_indices[i]}',
                     fontsize=10, 
                     color='darkblue',
                     weight='bold',
                     ha='left' if px >= 0 else 'right')

    # 5. 根据实际数据设置坐标轴范围
    # 计算数据范围并添加边距
    min_x, max_x = np.min(x), np.max(x)
    min_y, max_y = np.min(y), np.max(y)
    width = max_x - min_x
    height = max_y - min_y
    
    # 添加动态边距
    x_margin = max(width * margin, abs(min_x * margin), abs(max_x * margin))
    y_margin = max(height * margin, abs(min_y * margin), abs(max_y * margin))
    print(x_margin)
    
    plt.xlim(min_x - x_margin, max_x + x_margin)
    plt.ylim(min_y - y_margin, max_y + y_margin)
    
    # 设置网格间隔
    plt.gca().xaxis.set_major_locator(plt.MaxNLocator(10))
    plt.gca().yaxis.set_major_locator(plt.MaxNLocator(10))
    
    # 6. 图形美化
    plt.title(f"Data Points: {input_file}", fontsize=14)
    plt.xlabel("X-axis", fontsize=12)
    plt.ylabel("Y-axis", fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.5)
    plt.legend()
    
    # 7. 保存或显示结果
    if save_output:
        plt.savefig(save_output, dpi=dpi, bbox_inches='tight')
        print(f"图形已保存为: {save_output}")
    plt.show()

# 使用示例
if __name__ == "__main__":
    # 示例1: 绘制默认
    # plot_points_with_highlights('test_out.txt')
    
    # 示例2: 突出特定点
    plot_points_with_highlights(
        input_file='test_in.txt',
        highlight_indices=[0, 32, 64, 96],
        save_output='test_in.png'
    )
    plot_points_with_highlights(
        input_file='test_out.txt',
        highlight_indices=[0, 32, 64, 96],
        save_output='test_out.png'
    )



    
    # # 示例3: 增大边距
    # plot_points_with_highlights(
    #     input_file='large_range_data.csv',
    #     margin=0.15
    # )



