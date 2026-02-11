#!/usr/bin/env python3
"""
generate_test_data.py

可视化测试数据生成器（Tkinter）
功能：
- 选择输出模式（Raw binary / Text）
- 配置 bytes_per_value, total_values, values_per_line, separator
- 选择值生成模式（Random / Increment / Fixed）
- 选择文本显示格式（Hex/Bin/Dec/ASCII）
- 预览、复制预览、保存到文件（分块写入并显示进度）
"""

import tkinter as tk
from tkinter import ttk, filedialog, messagebox
import random
import math
import os
import sys
import string
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np
import matplotlib.pyplot as plt


APP_TITLE = "测试数据生成器"
# 设置全局字体（支持中文的字体，如 SimHei、Microsoft YaHei）
plt.rcParams['font.sans-serif'] = ['SimHei']  # Windows 默认中文字体
plt.rcParams['axes.unicode_minus'] = False   # 解决负号显示问题




# ---------- 生成器与格式化工具 ----------
def clamp_int(v, minv, maxv):
    try:
        iv = int(v)
    except Exception:
        return minv
    return max(minv, min(maxv, iv))

def is_printable_byte(b):
    c = chr(b)
    return c in string.printable and c not in '\t\n\r\x0b\x0c'

def sanitize_separator(s):
    # 支持常见转义写法 \t, \n
    return s.encode('utf-8').decode('unicode_escape')

def value_generator(mode, bytes_per_value, total_values, start=0, step=1, fixed_value=0, rand_seed=None):
    """
    生成整数值（每个值的范围由 bytes_per_value 决定）
    mode: 'random'|'increment'|'fixed'
    yields ints in range [0, max_value]
    """
    max_value = (1 << (bytes_per_value * 8)) - 1
    rng = random.Random(rand_seed)
    if mode == 'random':
        for _ in range(total_values):
            yield rng.randint(0, max_value)
    elif mode == 'increment':
        v = start & max_value
        for _ in range(total_values):
            yield v
            v = (v + step) & max_value
    elif mode == 'fixed':
        val = fixed_value & max_value
        for _ in range(total_values):
            yield val
    else:
        raise ValueError("Unknown mode")

def int_to_bytes_le_be(value, length, little_endian):
    return value.to_bytes(length, byteorder='little' if little_endian else 'big')

def format_value_text(value, bytes_per_value, fmt, hex_upper=False, hex_prefix=False, little_endian=False):
    """
    将单个整数 value 格式化为文本（不会包含分隔符）
    fmt: 'hex'|'bin'|'dec'|'ascii'
    """
    if fmt == 'hex':
        width = bytes_per_value * 2
        s = f"{value:0{width}X}" if hex_upper else f"{value:0{width}x}"
        if hex_prefix:
            s = ("0x" + s) if not hex_upper else ("0x" + s)  # 0x 不区分大小写，但保留 prefix
        return s
    elif fmt == 'bin':
        width = bytes_per_value * 8
        return format(value, f'0{width}b')
    elif fmt == 'dec':
        return str(value)
    elif fmt == 'ascii':
        b = int_to_bytes_le_be(value, bytes_per_value, little_endian)
        # 对每个字节进行可打印检查，不可打印则显示 '.'
        chars = []
        for byte in b:
            if is_printable_byte(byte):
                chars.append(chr(byte))
            else:
                chars.append('.')
        return ''.join(chars)
    else:
        return str(value)

