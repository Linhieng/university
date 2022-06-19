#include <stdio.h>
#include <malloc.h>
#define INF 32767 // 无穷大
#define MAXV 100 // 最大顶点个数
typedef char InfoType;
// 顶点结构体
typedef struct {
    int no; // 顶点编号
    InfoType info; // 顶点其他信息
} VertexType;
// 邻接矩阵结构体
typedef struct {
    int edges[MAXV][MAXV]; // 邻接矩阵数组
    int n, e; // 顶点数、边数 
    VertexType vexs[MAXV];
} MatGraph;
// 边结点结构体
typedef struct ANode {
    int adjvex; // 该边的邻接点编号
    struct Anode * nextarc; // 指向下一条边的指针
    int weight; // 该边的其他信息，比如权值
} ArcNode;
// 邻接表头结点结构体
typedef struct Vnode {
    InfoType info; // 顶点的其他信息
    int count; // 存放顶点的入度（仅仅用于拓扑排序）
    ArcNode * firstarc; // 指向第一个边
} VNode;
// 完整的图邻接表类型
typedef struct {
    VNode adjlist[MAXV]; // 邻接表头结点数组
    int n, e; // 图中顶点数 n 和 边数 e
} AdjGraph;

/* ==========邻接矩阵的基本运算方法========== */

// 创建图的邻接矩阵
void CreateMat (MatGraph *g, int A[MAXV][MAXV], int n, int e) {
    int i, j;
    g->n = n;
    g->e = e;
    for (i = 0; i < n; i++) 
        for (j = 0; j < n; j++)
            g->edges[i][j] = A[i][j];
}
// 输出邻接矩阵 g
void DispMat (MatGraph g) {
    int i, j;
    for (i = 0; i < g.n; i++) {
        for (j = 0; j < g.n; j++) 
            if (g.edges[i][j] != INF)
                printf("\t%d", g.edges[i][j]);
            else
                printf("\t%s", "∞");
        printf("\n");
    }
}

/* ==========图的最短路径佛洛依德算法========== */
int A[MAXV][MAXV];
int path[MAXV][MAXV];

// 佛洛依德算法算出最短路径
void Floyd (MatGraph g) {
    int i, j, k;
    for (i = 0; i < g.n; i++)
        for (j = 0; j < g.n; j++) {
            A[i][j] = g.edges[i][j];
            if (i != j && g.edges[i][j] < INF)
                path[i][j] = i;
            else    
                path[i][j] = -1;
        }
    for (k = 0; k < g.n; k++) {
        for (i = 0; i < g.n; i++)
            for (j = 0; j < g.n; j++)
                if (A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = path[k][j];
                }
    }
}

// 输出最短路径
void shortPath (MatGraph g, int begin, int end, int pathArr[]) {
    // 佛洛依德算法求出所有的最短路径
    Floyd(g);

    int k, s, apath[MAXV], d;

    k = path[begin][end];
    d = 0;
    apath[d] = end;
    while (k != -1 && k != begin) {
        d++;
        apath[d] = k;
        k = path[begin][k];
    }
    d++;
    apath[d] = begin;
    
    k = 0;
    pathArr[k++] = apath[d];
    for (s = d-1; s >= 0; s--) 
        pathArr[k++] = apath[s];
    
    // -1 作为标识，后面再存放一个该路径总权值
    pathArr[k++] = -1;
    pathArr[k] = A[begin][end];

}


