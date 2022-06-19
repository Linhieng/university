#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h" // 我的一些配置
#include <conio.h>

#define MAX_FILE_NAME 32
#define MAX_CONTENT 1024
#define MAX_DIR_NUM 128

struct PCB {
    char filename[MAX_FILE_NAME];  // 文件名
    char content[MAX_CONTENT]; // 文件内容
    struct PCB * sub_file; // 当次 PCB 为目录时，它将拥有子文件
    struct PCB * prev;  // 链接上一个 PCB
    struct PCB * next;  // 链接下一个 PCB
};

typedef struct PCB PCB;

PCB* head; // 根节点
PCB* current_head; // 当前目录

char root[128] = "[/]"; // 控制台显示当前目录

// 初始化根节点
void init();
// 判断文件是否存在当前目录下
BOOL existFile(char file_name[MAX_FILE_NAME]);
// 判断文件在当前目录下, 是否是目录
BOOL isDir(char file_name[MAX_FILE_NAME]);
// 将一个新的 pcb 添加到当前目录末尾
void addPCB(PCB *pcb);
// 在当前目录下添加一个文件 pcb
void addFile(char file_name[MAX_FILE_NAME]);
// 删除当前目录下的文件
void deleteFile(char file_name[MAX_FILE_NAME]);
// 在当前目录下新建一个目录 pcb
void addDir(char dir_name[MAX_FILE_NAME]);
// 递归打印当前目录下所有的目录
void tree(PCB* pHead, int tabs, BOOL is_end);
// (非递归)查看当前目录下所有的文件
void ls(PCB* pcb);
// 重命名当前目录下的一个 pcb
void myRename(char old_name[], char new_name[]);
// 查看当前目录下的文件 pcb 的内容
void showContent(char file_name[MAX_FILE_NAME]);
// 将内容写入当前目录下的文件 pcb 中
void addContent(char file_name[MAX_FILE_NAME], char content[MAX_CONTENT]);
// 输入内容面板，接收用户输入的内容
void inputContent(char file_name[MAX_FILE_NAME]);
// 拷贝指定文件到当前目录
void copyFile(char dest[MAX_FILE_NAME], char src[MAX_FILE_NAME]);
// 回退上一级 cd ..
void cdBack();
// 改变当前目录
void cd(char dir_name[MAX_FILE_NAME]);
// 将当前目录的文件 pcb 移动到当前目录中的一个目录下
void mv(char src[MAX_FILE_NAME], char dest[MAX_FILE_NAME]);
// 检测用户输入的命令并执行对应的操作
void transfer();


void init() {
    head = malloc(sizeof(PCB));
    head->content[0] = 0;
    head->next = NULL;
    head->prev = NULL;
    head->sub_file = NULL;
    strcpy(head->filename, "/");
    current_head = head;
}

BOOL existFile(char file_name[MAX_FILE_NAME]) {
    PCB *t = current_head->next;
    while (t) {
        if (0 == strcmp(t->filename, file_name)) {
            return TRUE;
        }
        t = t->next;
    }
    return FALSE;
}

BOOL isDir(char file_name[MAX_FILE_NAME]) {
    PCB *t = current_head->next;
    while (t) {
        if (0 == strcmp(t->filename, file_name)) {
            return t->sub_file == NULL? FALSE : TRUE;
        }
        t = t->next;
    }

}

void addPCB(PCB *pcb) {
    // 添加到 PCB 链上
    PCB *t = current_head;
    while (t->next) t = t->next;
    pcb->prev = t;
    t->next = pcb;
}

void addFile(char file_name[MAX_FILE_NAME]) {
    if (existFile(file_name)) {
        red("已存在该文件！\n");
        return;
    }

    // 创建一个文件 PCB
    PCB *pcb = malloc(sizeof(PCB));
    strcpy(pcb->filename, file_name);
    pcb->content[0] = 0;
    pcb->sub_file = NULL;
    pcb->next = NULL;

    addPCB(pcb);
}

void deleteFile(char file_name[MAX_FILE_NAME]) {
    PCB *t = current_head->next;
    while (t) {
        if (0 == strcmp(t->filename, file_name)) {
            // 双向链表的删除
            PCB *tm = t->prev;
            tm->next = t->next; // tm 肯定不为 NULL
            t->next && (t->next->prev = tm); // t->next 可能为 NULL
            // 防止内存泄露
            if (t->sub_file) free(t->sub_file) ;
            free(t);
            return;
        }
        t = t->next;
    }
    red("不存在该文件！\n");
}

void addDir(char dir_name[MAX_FILE_NAME]) {

    // 创建一个文件 PCB
    PCB *pcb = malloc(sizeof(PCB));
    strcpy(pcb->filename, dir_name);
    pcb->content[0] = 0;

    // 创建子目录 head
    PCB *h = malloc(sizeof(PCB));
    strcpy(h->filename, ".");
    h->content[0] = 0;
    h->sub_file = NULL;
    // h->prev = pcb;
    h->prev = current_head;
    h->next = NULL;

    pcb->sub_file = h;
    pcb->next = NULL;

    // 添加到 PCB 链上
    addPCB(pcb);
}

