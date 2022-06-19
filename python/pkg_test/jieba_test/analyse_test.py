# 关键词提取测试

from os import path
import jieba.analyse as analyse

cur_path = path.dirname(__file__)  # 获取当前脚本路径

text_path = 'Book_del_4000/neg/4.txt'  # 设置要分析的文本路径

text = open(path.join(cur_path, text_path)).read()
text = text.rstrip()  # 清楚文本后边空白符
text = text[10:]   # 清除前边格式内容
print(text)
# 使用 jieba.analyse.extract_tags() 参数提取关键字,第二个参数为提取关键字的个数
for key in analyse.extract_tags(text, 5, withWeight=False):
    # 若出现乱码，试试设为 utf-8 编码，即 print(key.encode('utf-8'))
    # 当 withWeight=True 时,将会返回 number 类型的一个权重值(TF-IDF)
    print(key)

# 一行显示 10 个关键字
tags = analyse.extract_tags(text, topK=10)
print(",".join(tags))
