#include "main.c"

// 权值
char weight[7][4] = {
    {'1', '2', '1', '*' },
    {'1', '1', '1', '1' },
    {'1', '4', '2', '*' },
    {'1', '2', '1', '1' },
    {'1', '2', '1', '*' },
    {'1', '2', '1', '9' },
    {'1', '1', '1', '*'}
};


// 生成权值并且计算各个点之间的最短路径
void initGraph (MatGraph *g) {
    // A 即权值表
    int A[MAXV][MAXV];

    // x 代表地图的图形是一个 4 × 4 的点线图
    // n 是 顶点数，e 是边数
    int x = 4;
    int n = x*x, e = 2*x*(x-1);
    // 权值初始化
    int i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) 
            A[i][j] = (i == j? 0 : INF);

    // char weight[7][4] = {
    //     {'1', '2', '1', '*' },
    //     {'1', '1', '1', '1' },
    //     {'1', '4', '2', '*' },
    //     {'1', '2', '1', '1' },
    //     {'1', '2', '1', '*' },
    //     {'1', '2', '1', '2' },
    //     {'1', '1', '1', '*'}
    // };
    int wi;

    for (i = 0, wi = 0; i < 13; i+=4, wi+=2) {
        // A[][]
        // 01 12 23  
        // 04 15 36 47 i = 0
        // 45 56 67
        // 48 59 6A 7B i = 4
        // 89 9A AB
        // 8C 9D AE BF i = 8
        // CD DE EF
        for (j = i, k = 0; j < i+4; j++, k++) {
            // 这个 for 循环中会用掉两行 weight
            // 依次是 [0][...] 赋值给 A[][] 01 12 23
            // [1][...] 赋值给 A[][] 04 15 36 47

            // 01 12 23   j = i = 0, A[j][j+1]
            // 04 15 36 47 j = i = 0, A[j][j+4]

            // weight[1][0,1,2,3]
            // weight[3][0,1,2,3]
            // weight[5][0,1,2,3]
            A[j][j+4] = A[j+4][j] = weight[wi+1][k]-'0';
            if (j != i+3)
                // weight[0][0,1,2]
                // weight[2][0,1,2]
                // weight[4][0,1,2]
                // weight[6][0,1,2]
                A[j][j+1] = A[j+1][j] = weight[wi][k]-'0';
        }
    }    
    
    // 生成邻接矩阵
    CreateMat(g, A, n, e);
    // DispMat(*g); // 显示邻接矩阵
}


// 随机生成权值
void initGraph2 (MatGraph *g) {
    // A 即权值表
    int A[MAXV][MAXV];

    // 地图的图形是一个 4 × 4 的点线图
    // n 是 顶点数，e 是边数
    int x = 4;
    int n = x*x, e = 2*x*(x-1);
    // 为点与点之间随机赋值权重
    int i, j, a = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) 
            A[i][j] = (i == j? 0 : INF);
        // a-1 左 要比 a/x*x 大
        // a+1 右 要比 a/x*x+x-1 小
        // a-x 上 要比 (a-x)/x*x 大
        // a+x 下 要比 (a-x)/x*x+x-1 小
        if (a/x*x <= a-1) 
            A[a][a-1] = A[a-1][a] = getRand(1, 9);
        if (a+1 <= a/x*x+x-1) 
            A[a][a+1] = A[a+1][a] = getRand(1, 9);
        if ((a-x)/x*x <= (a-x)) 
            A[a][a-x] = A[a-x][a] = getRand(1, 9);
        if (a+x <= (a+x)/x*x+x-1) 
            A[a][a+x] = A[a+x][a] = getRand(1, 9);
        a++;
    }
    // 生成邻接矩阵
    CreateMat(g, A, n, e);
}

// 显示权值图
void displayWeight () {
    char point[4][4] = {
        {'A', 'B', 'C', 'D'} ,
        {'E', 'F', 'G', 'H'} ,
        {'I', 'J', 'K', 'L'} ,
        {'M', 'N', 'O', 'P'} 
    };
    // char weight[7][4] = {
    //     {'1', '2', '1', '*' },
    //     {'1', '1', '1', '1' },
    //     {'1', '4', '2', '*' },
    //     {'1', '2', '1', '1' },
    //     {'1', '2', '1', '*' },
    //     {'1', '2', '1', '9' },
    //     {'1', '1', '1', '*'}
    // };
    int row = 7;
    int i,j,k;

    for (i = 0, k = 0; i < 4; i++, k++) {
        printf("\t");
        // 输出 A----1----B----2----C----1----D
        for (j = 0; j < row; j++) 
            printf("%c%s", j%2? weight[k][j/2]:point[i][j/2], j+1!=row? "----":"");
        
        // output :         :         :         :
        //        1         1         1         1
        //        :         :         :         :
        if (i+1 != 4) {
            printf("\n\t:         :         :         :\n\t");
            k++;
            for (j = 0; j < 4; j++)
                printf("%c%s", weight[k][j], i+1 != 4? "         " : "");
            printf("\n\t:         :         :         :\n");
        }
    }

}