void tree(PCB* pHead, int tabs, BOOL is_end) {
    PCB *t = pHead->next;

    if (tabs <= 0) printf("  %s\n", pHead->filename);

    // 提取出目录 PCB
    PCB *(dir[MAX_DIR_NUM]);
    int di = 0; // 目录数量
    while (t) {
        if (t->sub_file != NULL) {
            dir[di] = t;
            di++;
        }
        t = t->next;
    }
    if (tabs == 0 && di == 0) {
        green(" 没有子文件夹\n");
        return;
    }
    // 打印目录
    for (int i = 0; i < di; i++) {
        for (int j = 0; j < tabs; j++) printf(" %s    ", is_end ? " " : "┃");
        printf(" %s━━━━ %s\n", i == di-1? "┗" : "┣", dir[i]->filename);
        tree(dir[i]->sub_file, tabs + 1, i == di-1? TRUE : FALSE);
    }
}

void ls(PCB* pcb) {
    PCB *t = pcb->next;
    while (t) {
        t->sub_file == NULL
            ? printf("%s", t->filename)
            : blue(t->filename)
            ;
        printf("\n");
        t = t->next;
    }
}

void myRename(char old_name[], char new_name[]) {
    PCB *t = current_head->next;
    while (t) {
        if (0 == strcmp(t->filename, old_name)) {
            strcpy(t->filename, new_name);
            return;
        }
        t = t->next;
    }
    red("不存在该文件！\n");
}

void showContent(char file_name[MAX_FILE_NAME]) {
    if (isDir(file_name)) {
        red("请输入一个文件名！\n");
        return;
    }

    PCB *t = current_head->next;
    while(t) {
        if (0 == strcmp(t->filename, file_name)) {
            green("===BEGIN===\n");
            t->content[0] == 0
                ?
                : printf("%s", t->content)
                ;
            green("\n===END===\n");
            return;
        }
        t = t->next;
    }
}

void addContent(char file_name[MAX_FILE_NAME], char content[MAX_CONTENT]) {
    PCB *t = current_head->next;
    while (t) {
        if (0 == strcmp(file_name, t->filename)) {
            strcpy(t->content, content);
            break;
        }
        t = t->next;
    }

}

void inputContent(char file_name[MAX_FILE_NAME]) {
    green("vim 操作台：请在下方输入内容（输入 ESC 则退出并保存）：\n");
    char content[MAX_CONTENT] = {0};
    while (1) {
        char c = getch(); // 这里得用 char, 换成 int 会获取不到中文
        // 基本字符（键盘基本字符：字母、数字、符号）
        if (c >= 0x20 && c <= 0x7F) {
            sprintf(content, "%s%c", content, c);
            printf("%c", c);

        } else if(c == 13) {
            sprintf(content, "%s\n", content);
            printf("\n");

        } else if (c == 8) { // 删除字符
            int i = 1;
            while (content[i]) i++; // 有初始化 content 为0, 不怕死循环
            i--;
            if (content[i] == 10) { // 删除已到达行首
                content[i] = 0;
                back(); // 回退到上行行首
                int j = i;
                while (j >= 0 && content[j] != 10) j--;
                printArr(&content[j+1]);
                continue;
            }
            if (content[i] >= 0x20 && content[i] <= 0x7F) {
                content[i] = 0;
                printf("\b \b");
                continue;
            }
            // 不是基本字符, (默认)就是中文, 中文占两字节.
            content[i-1] = 0;
            printf("\b\b  \b\b");

        } else if (c == 27) { // esc 按键
            break;
        } else if (c < 0) { // 期待的是这里接收的全部都是汉字（可能有意外）
            // 上下左右按键，占用两个字节, 高 4 位均为 -32 故此处将其吸收掉
            if (c == -32) { // 如果遇到有中文输入不了，则可能是在这里被吸收了
                getch();
                continue;
            }
            sprintf(content, "%s%c", content, c);
            printf("%c", c);
        }

    }

    addContent(file_name, content);

    green("\n输入的内容：\n");
    printf("%s\n", content);
}

void copyFile(char dest[MAX_FILE_NAME], char src[MAX_FILE_NAME]) {

    if (!existFile(dest)) {
        red("无法拷贝不存在的文件！\n");
        return;
    }
    if (isDir(dest)) {
        red("不支持拷贝目录");
        return;
    }
    if (existFile(src)) {
        red("不允许覆盖已存在的文件！\n");
        return;
    }

    PCB *t = current_head;
    while (1) { // 调用 copyFile 处前面进行了检查，已确保存在 dest 文件
        if (0 == strcmp(t->filename, dest)) {
            break;
        }
        t = t->next;
    }
    PCB *n = malloc(sizeof(PCB));
    strcpy(n->filename, src);
    strcpy(n->content, t->content);
    n->sub_file = NULL; // 改函数不是用来拷贝目录的
    n->next = NULL;

    addPCB(n);
}

