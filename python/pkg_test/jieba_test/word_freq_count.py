import jieba
from jieba import analyse
from os import path

cur_path = path.dirname(__file__)  # 获取当前脚本路径
text_path = 'C000008/10.txt'  # 设置要分析的文本路径
text = open(path.join(cur_path, text_path), "r").read()
text = text.rstrip()  # 清除文本后边空白符
text = text[10:]   # 清除前边格式内容


# input_text : 输入的文本（已经处理好）
# topN ： 输出出现次数最高的 N 个词汇的词频，以及与最大词频之比
def word_freq_count(input_text, topN):
    print("------此文档：合计有{}个字符------".format(len(input_text)))
    dic = {}

    # jieba 分词
    cut_words = jieba.cut(input_text, cut_all=False, HMM=True)

    # 取出分词结果中字长大于 1 的词并统计，统计结果
    for word in cut_words:
        if len(word) == 1:
            continue   # 字长为1的去掉
        if word in dic:
            dic[word] += 1  # 计数加一
        else:
            dic[word] = 1  # 字典没有则添加

    dic = list(dic.items())  # 将 items() 返回的元组转换为列表

    dic.sort(key=lambda x: x[1], reverse=True)  # lambda 对第二维数据排序

    # 输出统计结果
    print("num    words          times     wf_ratio")
    print("----------------------------------------")
    for i in range(topN):  # 对出现次数最多的前 topN 个 词汇进行遍历统计
        word = dic[i][0]  # 被统计词汇
        count = dic[i][1]   # 词汇出现的次数
        wf_ratio = dic[i][1]/dic[0][1]  # 词频/最大词频
        print("{:<5}{:<10}{: ^10}{:>5}".format(i+1, word, count, wf_ratio))


if __name__ == '__main__':
    word_freq_count(text, 20)  # 统计文本 text 中前 20 个词频最高的词汇的情况


