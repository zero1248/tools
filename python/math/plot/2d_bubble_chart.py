# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure(figsize=(9,6))

# 泡泡的数量
n = 50
size_min = 50
size_max = 50*50

# Ring position,rand可以产生2维数组
P = np.random.rand(n,2)

# Ring colors R,G,B,A
C = np.ones((n,4)) * (0,0,0,1)
# Alpha color channel goes from 0 (transparent) to 1 (opaque)
C[:,3] = np.linspace(0,1,n)

# Ring sizes
S = np.linspace(size_min, size_max, n)

# Scatter plot
plt.scatter(P[:,0], P[:,1], s=S, lw = 1.5,
                  edgecolors = C, facecolors='None')

#range只能排列出整数，在排列小数时可以用到np.arange
plt.xlim(0,1), plt.xticks(np.arange(0,1.1,0.1))
plt.ylim(0,1), plt.yticks(np.arange(0,1.1,0.1))

plt.show()







