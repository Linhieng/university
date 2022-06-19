import math

points = [(2, 3), (10, 1), (3, 25), (23, 15), (18, 3), (8, 9), (12, 30), (25, 30), (9, 2), (13, 10), (3, 4), (5, 6),
          (22, 32), (5, 32), (23, 9), (19, 25), (14, 1), (11, 25), (26, 26), (12, 9), (18, 9), (27, 13), (32, 13)]

# 计算一个坐标系中两个点的欧拉距离, a b 是坐标值, 用数组表示
def distance(a, b):
    return math.sqrt( math.pow( (a[0]-b[0]), 2 ) + math.pow( a[1]-b[1], 2 ) )

def sort_y(tuples):
    return sorted( tuples, key=lambda last : last[-1] )

# 点数小于 3 时, 直接计算(穷举)最小距离, 效率更高
def brute_force(X, n):
    min_d = distance(X[0], X[1])    # 初始化一个最小距离
    for i, (x, y) in enumerate(X):  # 分别取出每一个点
        for j in range(i+1, n):     # 将该点与其他每一个点都进行计算距离
            if distance(X[i], X[j]) < min_d:    # 若找到距离更小的两个点, 则更新最小距离
                min_d = distance(X[i], X[j])
    return min_d

# 处理边界内的最小点对
def strip_closest(strip, d):
    min_d = d
    for i, (x, y) in enumerate(strip):
        for j in range(i+1, 8): # 根据数学原理, 只需要考虑 7 个点
            if i + j < len(strip):  # 防止数据越界
                tem_dis = distance(strip[i], strip[j])  # 计算欧拉距离
                if tem_dis < min_d: # 存储最小的最小距离
                    min_d = tem_dis
    return min_d

# 使用分支算法计算最小距离点对
def closet_pair(X, Y, n):
    if n <= 3:
        return brute_force(X, n)
    mid = int(n / 2)    # 要强制转换为 int 类型
    Y_left = []     # Y_left 是为直线 L 左边的所有点, 且它的 Y 轴坐标值依次增大
    Y_right = []    # Y_right 是直线 L 右边的所有点, 且它的 Y 轴坐标依次增大
    for p in Y:     # 对 Y_right 和 Y_left 进行初始化: 计算哪些是 Y_left 哪些点是 Y_right
        if p in X[:mid]:
            Y_left.append(p)
        else:
            Y_right.append(p)
    dis_left = closet_pair(X[:mid], Y_left, mid)    # 递归处理直线 L 左边的点, 选出左区域内距离最小的点距离
    dis_right = closet_pair(X[mid:], Y_right, mid)  # 递归处理直线 L 右边的点, 选择右区域内距离最小的点距离
    min_dis = min(dis_left, dis_right)  # 选出左右两个区域中距离最小的点
    strip = []  # 存储直线 L 附件的点对
    for (x, y) in Y:
        if abs(x - X[mid][0]) < min_dis:    # 只考虑范围在 L+min_dis L-min_dis 之间的点
            strip.append((x, y))
    return min(min_dis, strip_closest(strip, min_dis))  # 看看跨界(一个点在左边一个点在右边)之间的最小距离点对是否有比 min_dis 更小的

# 使用穷举算法, 时间复杂度是 n^2, X 是点的集合, n 是点的数量
def experiment01(P, n):
    X = list(P) # list 是数组
    Y = list(P)
    X.sort()    # 预处理, 先对点集按照 X 轴进行排序, 排序的目的是提高算法效率
    Y = sort_y(Y)    # 同上, 对点集按照 Y 轴进行排序
    return closet_pair(X, Y, n) # 计算最小距离点对

if __name__ == '__main__':
    print(experiment01(points, len(points)))
