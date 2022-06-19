
# n 金矿数量, w 总人数, g 为金矿存储黄金数组, p 为所需工人数组
def max_gold(person, gold, worker):
    dp = [[0] * (person + 1) for _ in range(len(gold) + 1)]

    for i in range(1, len(gold) + 1):
        for j in range(1, person + 1):
            if j < worker[i - 1]:
                dp[i][j] = dp[i - 1][j]
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - worker[i - 1]] + gold[i - 1])
        print(dp[i])
    return dp[len(gold)][person]


def experiment04():
    res = max_gold(16, [500, 300, 100, 300, 350, 350], [6, 5, 6, 4, 3, 3])
    print(res)


if __name__ == '__main__':
    experiment04()