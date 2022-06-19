# -*- coding: utf-8 -*-

from bashplotlib.scatterplot import plot_scatter
from bashplotlib.histogram import plot_hist
import numpy as np

# 直方图
# arr = np.random.normal(size=1000, loc=0, scale=1)
# plot_hist(arr,bincount=50)

# 散点图
# plot_scatter(None, 'data\\x.txt', 'data\\y.txt', 20, '*', 'red', 'Test')

# 散点图
plot_scatter('data\\texas.txt', None, None, 20, '*', 'red', 'Test')