# ---------- GUI 主应用 ----------
class TestDataGeneratorApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title(APP_TITLE)        # 设置窗口标题
        self.geometry("1200x800")     # 设置窗口初始大小（宽x高）
        self.minsize(980, 640)       # 设置窗口最小尺寸（用户不能缩小到比这更小）
        self._build_ui()             # 调用自定义方法构建UI组件

    def _build_ui(self):
        pad = 8
        main = ttk.Frame(self)
        main.pack(fill=tk.BOTH, expand=True, padx=pad, pady=pad)

        left = ttk.Frame(main)
        left.pack(side=tk.LEFT, fill=tk.Y, padx=(0, pad))

        right = ttk.Frame(main)
        right.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)

        # -------------- 左侧参数区 --------------
        # 输出模式
        mode_frame = ttk.LabelFrame(left, text="输出 / 文件模式")
        mode_frame.pack(fill=tk.X, pady=4)
        self.output_mode = tk.StringVar(value='text')  # 'text' or 'binary'
        ttk.Radiobutton(mode_frame, text="文本 (可读)", variable=self.output_mode, value='text').pack(anchor=tk.W, padx=6, pady=2)
        ttk.Radiobutton(mode_frame, text="原始二进制 (.bin)", variable=self.output_mode, value='binary').pack(anchor=tk.W, padx=6, pady=2)

        # 值格式（文本显示用）
        fmt_frame = ttk.LabelFrame(left, text="文本显示格式（仅适用于文本输出或预览）")
        fmt_frame.pack(fill=tk.X, pady=4)
        self.value_format = tk.StringVar(value='hex')  # hex / bin / dec / ascii
        for txt, v in [("Hex", 'hex'), ("Binary", 'bin'), ("Decimal", 'dec'), ("ASCII", 'ascii')]:
            ttk.Radiobutton(fmt_frame, text=txt, variable=self.value_format, value=v).pack(anchor=tk.W, padx=6)

        # Hex 选项 & Endianness
        opt_frame = ttk.Frame(left)
        opt_frame.pack(fill=tk.X, pady=4)
        self.hex_upper = tk.BooleanVar(value=True)
        self.hex_prefix = tk.BooleanVar(value=False)
        ttk.Checkbutton(opt_frame, text="Hex 大写", variable=self.hex_upper).grid(row=0, column=0, sticky=tk.W, padx=4, pady=2)
        ttk.Checkbutton(opt_frame, text="显示 0x 前缀 (文本)", variable=self.hex_prefix).grid(row=0, column=1, sticky=tk.W, padx=4, pady=2)
        ttk.Label(opt_frame, text="字节序:").grid(row=1, column=0, sticky=tk.W, padx=4)
        self.endianness = tk.StringVar(value='little')
        ttk.Radiobutton(opt_frame, text="Little-endian", variable=self.endianness, value='little').grid(row=1, column=1, sticky=tk.W)
        ttk.Radiobutton(opt_frame, text="Big-endian", variable=self.endianness, value='big').grid(row=1, column=2, sticky=tk.W)

        # bytes_per_value, total_values, per_line, separator
        size_frame = ttk.LabelFrame(left, text="数据尺寸与布局")
        size_frame.pack(fill=tk.X, pady=4)
        ttk.Label(size_frame, text="每个值占字节数 (1-8):").grid(row=0, column=0, sticky=tk.W, padx=4, pady=2)
        self.bytes_per_value = tk.Spinbox(size_frame, from_=1, to=8, width=6)
        self.bytes_per_value.delete(0, tk.END); self.bytes_per_value.insert(0, "1")
        self.bytes_per_value.grid(row=0, column=1, sticky=tk.W, padx=4)

        ttk.Label(size_frame, text="总值数量 (values):").grid(row=1, column=0, sticky=tk.W, padx=4, pady=2)
        self.total_values_var = tk.Entry(size_frame, width=12)
        self.total_values_var.insert(0, "256")
        self.total_values_var.grid(row=1, column=1, sticky=tk.W, padx=4)

        ttk.Label(size_frame, text="每行多少值:").grid(row=2, column=0, sticky=tk.W, padx=4, pady=2)
        self.values_per_line = tk.Spinbox(size_frame, from_=1, to=1024, width=8)
        self.values_per_line.delete(0, tk.END); self.values_per_line.insert(0, "16")
        self.values_per_line.grid(row=2, column=1, sticky=tk.W, padx=4)

        ttk.Label(size_frame, text="值间分隔符:").grid(row=3, column=0, sticky=tk.W, padx=4, pady=2)
        self.sep_entry = tk.Entry(size_frame, width=12)
        self.sep_entry.insert(0, " ")
        self.sep_entry.grid(row=3, column=1, sticky=tk.W, padx=4)
        ttk.Label(size_frame, text="（支持转义，如 \\t, \\n）").grid(row=3, column=2, sticky=tk.W)

        # 生成模式（pattern）
        pattern_frame = ttk.LabelFrame(left, text="值生成模式 (pattern)")
        pattern_frame.pack(fill=tk.X, pady=4)
        self.pattern_mode = tk.StringVar(value='increment')
        ttk.Radiobutton(pattern_frame, text="递增 (推荐)", variable=self.pattern_mode, value='increment').grid(row=0, column=0, sticky=tk.W, padx=4, pady=2)
        ttk.Radiobutton(pattern_frame, text="随机", variable=self.pattern_mode, value='random').grid(row=0, column=1, sticky=tk.W, padx=4, pady=2)
        ttk.Radiobutton(pattern_frame, text="固定值", variable=self.pattern_mode, value='fixed').grid(row=0, column=2, sticky=tk.W, padx=4, pady=2)

        ttk.Label(pattern_frame, text="起始值:").grid(row=1, column=0, sticky=tk.W, padx=4)
        self.start_value = tk.Entry(pattern_frame, width=12); self.start_value.insert(0, "0")
        self.start_value.grid(row=1, column=1, sticky=tk.W, padx=4)

        ttk.Label(pattern_frame, text="步长:").grid(row=2, column=0, sticky=tk.W, padx=4)
        self.step_value = tk.Entry(pattern_frame, width=12); self.step_value.insert(0, "1")
        self.step_value.grid(row=2, column=1, sticky=tk.W, padx=4)

        ttk.Label(pattern_frame, text="固定值:").grid(row=3, column=0, sticky=tk.W, padx=4)
        self.fixed_value = tk.Entry(pattern_frame, width=12); self.fixed_value.insert(0, "0")
        self.fixed_value.grid(row=3, column=1, sticky=tk.W, padx=4)

        # 预览行数和操作按钮
        action_frame = ttk.Frame(left)
        action_frame.pack(fill=tk.X, pady=6)
        ttk.Label(action_frame, text="预览行数:").grid(row=0, column=0, sticky=tk.W, padx=4)
        self.preview_lines = tk.Spinbox(action_frame, from_=1, to=1000, width=6)
        self.preview_lines.delete(0, tk.END); self.preview_lines.insert(0, "8")
        self.preview_lines.grid(row=0, column=1, sticky=tk.W, padx=4)

        ttk.Button(action_frame, text="生成预览", command=self.on_generate_preview).grid(row=1, column=0, pady=6, padx=4)
        ttk.Button(action_frame, text="复制预览到剪贴板", command=self.on_copy_preview).grid(row=1, column=1, pady=6, padx=4)
        ttk.Button(action_frame, text="保存到文件", command=self.on_save_file).grid(row=1, column=2, pady=6, padx=4)
        ttk.Button(action_frame, text="统计分布", command=self.on_show_stats).grid(row=2, column=0, pady=6, padx=4)

        # -------------- 右侧预览区 --------------
        preview_frame = ttk.LabelFrame(right, text="预览 / 输出")
        preview_frame.pack(fill=tk.BOTH, expand=True)

        self.preview_text = tk.Text(preview_frame, wrap=tk.NONE, font=("Consolas", 10))
        self.preview_text.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        # 字体 fallback on some systems:
        try:
            self.preview_text.configure(font=("Consolas", 11))
        except Exception:
            pass

        vsb = ttk.Scrollbar(preview_frame, orient=tk.VERTICAL, command=self.preview_text.yview)
        vsb.pack(side=tk.RIGHT, fill=tk.Y)
        self.preview_text.configure(yscrollcommand=vsb.set)

        # 值分布统计
        stats_frame = ttk.LabelFrame(right, text="值分布统计 (0–255)")
        stats_frame.pack(fill=tk.BOTH, expand=True)

        self.fig = Figure(figsize=(6, 2.5), dpi=100)
        self.ax = self.fig.add_subplot(111)
        self.ax.set_title("还未生成统计")
        self.ax.set_xlabel("字节值")
        self.ax.set_ylabel("频率")

        self.canvas = FigureCanvasTkAgg(self.fig, master=stats_frame)
        self.canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

        # 下方进度条与信息
        bottom_frame = ttk.Frame(self)
        bottom_frame.pack(fill=tk.X, padx=pad, pady=(0,pad))
        self.progress = ttk.Progressbar(bottom_frame, orient=tk.HORIZONTAL, length=400, mode='determinate')
        self.progress.pack(side=tk.LEFT, padx=(0,10))
        self.status_label = ttk.Label(bottom_frame, text="就绪")
        self.status_label.pack(side=tk.LEFT)

    # ---------- UI 操作 ----------
    def collect_parameters(self, for_preview=False):
        """
        从 UI 读取参数并做最基本校验，返回 dict 或抛出错误（messagebox）
        for_preview: 如果 True，可按预览限制自动缩减 total_values
        """
        try:
            bpv = int(self.bytes_per_value.get())
            if not (1 <= bpv <= 8):
                raise ValueError
        except Exception:
            messagebox.showerror("参数错误", "每个值占字节数必须是 1 到 8 的整数。")
            raise

        try:
            total_values = int(self.total_values_var.get())
            if total_values < 1:
                raise ValueError
        except Exception:
            messagebox.showerror("参数错误", "总值数量必须是正整数。")
            raise

        try:
            per_line = int(self.values_per_line.get())
            if per_line < 1:
                raise ValueError
        except Exception:
            messagebox.showerror("参数错误", "每行多少值必须是正整数。")
            raise

        sep = sanitize_separator(self.sep_entry.get())

        pattern = self.pattern_mode.get()
        try:
            start = int(self.start_value.get()) if self.start_value.get() != "" else 0
        except Exception:
            messagebox.showerror("参数错误", "起始值必须是整数。"); raise
        try:
            step = int(self.step_value.get()) if self.step_value.get() != "" else 1
        except Exception:
            messagebox.showerror("参数错误", "步长必须是整数。"); raise
        try:
            fixed = int(self.fixed_value.get()) if self.fixed_value.get() != "" else 0
        except Exception:
            messagebox.showerror("参数错误", "固定值必须是整数。"); raise

        if for_preview:
            # 限制预览的最大值数量，避免太大
            max_preview_values = int(self.preview_lines.get()) * per_line
            total_values_preview = min(total_values, max_preview_values)
            total_values_to_use = total_values_preview
        else:
            total_values_to_use = total_values

        params = {
            'output_mode': self.output_mode.get(),  # 'text'|'binary'
            'value_format': self.value_format.get(),  # 'hex'|'bin'|'dec'|'ascii'
            'bytes_per_value': bpv,
            'total_values': total_values_to_use,
            'values_per_line': per_line,
            'sep': sep,
            'pattern': pattern,
            'start': start,
            'step': step,
            'fixed': fixed,
            'hex_upper': self.hex_upper.get(),
            'hex_prefix': self.hex_prefix.get(),
            'little_endian': (self.endianness.get() == 'little'),
        }
        return params

    def on_generate_preview(self):
        try:
            params = self.collect_parameters(for_preview=True)
        except Exception:
            return
        # 生成 preview
        preview_text = self.generate_preview_text(params)
        self.preview_text.delete('1.0', tk.END)
        self.preview_text.insert(tk.END, preview_text)
        self.status_label.config(text=f"预览显示 {params['total_values']} 个值（前 {self.preview_lines.get()} 行）")

    def on_copy_preview(self):
        txt = self.preview_text.get('1.0', tk.END)
        if not txt.strip():
            messagebox.showinfo("复制失败", "当前没有预览内容可复制，请先生成预览。")
            return
        self.clipboard_clear()
        self.clipboard_append(txt)
        messagebox.showinfo("已复制", "预览内容已复制到剪贴板。")

    def on_save_file(self):
        try:
            params = self.collect_parameters(for_preview=False)
        except Exception:
            return

        # 选择文件
        if params['output_mode'] == 'binary':
            fpath = filedialog.asksaveasfilename(defaultextension=".bin", filetypes=[("Binary files","*.bin"), ("All files","*.*")])
            if not fpath:
                return
            try:
                self.save_binary_file(fpath, params)
            except Exception as e:
                messagebox.showerror("保存失败", f"写入文件过程中出错：{e}")
                self.status_label.config(text="保存失败")
                return
        else:
            fpath = filedialog.asksaveasfilename(defaultextension=".txt", filetypes=[("Text files","*.txt"), ("Hex/Text files","*.hex;*.txt"), ("All files","*.*")])
            if not fpath:
                return
            try:
                self.save_text_file(fpath, params)
            except Exception as e:
                messagebox.showerror("保存失败", f"写入文件过程中出错：{e}")
                self.status_label.config(text="保存失败")
                return

        messagebox.showinfo("保存完成", f"已保存到：\n{fpath}")
        self.status_label.config(text=f"已保存：{os.path.basename(fpath)}")

    def on_show_stats(self):
        try:
            params = self.collect_parameters(for_preview=False)
        except Exception:
            return

        total = params['total_values']
        bpe = params['bytes_per_value']
        little_endian = params['little_endian']

        # 限制最大统计数，避免内存耗尽
        max_samples = min(total, 200000)  # 最多统计 20 万个值
        gen = value_generator(params['pattern'], bpe, max_samples,
                              start=params['start'], step=params['step'], fixed_value=params['fixed'])

        # 按字节统计 0–255 分布
        freq = np.zeros(256, dtype=np.int64)
        for v in gen:
            b = int_to_bytes_le_be(v, bpe, little_endian)
            for byte in b:
                freq[byte] += 1

        # 更新绘图
        self.ax.clear()
        self.ax.bar(range(256), freq, width=1.0)
        self.ax.set_title(f"前 {max_samples} 个值的字节分布")
        self.ax.set_xlabel("字节值 (0–255)")
        self.ax.set_ylabel("频率")
        self.canvas.draw()

        self.status_label.config(text=f"统计完成：采样 {max_samples} 个值")

    # ---------- 生成文本预览（不写到磁盘） ----------
    def generate_preview_text(self, params):
        """
        根据 params 生成用于显示的文本（前 N 行 / 前 M 个值）
        """
        gen = value_generator(params['pattern'], params['bytes_per_value'], params['total_values'],
                              start=params['start'], step=params['step'], fixed_value=params['fixed'])
        lines = []
        per_line = params['values_per_line']
        sep = params['sep']
        fmt = params['value_format']
        bpe = params['bytes_per_value']
        hex_upper = params['hex_upper']
        hex_prefix = params['hex_prefix']
        little_endian = params['little_endian']

        cur = []
        count = 0
        for v in gen:
            s = format_value_text(v, bpe, fmt, hex_upper=hex_upper, hex_prefix=hex_prefix, little_endian=little_endian)
            cur.append(s)
            count += 1
            if count % per_line == 0:
                lines.append(sep.join(cur))
                cur = []
        if cur:
            lines.append(sep.join(cur))
        return "\n".join(lines)

    # ---------- 保存为文本文件（格式化后写入） ----------
    def save_text_file(self, path, params):
        total = params['total_values']
        per_line = params['values_per_line']
        sep = params['sep']
        fmt = params['value_format']
        bpe = params['bytes_per_value']
        hex_upper = params['hex_upper']
        hex_prefix = params['hex_prefix']
        little_endian = params['little_endian']

        chunk_lines = []
        written_values = 0
        buffer_limit = 4096  # 行缓冲后再写入（约）
        self.progress['maximum'] = total
        self.progress['value'] = 0
        self.status_label.config(text=f"写入文本到 {os.path.basename(path)} ...")
        self.update_idletasks()

        with open(path, 'w', encoding='utf-8', newline='\n') as f:
            gen = value_generator(params['pattern'], bpe, total, start=params['start'], step=params['step'], fixed_value=params['fixed'])
            cur_vals = []
            for v in gen:
                cur_vals.append(format_value_text(v, bpe, fmt, hex_upper=hex_upper, hex_prefix=hex_prefix, little_endian=little_endian))
                written_values += 1
                if written_values % per_line == 0:
                    chunk_lines.append(sep.join(cur_vals))
                    cur_vals = []

                # flush buffer periodically
                if len(chunk_lines) >= buffer_limit:
                    f.write("\n".join(chunk_lines) + "\n")
                    chunk_lines = []
                    self.progress['value'] = written_values
                    self.update_idletasks()

            if cur_vals:
                chunk_lines.append(sep.join(cur_vals))
            if chunk_lines:
                f.write("\n".join(chunk_lines) + "\n")
            self.progress['value'] = total
            self.update_idletasks()

    # ---------- 保存为二进制文件（按 bytes 写入） ----------
    def save_binary_file(self, path, params):
        total = params['total_values']
        bpe = params['bytes_per_value']
        little_endian = params['little_endian']

        self.progress['maximum'] = total
        self.progress['value'] = 0
        self.status_label.config(text=f"写入二进制到 {os.path.basename(path)} ...")
        self.update_idletasks()

        chunk_bytes = []
        written_values = 0
        buffer_limit = 4096  # 值数达到后 flush
        with open(path, 'wb') as f:
            gen = value_generator(params['pattern'], bpe, total, start=params['start'], step=params['step'], fixed_value=params['fixed'])
            for v in gen:
                b = int_to_bytes_le_be(v, bpe, little_endian)
                chunk_bytes.append(b)
                written_values += 1
                if len(chunk_bytes) >= buffer_limit:
                    f.write(b''.join(chunk_bytes))
                    chunk_bytes = []
                    self.progress['value'] = written_values
                    self.update_idletasks()
            if chunk_bytes:
                f.write(b''.join(chunk_bytes))
            self.progress['value'] = total
            self.update_idletasks()

# ---------- 启动 ----------
def main():
    app = TestDataGeneratorApp()
    app.mainloop()

if __name__ == "__main__":
    main()
