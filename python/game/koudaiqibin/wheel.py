import tkinter as tk
import random
import math

class WheelApp:
    def __init__(self, root):
        self.root = root
        self.root.title("转盘程序")

        self.entries = []  # 初始为空，用户可修改
        self.angle = 0  # 当前转盘角度
        self.running = False

        # 画布
        self.canvas = tk.Canvas(root, width=400, height=400, bg="white")
        self.canvas.pack(pady=10)

        # 输入框和按钮
        frame = tk.Frame(root)
        frame.pack()

        self.entry = tk.Entry(frame, width=20)
        self.entry.pack(side=tk.LEFT, padx=5)
        tk.Button(frame, text="添加条目", command=self.add_entry).pack(side=tk.LEFT)

        # 初始条目输入
        self.init_entry = tk.Entry(root, width=40)
        self.init_entry.pack(pady=5)
        self.init_entry.insert(0, "用逗号分隔初始条目，例如: A,B,C")
        tk.Button(root, text="设置初始条目", command=self.set_initial_entries).pack()

        tk.Button(root, text="开始", command=self.start_spin).pack(pady=10)

        self.result_label = tk.Label(root, text="")
        self.result_label.pack()

        self.draw_wheel()

    def set_initial_entries(self):
        text = self.init_entry.get().strip()
        if text:
            self.entries = [t.strip() for t in text.split(',') if t.strip()]
            self.draw_wheel()

    def add_entry(self):
        text = self.entry.get().strip()
        if text:
            self.entries.append(text)
            self.entry.delete(0, tk.END)
            self.draw_wheel()

    def draw_wheel(self):
        self.canvas.delete("all")
        n = len(self.entries)
        if n == 0:
            return

        angle_per = 360 / n
        for i, text in enumerate(self.entries):
            start = i * angle_per + self.angle
            color = "#%06x" % random.randint(0, 0xFFFFFF)
            self.canvas.create_arc(50, 50, 350, 350, start=start, extent=angle_per,
                                   fill=color, outline="black")

            # 文字位置
            rad = math.radians(start + angle_per / 2)
            x = 200 + 100 * math.cos(rad)
            y = 200 - 100 * math.sin(rad)
            self.canvas.create_text(x, y, text=text)

        # 指针
        self.canvas.create_polygon(190, 10, 210, 10, 200, 40, fill="red")

    def start_spin(self):
        if self.running or not self.entries:
            return
        self.running = True
        self.speed = random.randint(20, 30)  # 初始速度
        self.spin()

    def spin(self):
        if self.speed > 0:
            self.angle += self.speed
            self.angle %= 360
            self.draw_wheel()
            self.speed -= 0.2  # 减速
            self.root.after(50, self.spin)
        else:
            self.running = False
            self.show_result()

    def show_result(self):
        n = len(self.entries)
        angle_per = 360 / n
        # 指针固定在 90 度（上方），找到对应条目
        idx = int(((360 - self.angle + 90) % 360) // angle_per)
        result = self.entries[idx]
        self.result_label.config(text=f"结果: {result}")


if __name__ == "__main__":
    root = tk.Tk()
    app = WheelApp(root)
    root.mainloop()
