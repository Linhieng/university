class solution(object):
    maxsum = 0
    maxIJ = [[0 for i in range(7)] for i in range(7)]
    ij = [[0, 0, 0, 0, 1, 1, 0], [0, 1, 1, 0, 1, 1, 0], [0, 1, 1, 0, 0, 0, 0], [0, 0, 1, 0, 0, 1, 1], [0, 0, 0, 0, 0, 0, 0], [0, 0, 1, 1, 0, 0, 0], [0, 0, 0, 1, 0, 0, 1]]

    def maxAreaOfIsland(self, grid):
        row = len(grid)  # 地图的行数
        col = len(grid[0])  # 地图的列数
        for i in range(row):
            for j in range(col):
                if grid[i][j] == 1:
                    current = 1
                    self.dfs(i, j, current, grid)  # 测量岛屿的面积
        printfIJ(self.maxIJ)
        return self.maxsum

    def dfs(self, i, j, current, grid):
        grid[i][j] = 2  # 先标记此处已访问
        self.ij[i][j] = '*'
        if i > 0 and grid[i - 1][j] == 1:  # 上
            self.ij[i][j] = '*'
            current = self.dfs(i - 1, j, current + 1, grid)
        if i < len(grid) - 1 and grid[i + 1][j] == 1:  # 下
            self.ij[i][j] = '*'
            current = self.dfs(i + 1, j, current + 1, grid)
        if j > 0 and grid[i][j - 1] == 1:  # 左
            self.ij[i][j] = '*'
            current = self.dfs(i, j - 1, current + 1, grid)
        if j < len(grid[0]) - 1 and grid[i][j + 1] == 1:  # 右
            self.ij[i][j] = '*'
            current = self.dfs(i, j + 1, current + 1, grid)
        if (self.maxsum < current):
            self.maxsum = current
            self.maxIJ = self.ij
            self.ij = [[0, 0, 0, 0, 1, 1, 0], [0, 1, 1, 0, 1, 1, 0], [0, 1, 1, 0, 0, 0, 0], [0, 0, 1, 0, 0, 1, 1], [0, 0, 0, 0, 0, 0, 0], [0, 0, 1, 1, 0, 0, 0], [0, 0, 0, 1, 0, 0, 1]]

        return current


def printfIJ(ij):
    for i in range(7):
        for j in range(7):
            print(ij[i][j], ' ', end="")
        print()


def experiment04():
    grid = [[0, 0, 0, 0, 1, 1, 0],
            [0, 1, 1, 0, 1, 1, 0],
            [0, 1, 1, 0, 0, 0, 0],
            [0, 0, 1, 0, 0, 1, 1],
            [0, 0, 0, 0, 0, 0, 0],
            [0, 0, 1, 1, 0, 0, 0],
            [0, 0, 0, 1, 0, 0, 1]]
    print(solution().maxAreaOfIsland(grid))


if __name__ == '__main__':
    experiment04()