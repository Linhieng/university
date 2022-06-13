#include <windows.h>

#define TRUE 1
#define FALSE 0

typedef int BOOL;

#ifndef MYPROJECT_MYUTIL_H
#define MYPROJECT_MYUTIL_H

// 错误信息用红色
void red(char * string) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
    printf(string);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
}
// [当前目录] + 命令提示符
// void yellow(char * string) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08); printf(string); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); }
void yellow(char * string) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E); printf(string); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); }
// 显示目录文件时，目录用蓝色
void blue(char * string) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x09); printf(string); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); }
// 提示信息用绿色
void green(char * string) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A); printf(string); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); }

void showMenu() {
    printf("创建文件\t");       printf("touch <文件名>\n");
    printf("删除文件\t");       printf("rm <文件名>\n");
    printf("创建目录\t");       printf("mkdir <文件名>\n");
    printf("删除目录\t");       printf("rmdir <文件名>\n");
    printf("显示文件目录\t");    printf("tree\n");
    printf("查看目录文件\t");    printf("ls\n");
    printf("重命名文件\t");      printf("rename <旧文件名> <新文件名>\n");
    printf("显示文件内容\t");    printf("cat <文件名>\n");
    printf("改写文件内容\t");    printf("vim <文件名>\n");
    printf("改变目录\t");       printf("cd <文件目录>\n");
    printf("移动文件\t");       printf("mv <文件名> <目录>\n");
    printf("拷贝文件\t");       printf("copy <新文件> <被拷贝文件>\n");
    printf("显示此帮助菜单\t");       printf("help\n");
    printf("退出系统\t");       printf("exit\n");
    printf("\n");
}

void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}
//获取光标的位置x
int wherex() {
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.X);
}
//获取光标的位置y
int wherey() {
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.Y);
}

void back() { // 回退到上行行首，x = 0, y 需要 -2(测试得来的)
    gotoxy(0, wherey() - 1);
}

void printArr(char c[]) {
    int i = 0;
    while (c[i]) printf("%c", c[i++]);
}

#endif //MYPROJECT_MYUTIL_H
