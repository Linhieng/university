
# all_weight 背包最大称重, wei_arr 是物品重量, va_arr 是物品价格
def max_value(all_weight, wei_arr, va_arr):
    # 从横轴看是物品一定, 重量不断增加; 从纵轴看是重量一定, 物品不断增加.
    dp = [[0 for _ in range(all_weight + 1)] for _ in range(len(va_arr) + 1)]

    # 不需要考虑物品为 0 和 重量为 0 的情况, 故循环不从 0 开始
    for i in range(1, len(va_arr) + 1):  # 物品不断增加
        for w in range(1, all_weight + 1):  # 物品一定时, 重量不断增加, 计算最大价值
            if w < wei_arr[i-1]:  # 背包重量不足以放下当前物品
                dp[i][w] = dp[i-1][w]   # 最大价值不变(未放入此物品时的价值)
            else:   # 背包重量足以放下当前物品, 考虑两种情况: 可以全部放下; 不可以全部放下.
                dp[i][w] = max(  # 两种情况: 放入新物品; 不放入新物品.
                    va_arr[i - 1]  # 放入新物品
                    # w - wei_arr[i - 1] 是放入新物品后剩余空间
                    # dp[i - 1][w - wei_arr[i - 1]] 是剩余空间能够拥有的最大价值
                    # 故这里处理的是这两种情况: 可以全部放下; 不可以全部放下.
                    + dp[i - 1][w - wei_arr[i - 1]],
                    dp[i - 1][w],  # 不放入新物品
                )
    return dp


# n 是物品数量, c 是最大承重, w_arr 是物品重量数组, max_v 是最大价值数组
def show(n, bearing, w_arr, max_v):
    name = ['足球', '旱冰鞋', '随身听', '单词本']
    print('最大价值为:', max_v[n][bearing])
    x = [False for _ in range(n)]
    for i in range(n, 0, -1):
        # 当最大价值发生变化时, 说明取出的物品肯定发生了变化
        # 而能发生变化的情况, 就是因为放入了 max_v[i-1] 这个物品
        # 为什么呢? 因为 max_value 中有这么一条语句 dp[i][w] = max(va_arr[i - 1] + dp[i - 1][w - wei_arr[i - 1]], dp[i - 1][w])
        # 最大价值变化就是由这条语句引起的, 当它放入新物品时, 最大价值发生变化.
        # 所以在这里我们可以逆推, 取出它放入的新物品 —— x[i - 1]
        if max_v[i][bearing] > max_v[i - 1][bearing]:
            x[i - 1] = True
            bearing -= w_arr[i - 1]
    print('背包中所装物品为: ', end='')
    for i in range(n):
        if x[i]:
            print(name[i], ' ', end='')


def experiment04():
    res = max_value(9, [2, 4, 5, 3], [5, 4, 6, 2])
    show(4, 9, [2, 4, 5, 3], res)


if __name__ == '__main__':
    experiment04()

