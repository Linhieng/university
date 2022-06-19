#include "myconfig.c"

// 初始显示背景信息
void menu() {
    puts("");
    println("基于弗洛伊德算法的最短路径问题研究");
    puts("");
    println("考古学家在沙漠中，");
    println("需要一个中转站到达另外一个中转站。");
    println("因为考古学家们身上携带的资源有限，");
    println("而且沙漠的天气状况随时可能变化，");
    println("所以需要考古学家们尽可能的节省资源和时间，");
    println("以求早日到达另外一个中转站。");
    puts("");
    println("现在由你定下考古学家们的两个中转站地点");
    puts("");
}

// 让用户选择起点和终点
void selectPath (int *b, int *e) {
    char begin;
    char end;

    print("\t沙漠地图如下，请选择起点和终点\n", TRUE, GREEN|INTENSITY, BLACK);
    char i = 65; // 'A'
    int line, row;
    line = row = 4;

    // 画出 4×4 的地图
    setColor(YELLOW, BLACK);
    while (line--) {
        row = 4;
        printf("\t");
        while (row--)
            printf("%c ", i++);
        printf("\n");        
    }
    renewColor();

    printf("\t输入起点：");
    begin = getche();
    while (errorPath(begin)) {
        printf("\n\t请重新输入起点：");
        begin = getche();  
    }

    printf("\n\t输入终点：");
    end = getche();
    while (errorPath(end) || begin == end || !((begin - end)%32)) {
        if (begin == end || !((begin - end)%32))
            printf("\n\t起点终点不能相同");
        printf("\n\t请重新输入终点：");
        end = getche();  
    }

    // 将 char 变为对应的 int，'a'='A'= 0, 
    *b = (begin < 'a'? begin - 'A' : begin - 'a');
    *e = (end   < 'a'? end   - 'A' : end   - 'a');

    printf("\n\t你输入的起点是 %c, 输入的终点是 %c\n", begin, end);
}

// 显示一个 4×4 的地图
void displayMap (int begin, int end) {
    
    int line, row, l, r;
    line = row = 4;
    // 起点和终点的坐标 (row,line)
    int l1 = begin/line, r1 = begin%4;
    int l2 = end/line, r2 = end%4;

    for (l = 0; l < line; l++) {
        printf("\t");
        for (r = 0; r < row; r++) {
            if (r == r1 && l == l1)
                print(" 始 ", TRUE, RED | INTENSITY, BLACK);
            else if (r == r2 && l == l2) 
                print(" 终 ", TRUE, RED | INTENSITY, BLACK);
            else 
                print(" 点 ", TRUE, YELLOW, BLACK);
        }
        puts("");
    }
    puts("");
}

// 为 weight 数组随机设置权值
void randWeight () {
    int i, j;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 4; j++)
            weight[i][j] = getRand(1,9)+'0';
}

// 生成权值并且计算各个点之间的最短路径
void initGraph (MatGraph *g) {
    // A 邻接矩阵
    int A[MAXV][MAXV];
    // x 代表地图的图形是一个 4 × 4 的点线图
    // n 是 顶点数，e 是边数
    int x = 4;
    int n = x*x, e = 2*x*(x-1);
    // 权值初始化, k, wi 用于 weight[wi][k]
    int i, j, k, wi;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) 
            A[i][j] = (i == j? 0 : INF);

    // 为 weight 随机设置权值，范围是 1-9
    randWeight();

    // 将 weight 中的权值对应到 A 中
    for (i = 0, wi = 0; i < 13; i+=4, wi+=2) {
        for (j = i, k = 0; j < i+4; j++, k++) {
            A[j][j+4] = A[j+4][j] = weight[wi+1][k]-'0';
            if (j != i+3)
                A[j][j+1] = A[j+1][j] = weight[wi][k]-'0';
        }
    }    
    
    // 生成邻接矩阵，用于计算最短路径
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
    int row = 7;
    int i,j,k;

    for (i = 0, k = 0; i < 4; i++, k++) {
        printf("\t");
        for (j = 0; j < row; j++) 
            printf("%c%s", j%2? weight[k][j/2]:point[i][j/2], j+1!=row? "----":"");
        if (i+1 != 4) {
            printf("\n\t:         :         :         :\n\t");
            k++;
            for (j = 0; j < 4; j++)
                printf("%c%s", weight[k][j], i+1 != 4? "         " : "");
            printf("\n\t:         :         :         :\n");
        }
    }

}

// 显示最终路径图
void displayPath (int path[]) {
    print("\n\t最终路径图如图所示\n", TRUE, GREEN | INTENSITY, BLACK);
    int line, row;
    line = row = 4;
    int l, r;
    int num = 0; // 第一个点
    int index; // path 下标
    for (l = 0; l < line; l++) {
        printf("\t");
        for (r = 0; r < row; r++) {
            // if (num == path[index]) {
            if (includeNum(path, num, &index)) {
                setColor(WHITE | INTENSITY, RED);
                printf(" %d ", index);
                renewColor();
                index++;
            } else
                print(" X ", TRUE, YELLOW, BLACK);
            num++;
        }
        print("\n", FALSE);
    }
    print("\n", FALSE);
}

//计算物资的消耗 
void ResourceCost(int days){
	//定义天气系统规则
	int weather[10]={2,2,1,3,1,2,3,1,2,2};//天气的情况
	int WaterCost[3]={5,8,10};//3种天气的水消耗量
	int FoodCost[3]={7,6,10};//3种天气的食物消耗量
	int price_w=5;//水的价格/箱
	int price_f=10;//食物的价格/箱
	int sumw=3;//总共需要的水/箱
	int sumf=0;//总共需要的食物/箱 
	int day=0;

	int i=0;
	while(day<days){
		for(i;i<10;i++){
			if(weather[i]!=3){
			day=day+1;//沙暴天气不能走，还要原地待一天 
			sumw=sumw+2*WaterCost[weather[i]];
			sumf=sumf+2*FoodCost[weather[i]];
			}
			else                   //遇到沙暴的情况 
			sumw=sumw+WaterCost[weather[i]];
			sumf=sumf+FoodCost[weather[i]];
		}
		day++;
	}

    printf("\n\t最终需要的水和食物和天数为：");
    printf("\n\t%dkg食物\n",sumf);
    printf("\n\t%dkg水\n",sumw);
    printf("\n\t%d天\n",days);
	
}


int main (void) {

    // system("chcp 65001");
    system("title 数据结构课程设计");

    // 显示问题背景
    menu();

    // 让用户决定起点和终点
    int begin, end;
    selectPath(&begin, &end);
    
    // 显示地图
    displayMap(begin, end);
    
    // 将地图转换成图结构，并为其赋权值和创建邻接矩阵
    MatGraph g;
    initGraph(&g);
    printf("\t地图中点与点之间的权值如下\n");
    displayWeight();

    // 输出最短路径
    int pathArr[16], i = 0;
    shortPath(g, begin, end, pathArr);
    displayPath(pathArr);
    
    // 输出最终需要的天数
    while (pathArr[i++] != -1);
    ResourceCost(pathArr[i]);

    printf("\t程序运行结束，请输入任意键退出......  ");
    getch();
    
    return 0;
}