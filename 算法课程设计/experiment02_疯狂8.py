def generate_cards(n):
    import random
    import itertools
    SUITS = 'cdhs'             #四种花色
    RANKS = '23456789XJQKA'    #十三种面值
    DECK = tuple(''.join(card) for card in itertools.product(RANKS, SUITS))
    hand = random.sample(DECK, n)
    return hand

import numpy as np

def value(x):
    if x == 's': return '♠'
    if x == 'h': return '♥'
    if x == 'c': return '♣'
    if x == 'd': return '♦'
    if x == 'X': return '10'
    return x

def info(ci):
    return '面值: {}, 花色: {}'.format(value(ci[0]), value(ci[1]))

def crazy_eight(cards):
    trick = {}  #
    parent = {}
    trick[0] = 1    # 第一张扑克默认“匹配成功”, 长度为 1
    parent[0] = None    # 第一张扑克没有父结点
    print('第 0 张扑克, ', info(cards[0]))
    for i, ci in enumerate(cards):  # 取出每一张扑克, i 是第几张扑克, ci 是扑克信息数组, 第一个元素是面值, 第二个元素是花色
        tem_trick = []
        if i > 0: # 跳过第一张扑克牌
            print('计算: 当前是第 {} 张扑克, {}'.format(i, info(ci)))
            for j, cj in enumerate(cards[:i]): # 遍历前面所有的牌子
                print('\t 对第 {} 张扑克进行配对, {}'.format(j, info(cj)))
                if is_trick(ci, cj):
                    tem_trick.append(trick[j])  # 配对成功, 纪录下来
                    print('\t\t 匹配成功, 增加了 trick[{}] = {}'.format(j, trick[j]))
                else:
                    tem_trick.append(0)
                    print('\t\t 匹配失败')
                    print('\t\t ', info(ci))
                    print('\t\t ', info(cj))
            # 此轮配对结束, 进行收尾工作
            max_trick = max(tem_trick)
            trick[i] = 1 + max_trick
            print('\n\t ======此轮计算 trick[{}] 结束'.format(i))
            print(  '\t |     trick[{}] = 1+{} = {}'.format(i, max_trick, trick[i]))
            i_m = np.argmax(tem_trick) # 从 tem_trick 中取出最大值所在索引
            print(  '\t |     前面扑克中 trick 最大值: trick[{}] = {}'.format(i_m, trick[int(i_m)]))
            if is_trick(ci, cards[i_m]):    # 配置 parent , parent 作用在于纪录配对最长子序列
                parent[i] = i_m
                print('\t |     第 {} 张扑克 {}'.format(i, info(ci)))
                print('\t |     它的 parent 是第 {} 张扑克, {}'.format(i_m, info(cards[i_m])))
            else:
                parent[i] = None
                print('\t |     此轮结束后还是只有最长配对子序列还是只有一张牌(第 0 张牌)')
            print('\t ==============================')
    return trick, parent

# 判断两张扑克是否配对
def is_trick(c1, c2):
    if c1[0] == c2[0]:  # 满足相同的面值
        return True
    elif c1[1] == c2[1]:    # 满足相同的花色
        return True
    elif c1[0] == '8' or c2[0] == '8':  # 其中一张牌是 8
        return True
    else:   # 其他情况，则说明配对失败
        return False

# 输出最长配对序列的扑克信息
def get_longest_subsequence(cards, trick, parent):
    ind_max = max(trick.keys(), key=(lambda key: trick[key]))
    subsequence = []
    while ind_max is not None:
        subsequence.append(cards[ind_max])
        ind_max = parent[ind_max]
    subsequence.reverse()
    return subsequence

# 输出最终的 trick 信息
def printTrick(trick):
    for i in range(len(trick)):
        print('trick[{}]: '.format(i), trick[i])

# 输出最长配对序列的信息
def printListInfo(sub_cards):
    for _, item in enumerate(sub_cards):
        print(info(item))


def experiment02():
    cards = generate_cards(10)  # 随机生成 10 张扑克牌
    trick, parent = crazy_eight(cards)  # 进行匹配
    print('计算结束, 总结:')
    printTrick(trick)
    sub_cards = get_longest_subsequence(cards, trick, parent)
    printListInfo(sub_cards)

if __name__ == '__main__':
    print(experiment02())
