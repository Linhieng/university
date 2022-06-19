#include "myconfig.c"

// ��ʼ��ʾ������Ϣ
void menu() {
    puts("");
    println("���ڸ��������㷨�����·�������о�");
    puts("");
    println("����ѧ����ɳĮ�У�");
    println("��Ҫһ����תվ��������һ����תվ��");
    println("��Ϊ����ѧ��������Я������Դ���ޣ�");
    println("����ɳĮ������״����ʱ���ܱ仯��");
    println("������Ҫ����ѧ���Ǿ����ܵĽ�ʡ��Դ��ʱ�䣬");
    println("�������յ�������һ����תվ��");
    puts("");
    println("�������㶨�¿���ѧ���ǵ�������תվ�ص�");
    puts("");
}

// ���û�ѡ�������յ�
void selectPath (int *b, int *e) {
    char begin;
    char end;

    print("\tɳĮ��ͼ���£���ѡ�������յ�\n", TRUE, GREEN|INTENSITY, BLACK);
    char i = 65; // 'A'
    int line, row;
    line = row = 4;

    // ���� 4��4 �ĵ�ͼ
    setColor(YELLOW, BLACK);
    while (line--) {
        row = 4;
        printf("\t");
        while (row--)
            printf("%c ", i++);
        printf("\n");        
    }
    renewColor();

    printf("\t������㣺");
    begin = getche();
    while (errorPath(begin)) {
        printf("\n\t������������㣺");
        begin = getche();  
    }

    printf("\n\t�����յ㣺");
    end = getche();
    while (errorPath(end) || begin == end || !((begin - end)%32)) {
        if (begin == end || !((begin - end)%32))
            printf("\n\t����յ㲻����ͬ");
        printf("\n\t�����������յ㣺");
        end = getche();  
    }

    // �� char ��Ϊ��Ӧ�� int��'a'='A'= 0, 
    *b = (begin < 'a'? begin - 'A' : begin - 'a');
    *e = (end   < 'a'? end   - 'A' : end   - 'a');

    printf("\n\t������������ %c, ������յ��� %c\n", begin, end);
}

// ��ʾһ�� 4��4 �ĵ�ͼ
void displayMap (int begin, int end) {
    
    int line, row, l, r;
    line = row = 4;
    // �����յ������ (row,line)
    int l1 = begin/line, r1 = begin%4;
    int l2 = end/line, r2 = end%4;

    for (l = 0; l < line; l++) {
        printf("\t");
        for (r = 0; r < row; r++) {
            if (r == r1 && l == l1)
                print(" ʼ ", TRUE, RED | INTENSITY, BLACK);
            else if (r == r2 && l == l2) 
                print(" �� ", TRUE, RED | INTENSITY, BLACK);
            else 
                print(" �� ", TRUE, YELLOW, BLACK);
        }
        puts("");
    }
    puts("");
}

// Ϊ weight �����������Ȩֵ
void randWeight () {
    int i, j;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 4; j++)
            weight[i][j] = getRand(1,9)+'0';
}

// ����Ȩֵ���Ҽ��������֮������·��
void initGraph (MatGraph *g) {
    // A �ڽӾ���
    int A[MAXV][MAXV];
    // x �����ͼ��ͼ����һ�� 4 �� 4 �ĵ���ͼ
    // n �� ��������e �Ǳ���
    int x = 4;
    int n = x*x, e = 2*x*(x-1);
    // Ȩֵ��ʼ��, k, wi ���� weight[wi][k]
    int i, j, k, wi;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) 
            A[i][j] = (i == j? 0 : INF);

    // Ϊ weight �������Ȩֵ����Χ�� 1-9
    randWeight();

    // �� weight �е�Ȩֵ��Ӧ�� A ��
    for (i = 0, wi = 0; i < 13; i+=4, wi+=2) {
        for (j = i, k = 0; j < i+4; j++, k++) {
            A[j][j+4] = A[j+4][j] = weight[wi+1][k]-'0';
            if (j != i+3)
                A[j][j+1] = A[j+1][j] = weight[wi][k]-'0';
        }
    }    
    
    // �����ڽӾ������ڼ������·��
    CreateMat(g, A, n, e);
}

// ��ʾȨֵͼ
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

// ��ʾ����·��ͼ
void displayPath (int path[]) {
    print("\n\t����·��ͼ��ͼ��ʾ\n", TRUE, GREEN | INTENSITY, BLACK);
    int line, row;
    line = row = 4;
    int l, r;
    int num = 0; // ��һ����
    int index; // path �±�
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

//�������ʵ����� 
void ResourceCost(int days){
	//��������ϵͳ����
	int weather[10]={2,2,1,3,1,2,3,1,2,2};//���������
	int WaterCost[3]={5,8,10};//3��������ˮ������
	int FoodCost[3]={7,6,10};//3��������ʳ��������
	int price_w=5;//ˮ�ļ۸�/��
	int price_f=10;//ʳ��ļ۸�/��
	int sumw=3;//�ܹ���Ҫ��ˮ/��
	int sumf=0;//�ܹ���Ҫ��ʳ��/�� 
	int day=0;

	int i=0;
	while(day<days){
		for(i;i<10;i++){
			if(weather[i]!=3){
			day=day+1;//ɳ�����������ߣ���Ҫԭ�ش�һ�� 
			sumw=sumw+2*WaterCost[weather[i]];
			sumf=sumf+2*FoodCost[weather[i]];
			}
			else                   //����ɳ������� 
			sumw=sumw+WaterCost[weather[i]];
			sumf=sumf+FoodCost[weather[i]];
		}
		day++;
	}

    printf("\n\t������Ҫ��ˮ��ʳ�������Ϊ��");
    printf("\n\t%dkgʳ��\n",sumf);
    printf("\n\t%dkgˮ\n",sumw);
    printf("\n\t%d��\n",days);
	
}


int main (void) {

    // system("chcp 65001");
    system("title ���ݽṹ�γ����");

    // ��ʾ���ⱳ��
    menu();

    // ���û����������յ�
    int begin, end;
    selectPath(&begin, &end);
    
    // ��ʾ��ͼ
    displayMap(begin, end);
    
    // ����ͼת����ͼ�ṹ����Ϊ�丳Ȩֵ�ʹ����ڽӾ���
    MatGraph g;
    initGraph(&g);
    printf("\t��ͼ�е����֮���Ȩֵ����\n");
    displayWeight();

    // ������·��
    int pathArr[16], i = 0;
    shortPath(g, begin, end, pathArr);
    displayPath(pathArr);
    
    // ���������Ҫ������
    while (pathArr[i++] != -1);
    ResourceCost(pathArr[i]);

    printf("\t�������н�����������������˳�......  ");
    getch();
    
    return 0;
}