#include <windows.h>

#define TRUE 1
#define FALSE 0

typedef int BOOL;

#ifndef MYPROJECT_MYUTIL_H
#define MYPROJECT_MYUTIL_H

// ������Ϣ�ú�ɫ
void red(char * string) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
    printf(string);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
}
// [��ǰĿ¼] + ������ʾ��
// void yellow(char * string) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08); printf(string); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); }
void yellow(char * string) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E); printf(string); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); }
// ��ʾĿ¼�ļ�ʱ��Ŀ¼����ɫ
void blue(char * string) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x09); printf(string); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); }
// ��ʾ��Ϣ����ɫ
void green(char * string) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A); printf(string); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); }

void showMenu() {
    printf("�����ļ�\t");       printf("touch <�ļ���>\n");
    printf("ɾ���ļ�\t");       printf("rm <�ļ���>\n");
    printf("����Ŀ¼\t");       printf("mkdir <�ļ���>\n");
    printf("ɾ��Ŀ¼\t");       printf("rmdir <�ļ���>\n");
    printf("��ʾ�ļ�Ŀ¼\t");    printf("tree\n");
    printf("�鿴Ŀ¼�ļ�\t");    printf("ls\n");
    printf("�������ļ�\t");      printf("rename <���ļ���> <���ļ���>\n");
    printf("��ʾ�ļ�����\t");    printf("cat <�ļ���>\n");
    printf("��д�ļ�����\t");    printf("vim <�ļ���>\n");
    printf("�ı�Ŀ¼\t");       printf("cd <�ļ�Ŀ¼>\n");
    printf("�ƶ��ļ�\t");       printf("mv <�ļ���> <Ŀ¼>\n");
    printf("�����ļ�\t");       printf("copy <���ļ�> <�������ļ�>\n");
    printf("��ʾ�˰����˵�\t");       printf("help\n");
    printf("�˳�ϵͳ\t");       printf("exit\n");
    printf("\n");
}

void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
    SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}
//��ȡ����λ��x
int wherex() {
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.X);
}
//��ȡ����λ��y
int wherey() {
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.Y);
}

void back() { // ���˵��������ף�x = 0, y ��Ҫ -2(���Ե�����)
    gotoxy(0, wherey() - 1);
}

void printArr(char c[]) {
    int i = 0;
    while (c[i]) printf("%c", c[i++]);
}

#endif //MYPROJECT_MYUTIL_H
