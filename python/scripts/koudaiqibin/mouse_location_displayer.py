import pyautogui
import time
import tkinter as tk
from tkinter import ttk

def get_mouse_position():
    """获取当前鼠标坐标并返回格式化字符串"""
    x, y = pyautogui.position()
    return f"当前鼠标位置: ({x}, {y})"

def update_label():
    """更新标签显示并设置下一轮更新"""
    position_text.set(get_mouse_position())
    position_label.config(foreground='blue')  # 更新后变为蓝色
    root.after(50, update_label)  # 每50毫秒更新一次 (20fps)

def on_key_press(event):
    """处理按键事件"""
    if event.keysym == 'Escape':  # 按ESC键退出程序
        root.destroy()
    elif event.keysym in ['C', 'c']:  # 按C键复制坐标到剪贴板
        x, y = pyautogui.position()
        root.clipboard_clear()
        root.clipboard_append(f"({x}, {y})")
        position_text.set(f"已复制坐标 ({x}, {y}) 到剪贴板!")
        position_label.config(foreground='green')  # 复制成功后变为绿色
    else:
        position_text.set(get_mouse_position() + " - 按 C 复制坐标 | ESC 退出")

if __name__ == '__main__':

    # 创建主窗口
    root = tk.Tk()
    root.title("鼠标坐标实时显示器")
    root.geometry("400x100")
    root.resizable(False, False)

    # 设置样式
    style = ttk.Style()
    style.configure("TLabel", font=("微软雅黑", 12), padding=10)

    # 创建显示文本的变量
    position_text = tk.StringVar()
    position_text.set("正在初始化...")

    # 创建显示标签
    position_label = ttk.Label(root, textvariable=position_text, style="TLabel")
    position_label.pack(expand=True, fill='both')

    # 添加帮助文本
    help_label = ttk.Label(root, text="按 'C' 复制坐标 | 'ESC' 退出程序", font=("微软雅黑", 9), foreground="gray")
    help_label.pack(side='bottom', pady=(0, 5))

    # 设置全局按键绑定
    root.bind("<Key>", on_key_press)

    # 设置窗口关闭事件
    root.protocol("WM_DELETE_WINDOW", root.destroy)

    # 开始更新位置
    root.after(500, update_label)  # 0.5秒后开始更新

    # 运行主循环
    root.mainloop()