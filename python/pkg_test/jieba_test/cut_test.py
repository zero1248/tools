# 分词测试

import jieba

# jieba.cut的默认参数只有三个,jieba 源码如下
# cut(self, sentence, cut_all=False, HMM=True)
# 分别为:输入文本 是否为全模式分词 与是否开启HMM进行中文分词

seg_list = jieba.cut("我来到北京清华大学", cut_all=True, HMM=False)
print("Full Mode: " + "/ ".join(seg_list))  # 全模式

seg_list = jieba.cut("我来到北京清华大学", cut_all=False, HMM=True)
print("Default Mode: " + "/ ".join(seg_list))  # 默认模式

seg_list = jieba.cut("他来到了网易杭研大厦", HMM=False)
print(", ".join(seg_list))   # 搜索引擎模式

seg_list = jieba.cut_for_search("小明硕士毕业于中国科学院计算所，后在日本京都大学深造", HMM=False)
print(", ".join(seg_list))
