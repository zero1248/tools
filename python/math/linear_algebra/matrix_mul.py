# -*- coding: utf-8 -*-

import numpy as np


# 矩阵乘法运算
# a = np.array([[0, 0, 3],
#               [0, 2, 0],
#               [1, 0, 0]])
# a = np.array([[0, 0, 0, 5],
#               [0, 0, 4, 0],
#               [0, 2, 0, 0],
#               [2, 0, 0, 0]])
a = np.array([[0, 0, 0, 0],
              [1, 0, 0, 0],
              [0, 2, 0, 0],
              [0, 0, 3, 0]])
# a = np.array([[0, 1, 2, 3, 0],
#               [0, 3, 4, 5, 0],
#               [0, 0, 2, 6, 0],
#               [0, 0, 0, 1, 0],
#               [0, 0, 0, 0, 0]])

# b = np.array([[1, 2],
#               [3, 1]])
# print(np.dot(a, b))

# c = np.dot(a, a)
# print(c, end='\n\n')
# print(np.dot(c, a))

b = np.dot(a, a)
print(b)
print(np.dot(a, b))