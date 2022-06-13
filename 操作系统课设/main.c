#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h" // �ҵ�һЩ����
#include <conio.h>

#define MAX_FILE_NAME 32
#define MAX_CONTENT 1024
#define MAX_DIR_NUM 128

struct PCB {
    char filename[MAX_FILE_NAME];  // �ļ���
    char content[MAX_CONTENT]; // �ļ�����
    struct PCB * sub_file; // ���� PCB ΪĿ¼ʱ������ӵ�����ļ�
    struct PCB * prev;  // ������һ�� PCB
    struct PCB * next;  // ������һ�� PCB
};

typedef struct PCB PCB;

PCB* head; // ���ڵ�
PCB* current_head; // ��ǰĿ¼

char root[128] = "[/]"; // ����̨��ʾ��ǰĿ¼

// ��ʼ�����ڵ�
void init();
// �ж��ļ��Ƿ���ڵ�ǰĿ¼��
BOOL existFile(char file_name[MAX_FILE_NAME]);
// �ж��ļ��ڵ�ǰĿ¼��, �Ƿ���Ŀ¼
BOOL isDir(char file_name[MAX_FILE_NAME]);
// ��һ���µ� pcb ��ӵ���ǰĿ¼ĩβ
void addPCB(PCB *pcb);
// �ڵ�ǰĿ¼�����һ���ļ� pcb
void addFile(char file_name[MAX_FILE_NAME]);
// ɾ����ǰĿ¼�µ��ļ�
void deleteFile(char file_name[MAX_FILE_NAME]);
// �ڵ�ǰĿ¼���½�һ��Ŀ¼ pcb
void addDir(char dir_name[MAX_FILE_NAME]);
// �ݹ��ӡ��ǰĿ¼�����е�Ŀ¼
void tree(PCB* pHead, int tabs, BOOL is_end);
// (�ǵݹ�)�鿴��ǰĿ¼�����е��ļ�
void ls(PCB* pcb);
// ��������ǰĿ¼�µ�һ�� pcb
void myRename(char old_name[], char new_name[]);
// �鿴��ǰĿ¼�µ��ļ� pcb ������
void showContent(char file_name[MAX_FILE_NAME]);
// ������д�뵱ǰĿ¼�µ��ļ� pcb ��
void addContent(char file_name[MAX_FILE_NAME], char content[MAX_CONTENT]);
// ����������壬�����û����������
void inputContent(char file_name[MAX_FILE_NAME]);
// ����ָ���ļ�����ǰĿ¼
void copyFile(char dest[MAX_FILE_NAME], char src[MAX_FILE_NAME]);
// ������һ�� cd ..
void cdBack();
// �ı䵱ǰĿ¼
void cd(char dir_name[MAX_FILE_NAME]);
// ����ǰĿ¼���ļ� pcb �ƶ�����ǰĿ¼�е�һ��Ŀ¼��
void mv(char src[MAX_FILE_NAME], char dest[MAX_FILE_NAME]);
// ����û���������ִ�ж�Ӧ�Ĳ���
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
    // ��ӵ� PCB ����
    PCB *t = current_head;
    while (t->next) t = t->next;
    pcb->prev = t;
    t->next = pcb;
}

void addFile(char file_name[MAX_FILE_NAME]) {
    if (existFile(file_name)) {
        red("�Ѵ��ڸ��ļ���\n");
        return;
    }

    // ����һ���ļ� PCB
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
            // ˫�������ɾ��
            PCB *tm = t->prev;
            tm->next = t->next; // tm �϶���Ϊ NULL
            t->next && (t->next->prev = tm); // t->next ����Ϊ NULL
            // ��ֹ�ڴ�й¶
            if (t->sub_file) free(t->sub_file) ;
            free(t);
            return;
        }
        t = t->next;
    }
    red("�����ڸ��ļ���\n");
}

void addDir(char dir_name[MAX_FILE_NAME]) {

    // ����һ���ļ� PCB
    PCB *pcb = malloc(sizeof(PCB));
    strcpy(pcb->filename, dir_name);
    pcb->content[0] = 0;

    // ������Ŀ¼ head
    PCB *h = malloc(sizeof(PCB));
    strcpy(h->filename, ".");
    h->content[0] = 0;
    h->sub_file = NULL;
    // h->prev = pcb;
    h->prev = current_head;
    h->next = NULL;

    pcb->sub_file = h;
    pcb->next = NULL;

    // ��ӵ� PCB ����
    addPCB(pcb);
}

