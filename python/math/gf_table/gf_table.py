#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Generate GF(2^8) log and exp tables for FPGA use.
Polynomial: x^8 + x^4 + x^3 + x^2 + 1 (0x11d)
Log(0) is defined as 0 for FPGA convenience.
"""

POLY = 0x11d  # GF(2^8) 本原多项式
GF_SIZE = 256

def generate_tables():
    gf_exp = [0] * 512  # 扩展表 512，方便取模255
    gf_log = [0] * GF_SIZE

    x = 1
    for i in range(0, 255):   # 0..254 共 255 个值
        gf_exp[i] = x
        gf_log[x] = i
        x <<= 1
        if x & 0x100:
            x ^= POLY

    # 复制前 255 个元素到后 256~510，用于索引方便
    for i in range(255, 512):
        gf_exp[i] = gf_exp[i - 255]

    # 定义 log(0) = 0
    gf_log[0] = 0

    return gf_log, gf_exp

def save_mem(filename, table):
    with open(filename, "w") as f:
        for v in table:
            f.write(f"{v:02x}\n")

def main():
    gf_log, gf_exp = generate_tables()
    save_mem("gf_log.mem", gf_log)
    save_mem("gf_exp.mem", gf_exp)
    print("GF(2^8) tables generated with polynomial 0x11d: gf_log.mem and gf_exp.mem")

if __name__ == "__main__":
    main()
