import math

points = [(2, 3), (10, 1), (3, 25), (23, 15), (18, 3), (8, 9), (12, 30), (25, 30), (9, 2), (13, 10), (3, 4), (5, 6),
          (22, 32), (5, 32), (23, 9), (19, 25), (14, 1), (11, 25), (26, 26), (12, 9), (18, 9), (27, 13), (32, 13)]


# 计算一个坐标系中两个点的欧拉距离, a b 是坐标值, 用数组表示
def distance(a, b):
    return math.sqrt( math.pow( (a[0]-b[0]), 2 ) + math.pow( a[1]-b[1], 2 ) )

# 使用穷举算法, 时间复杂度是 n^2, X 是点的集合, n 是点的数量
def experiment01(X, n):
    min_d = distance(X[0], X[1])    # 设一个当前最小的距离
    for i, (x, y) in enumerate(X):  # 从点集中依次取出各个点坐标
        for j in range(i+1, n):     # 对每一个取出的点坐标, 遍历计算她和其他所有点坐标的距离
            if distance(X[i], X[j]) < min_d:    # 如果距离比最小距离还小, 则替换最小距离
                min_p = [X[i], X[j]]    # 记录是哪两个点之间的距离最小
                min_d = distance(X[i], X[j])    # 记录最小的距离
        return min_p, min_d # 返回最小的距离和两个点

if __name__ == '__main__':
    print(experiment01(points, len(points)))