void tree(PCB* pHead, int tabs, BOOL is_end) {
    PCB *t = pHead->next;

    if (tabs <= 0) printf("  %s\n", pHead->filename);

    // ��ȡ��Ŀ¼ PCB
    PCB *(dir[MAX_DIR_NUM]);
    int di = 0; // Ŀ¼����
    while (t) {
        if (t->sub_file != NULL) {
            dir[di] = t;
            di++;
        }
        t = t->next;
    }
    if (tabs == 0 && di == 0) {
        green(" û�����ļ���\n");
        return;
    }
    // ��ӡĿ¼
    for (int i = 0; i < di; i++) {
        for (int j = 0; j < tabs; j++) printf(" %s    ", is_end ? " " : "��");
        printf(" %s�������� %s\n", i == di-1? "��" : "��", dir[i]->filename);
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
    red("�����ڸ��ļ���\n");
}

void showContent(char file_name[MAX_FILE_NAME]) {
    if (isDir(file_name)) {
        red("������һ���ļ�����\n");
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
    green("vim ����̨�������·��������ݣ����� ESC ���˳������棩��\n");
    char content[MAX_CONTENT] = {0};
    while (1) {
        char c = getch(); // ������� char, ���� int ���ȡ��������
        // �����ַ������̻����ַ�����ĸ�����֡����ţ�
        if (c >= 0x20 && c <= 0x7F) {
            sprintf(content, "%s%c", content, c);
            printf("%c", c);

        } else if(c == 13) {
            sprintf(content, "%s\n", content);
            printf("\n");

        } else if (c == 8) { // ɾ���ַ�
            int i = 1;
            while (content[i]) i++; // �г�ʼ�� content Ϊ0, ������ѭ��
            i--;
            if (content[i] == 10) { // ɾ���ѵ�������
                content[i] = 0;
                back(); // ���˵���������
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
            // ���ǻ����ַ�, (Ĭ��)��������, ����ռ���ֽ�.
            content[i-1] = 0;
            printf("\b\b  \b\b");

        } else if (c == 27) { // esc ����
            break;
        } else if (c < 0) { // �ڴ�����������յ�ȫ�����Ǻ��֣����������⣩
            // �������Ұ�����ռ�������ֽ�, �� 4 λ��Ϊ -32 �ʴ˴��������յ�
            if (c == -32) { // ����������������벻�ˣ�������������ﱻ������
                getch();
                continue;
            }
            sprintf(content, "%s%c", content, c);
            printf("%c", c);
        }

    }

    addContent(file_name, content);

    green("\n��������ݣ�\n");
    printf("%s\n", content);
}

void copyFile(char dest[MAX_FILE_NAME], char src[MAX_FILE_NAME]) {

    if (!existFile(dest)) {
        red("�޷����������ڵ��ļ���\n");
        return;
    }
    if (isDir(dest)) {
        red("��֧�ֿ���Ŀ¼");
        return;
    }
    if (existFile(src)) {
        red("���������Ѵ��ڵ��ļ���\n");
        return;
    }

    PCB *t = current_head;
    while (1) { // ���� copyFile ��ǰ������˼�飬��ȷ������ dest �ļ�
        if (0 == strcmp(t->filename, dest)) {
            break;
        }
        t = t->next;
    }
    PCB *n = malloc(sizeof(PCB));
    strcpy(n->filename, src);
    strcpy(n->content, t->content);
    n->sub_file = NULL; // �ĺ���������������Ŀ¼��
    n->next = NULL;

    addPCB(n);
}

void cdBack() {
    if (0 == strcmp(current_head->filename, "/")) { // ��ǰ���ڸ�Ŀ¼��
        return;
    }
    strcpy(current_head->filename, ".");
    // ��Ҫ���˵����ļ��е�ͷ�ڵ�, �����Ǹ��ļ���
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

// src ֻ�����ǵ�ǰ�ļ��µ�����
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
        red("��ǰĿ¼�����ڸ��ļ�");
        return;
    }
    if (destHead == NULL) {
        red("��ǰĿ¼�����ڸ�Ŀ¼");
        return;
    }
    // �� src �������
    srcP->prev->next = srcP->next;
    srcP->next->prev = srcP->prev;
    // �� src �ƶ��� dest Ŀ¼��
    while (destHead->next) destHead = destHead->next;
    srcP->prev = destHead;
    srcP->next = NULL;
    destHead->next = srcP;
}

void transfer() {
    // ���������
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
            red("�����ڸ��ļ���\n");
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
            red("�����ڸ�Ŀ¼��");
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
        red("�����ָ��!\n");

    }
}

int main() {

    init();
    green("��ӭʹ��ģ���ļ�ϵͳ�ն˽���\n");

    showMenu();

    while (1) {
        // ��ǰĿ¼ + ������ʾ��
        char c[128];
        sprintf(c, "%s$ ", root);
        yellow(c);

        transfer();   // �����û������ָ�������Ӧ�Ĳ�������. ֻ������ exit �����˳�
    }
}