void cdBack() {
    if (0 == strcmp(current_head->filename, "/")) { // 当前已在根目录下
        return;
    }
    strcpy(current_head->filename, ".");
    // 需要回退到父文件夹的头节点, 而不是父文件夹
    current_head = current_head->prev;
    sprintf(root, "[%s]", current_head->filename);
}

void cd(char dir_name[MAX_FILE_NAME]) {
    PCB *t = current_head;
    while (t) {
        if (0 == strcmp(t->filename, dir_name)) {
            current_head = t->sub_file;
            strcpy(current_head->filename, t->filename);
            sprintf(root, "[/%s]", t->filename);
            return;
        }
        t = t->next;
    }
}

// src 只允许是当前文件下的内容
void mv(char src[MAX_FILE_NAME], char dest[MAX_FILE_NAME]) {
    PCB *t = current_head->next;
    PCB *srcP = NULL;
    PCB *destHead = NULL;
    while (t) {
        if (0 == strcmp(src, t->filename)) {
            srcP = t;
        }
        if (t->sub_file != NULL && 0 == strcmp(t->filename, dest)) {
            destHead = t->sub_file;
        }
        t = t->next;
    }
    if (srcP == NULL) {
        red("当前目录不存在该文件");
        return;
    }
    if (destHead == NULL) {
        red("当前目录不存在该目录");
        return;
    }
    // 将 src 抽离出来
    srcP->prev->next = srcP->next;
    srcP->next->prev = srcP->prev;
    // 将 src 移动到 dest 目录下
    while (destHead->next) destHead = destHead->next;
    srcP->prev = destHead;
    srcP->next = NULL;
    destHead->next = srcP;
}

void transfer() {
    // 输入的命名
    char command[10];
    fflush(stdin);
    scanf_s("%s", command, 10);

    if (0 == strcmp("touch", command)) {
        char file_name[MAX_FILE_NAME];
        scanf_s("%s", file_name, MAX_FILE_NAME);
        addFile(file_name);

    } else if (0 == strcmp("rm", command)) {
        char file_name[MAX_FILE_NAME];
        scanf_s("%s", file_name, MAX_FILE_NAME);
        deleteFile(file_name);

    } else if (0 == strcmp("mkdir", command)) {
        char dir_name[MAX_FILE_NAME];
        scanf_s("%s", dir_name, MAX_FILE_NAME);
        addDir(dir_name);

    } else if (0 == strcmp("rmdir", command)) {
        char dir_name[MAX_FILE_NAME];
        scanf_s("%s", dir_name, MAX_FILE_NAME);
        deleteFile(dir_name);

    } else if (0 == strcmp("ls", command)) {
        ls(current_head);

    } else if (0 == strcmp("tree", command)) {
        tree(current_head, 0, FALSE);

    } else if (0 == strcmp("rename", command)) {
        char old[MAX_FILE_NAME];
        char new[MAX_FILE_NAME];
        scanf_s("%s", old, MAX_FILE_NAME);
        scanf_s("%s", new, MAX_FILE_NAME);
        myRename(old, new);

    } else if (0 == strcmp("cat", command)) {
        char file_name[MAX_FILE_NAME];
        scanf_s("%s", file_name, MAX_FILE_NAME);
        showContent(file_name);

    } else if (0 == strcmp("vim", command)) {
        char file_name[MAX_FILE_NAME];
        scanf_s("%s", file_name, MAX_FILE_NAME);
        if (!existFile(file_name)) {
            red("不存在该文件！\n");
            return;
        }
        inputContent(file_name);

    } else if (0 == strcmp("cd", command)) {
        char dir_name[MAX_FILE_NAME];
        scanf_s("%s", dir_name, MAX_FILE_NAME);
        if (0 == strcmp(dir_name, "..")) {
            cdBack();
            return;
        }
        if (!isDir(dir_name)) {
            red("不存在该目录！");
            return;
        }
        cd(dir_name);

    } else if (0 == strcmp("mv", command)) {
        char src[MAX_FILE_NAME];
        char dest[MAX_FILE_NAME];
        scanf_s("%s", src, MAX_FILE_NAME);
        scanf_s("%s", dest, MAX_FILE_NAME);
        mv(src, dest);

    } else if (0 == strcmp("copy", command)) {
        char dest[MAX_FILE_NAME];
        char src[MAX_FILE_NAME];
        scanf_s("%s", dest, MAX_FILE_NAME);
        scanf_s("%s", src, MAX_FILE_NAME);
        copyFile(dest, src);

    } else if (0 == strcmp("exit", command)) {
        exit(0);

    } else if (0 == strcmp("help", command)) {
        showMenu();

    } else {
        red("错误的指令!\n");

    }
}

int main() {

    init();
    green("欢迎使用模拟文件系统终端界面\n");

    showMenu();

    while (1) {
        // 当前目录 + 命令提示符
        char c[128];
        sprintf(c, "%s$ ", root);
        yellow(c);

        transfer();   // 根据用户输入的指令，进入相应的操作界面. 只有输入 exit 才能退出
    }
}