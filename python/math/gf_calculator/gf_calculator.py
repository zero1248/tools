import tkinter as tk
from tkinter import ttk, messagebox

# 伽罗瓦域GF(2^8)乘法表（使用不可约多项式 x^8 + x^4 + x^3 + x^2 + 1）
irreducible_poly = 0x11d  # x^8 + x^4 + x^3 + x^2 + 1


def gf_multiply(a, b):
    """伽罗瓦域GF(2^8)乘法"""
    p = 0
    for _ in range(8):
        if b & 1:
            p ^= a
        hi_bit_set = a & 0x80
        a <<= 1
        if hi_bit_set:
            a ^= irreducible_poly
        b >>= 1
    return p


def calculate():
    try:
        # 获取输入
        input1 = entry1.get().strip()
        input2 = entry2.get().strip()
        operation = operation_var.get()

        # 验证输入
        if not input1 or not input2:
            messagebox.showerror("错误", "请输入两个有效的十六进制值")
            return

        # 将输入转换为字节数组
        bytes1 = bytes.fromhex(input1)
        bytes2 = bytes.fromhex(input2)

        # 确保两个输入长度相同
        if len(bytes1) != len(bytes2):
            messagebox.showerror("错误", "输入的长度必须相同")
            return

        result_bytes = bytearray()

        # 根据选择的操作进行计算
        if operation == "XOR":
            for b1, b2 in zip(bytes1, bytes2):
                result_bytes.append(b1 ^ b2)
        elif operation == "GF Multiply":
            for b1, b2 in zip(bytes1, bytes2):
                result_bytes.append(gf_multiply(b1, b2))

        # 显示结果
        result_var.set(result_bytes.hex().upper())

    except ValueError as e:
        messagebox.showerror("错误", f"无效的输入格式: {str(e)}")
    except Exception as e:
        messagebox.showerror("错误", f"发生错误: {str(e)}")


def clear_inputs():
    entry1.delete(0, tk.END)
    entry2.delete(0, tk.END)
    result_var.set("")


# 创建主窗口
root = tk.Tk()
root.title("异或和伽罗瓦GF(2^8)乘法计算器")
root.geometry("500x300")

# 使用主题
style = ttk.Style()
style.theme_use('clam')

# 创建输入框架
input_frame = ttk.Frame(root, padding="10")
input_frame.pack(fill=tk.BOTH, expand=True)

# 操作选择
operation_var = tk.StringVar(value="XOR")
operation_label = ttk.Label(input_frame, text="选择操作:")
operation_label.grid(row=0, column=0, padx=5, pady=5, sticky=tk.W)
xor_radio = ttk.Radiobutton(input_frame, text="异或(XOR)", variable=operation_var, value="XOR")
xor_radio.grid(row=0, column=1, padx=5, pady=5, sticky=tk.W)
gf_radio = ttk.Radiobutton(input_frame, text="伽罗瓦乘法(GF Multiply)", variable=operation_var, value="GF Multiply")
gf_radio.grid(row=0, column=2, padx=5, pady=5, sticky=tk.W)

# 输入1
label1 = ttk.Label(input_frame, text="输入1 (十六进制):")
label1.grid(row=1, column=0, padx=5, pady=5, sticky=tk.W)
entry1 = ttk.Entry(input_frame, width=40)
entry1.grid(row=1, column=1, columnspan=2, padx=5, pady=5, sticky=tk.W + tk.E)

# 输入2
label2 = ttk.Label(input_frame, text="输入2 (十六进制):")
label2.grid(row=2, column=0, padx=5, pady=5, sticky=tk.W)
entry2 = ttk.Entry(input_frame, width=40)
entry2.grid(row=2, column=1, columnspan=2, padx=5, pady=5, sticky=tk.W + tk.E)

# 结果
result_var = tk.StringVar()
result_label = ttk.Label(input_frame, text="结果 (十六进制):")
result_label.grid(row=3, column=0, padx=5, pady=5, sticky=tk.W)
result_entry = ttk.Entry(input_frame, textvariable=result_var, width=40, state='readonly')
result_entry.grid(row=3, column=1, columnspan=2, padx=5, pady=5, sticky=tk.W + tk.E)

# 按钮框架
button_frame = ttk.Frame(root, padding="10")
button_frame.pack(fill=tk.BOTH, expand=True)

# 计算按钮
calc_button = ttk.Button(button_frame, text="计算", command=calculate)
calc_button.pack(side=tk.LEFT, padx=5, pady=5)

# 清除按钮
clear_button = ttk.Button(button_frame, text="清除", command=clear_inputs)
clear_button.pack(side=tk.LEFT, padx=5, pady=5)

# 退出按钮
exit_button = ttk.Button(button_frame, text="退出", command=root.quit)
exit_button.pack(side=tk.RIGHT, padx=5, pady=5)

# 使用说明
instructions = ttk.Label(root, text="使用说明: 输入两个十六进制值(如'A1'或'A1B2C3')，选择操作类型，然后点击计算。")
instructions.pack(side=tk.BOTTOM, padx=5, pady=5, fill=tk.X)

root.mainloop()