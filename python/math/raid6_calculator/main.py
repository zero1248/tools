import tkinter as tk
from tkinter import messagebox

# ---------------------------
# GF(2^8) arithmetic helpers
# ---------------------------
GF_POLY = 0x11d
GF_SIZE = 256

# Build log/exp tables
exp_table = [0] * (GF_SIZE * 2)
log_table = [0] * GF_SIZE

x = 1
for i in range(GF_SIZE - 1):
    exp_table[i] = x
    log_table[x] = i
    x <<= 1
    if x & 0x100:
        x ^= GF_POLY
for i in range(GF_SIZE - 1, GF_SIZE * 2):
    exp_table[i] = exp_table[i - (GF_SIZE - 1)]


def gf_mul(a, b):
    if a == 0 or b == 0:
        return 0
    return exp_table[log_table[a] + log_table[b]]


# ---------------------------
# RAID6 P/Q computation
# ---------------------------
def raid6_compute(data_list):
    # data_list: list of bytearrays
    length = len(data_list[0])
    for d in data_list:
        if len(d) != length:
            raise ValueError("All inputs must have the same length!")

    P = bytearray(length)
    Q = bytearray(length)

    for j in range(length):
        p = 0
        q = 0
        for i, d in enumerate(data_list):
            b = d[j]
            p ^= b
            q ^= gf_mul(b, exp_table[i])  # multiply by α^i
        P[j] = p
        Q[j] = q
    return P, Q


# ---------------------------
# GUI
# ---------------------------
class RAID6App:
    def __init__(self, root):
        self.root = root
        self.root.title("RAID6 P/Q Calculator")
        self.root.geometry("700x600")

        tk.Label(root, text="RAID6 P/Q Calculator", font=("Arial", 18, "bold")).pack(pady=10)

        self.entries = []
        for i in range(8):
            frame = tk.Frame(root)
            frame.pack(pady=3)
            tk.Label(frame, text=f"D{i}:", width=4, anchor="e").pack(side=tk.LEFT)
            entry = tk.Entry(frame, width=80)
            entry.pack(side=tk.LEFT)
            self.entries.append(entry)

        self.btn = tk.Button(root, text="Compute P and Q", font=("Arial", 12, "bold"), command=self.compute)
        self.btn.pack(pady=10)

        self.result_p = tk.Text(root, height=4, width=85)
        self.result_q = tk.Text(root, height=4, width=85)
        tk.Label(root, text="P Value (Hex):").pack()
        self.result_p.pack()
        tk.Label(root, text="Q Value (Hex):").pack()
        self.result_q.pack()

    def compute(self):
        try:
            datas = []
            for entry in self.entries:
                txt = entry.get().strip().replace(" ", "")
                if txt:
                    if len(txt) % 2 != 0:
                        txt = "0" + txt
                    data = bytes.fromhex(txt)
                    if not (1 <= len(data) <= 64):  # 8bit–512bit
                        raise ValueError("Each input must be between 8 and 512 bits (1–64 bytes).")
                    datas.append(bytearray(data))

            if len(datas) < 2:
                messagebox.showerror("Error", "Please input at least two disks (D0 and D1).")
                return

            P, Q = raid6_compute(datas)
            self.result_p.delete("1.0", tk.END)
            self.result_q.delete("1.0", tk.END)
            self.result_p.insert(tk.END, P.hex().upper())
            self.result_q.insert(tk.END, Q.hex().upper())

        except Exception as e:
            messagebox.showerror("Error", str(e))


# ---------------------------
# Run the App
# ---------------------------
if __name__ == "__main__":
    root = tk.Tk()
    app = RAID6App(root)
    root.mainloop()
