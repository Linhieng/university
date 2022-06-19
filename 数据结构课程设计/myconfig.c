#include <stdio.h>
#include <windows.h>
#include <vadefs.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "graph.c"

// 颜色
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3 // 浅绿色
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define INTENSITY 8 // 高亮
// 布尔类型
#define TRUE 1
#define FALSE 0

typedef int BOOL;

// 默认权值, * 代表该值无效
char weight[7][4] = {
    {'1', '2', '1', '*' },
    {'2', '1', '1', '1' },
    {'1', '4', '2', '*' },
    {'3', '2', '6', '1' },
    {'1', '2', '1', '*' },
    {'6', '2', '1', '9' },
    {'1', '1', '1', '*'}
};

// 以特定颜色输出一段文本, flag 代表是否自定义颜色，默认为黑底白字
void print (char * string, int flag, ...) {
    // 默认颜色
    int color = WHITE;
    int background_color = BLACK;
    // 自定义颜色
    if (flag) {
        va_list pArgs = NULL;
	    va_start(pArgs, flag);
        color = va_arg(pArgs, int);
        background_color = va_arg(pArgs, int);
	    va_end(pArgs);
    }
    HANDLE consolehwnd; //创建句柄
    consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE); //实例化句柄
    SetConsoleTextAttribute(consolehwnd,color | background_color<<4); //设置字体颜色
    printf(string);
    SetConsoleTextAttribute(consolehwnd,WHITE);
}

// 设置后续字体的颜色
void setColor (int color, int background_color) {
    HANDLE consolehwnd; //创建句柄
    consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE); //实例化句柄
    SetConsoleTextAttribute(consolehwnd,color | background_color<<4); //设置字体颜色
}

// 恢复黑底白字
void renewColor () {
    HANDLE consolehwnd; //创建句柄
    consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE); //实例化句柄
    SetConsoleTextAttribute(consolehwnd,WHITE);
}

// 前面加 制表，后面加 换行
void println (char * string) {
    printf("\t");  
    printf(string);
    printf("\n");  
}

// 产生范围在 [a,b] 的伪随机数
int getRand (int a, int b) {
    Sleep(1);
    srand(clock());
    // if (a < b || a < 0 || b < 0)
    return (rand() % (b-a+1)) + a;
}

// 用于判断输入的起点和终点是否错误，错误则返回 1
int errorPath (char c) {
    // 小于 'A' 错误
    // 大于 'p' 错误
    // 小于 'a' 并且 大于 'P' 错误
    return c < 'A' || 'p' < c || ('P' < c && c < 'a');
}

// 判断数组中是否包含 num，遇到 -1 就停止
BOOL includeNum (int arr[], int x, int * index) {
    int i = 0;
    while (arr[i] != -1)
        if (arr[i++] == x) {
            *index = i;
            return TRUE;
        }
    return FALSE;
}