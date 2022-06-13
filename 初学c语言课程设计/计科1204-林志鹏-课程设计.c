#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <setjmp.h>	//���Ϊ��ǿ��goto�����Կ�Խ���� 
#include <time.h>
#include <conio.h> //getch()

#define MS 10
#define PEOPLE 50

void initializationAssign ();// ָ����ʼ��
void initialization ();// ��ʼ���ṹ��
void restart ();// ����
void color (int x);// ��ɫ
void welcome ();// ��ӭ����
void menu ();// ��ʾ���˵�
char receiveChar ();// �����ַ�
void run (int order);// ִ����Ӧ����
void byebye ();// �˳�
char* receiveString (int size);// �����ַ���
int createAssign (int i);// ����ָ����ŵ���ϵ��
void create ();// ����ͨѶ¼��Ϣ
void assignShow (int i);// ��ʾָ����ϵ��
void show ();// ��ʾͨѶ¼��Ϣ
void find ();// ����ͨѶ¼
void alter ();// �޸�ͨѶ¼
void deletion ();// ɾ��ͨѶ¼
void help();// ����˵��


// ͨѶ¼�ṹ��
struct AddressList {
	char *name;		//����
	char *phone;	//�ֻ�����
	char *address;	//��ַ
	char *comment;	//��ע
	int flag;		//�Ƿ������
} addressList[PEOPLE] = {
	{"����Ա", "19866770000", "�й��㶫տ��", "�������Ա", 1},
	{"������", "110", "�й��㶫������", "���������˵绰", 1},
	{"���غ���", "15967891501", "δ֪��ַ", "��Ҫ�򣡲�Ҫ�򣡲�Ҫ��", 1},
	{"�������", "120", "ҽԺ", "û�²�Ҫ��", 1}
};

clock_t begin_t, end_t;// ����ʱ��
double total_t;// ʱ���
jmp_buf buf;// ��ǿ��goto


// ����������
int main (void) {
	system("title ͨѶ¼����ϵͳ");
	// ��ʼ���ṹ��
	void initialization();

	// ��ӭ
	welcome();

	// ��ǿ��goto��ʶ������ʱ�ص��˴�
	if (setjmp(buf) != 0) fflush(stdin);

	while (1) {
		// �˵�
		menu();
		Sleep(MS);
		// ��������
		int order;
		worseInput:	//����Ƿ��ַ�ʱ��������
		order = (int)receiveChar();
		if (order >= '0' && order <= '8') {
			run(order-48);
		} else if (order == '\n') {
//			printf("\n��û�����룬���س���ʲô�������������룡\n");
			printf("\nδ��⵽��Ч�������������\n"); 
			Sleep(MS);
			goto worseInput;
		} else {
			printf("\n��⵽�����ڵ��������������\n");
			Sleep(MS);
			goto worseInput;
		}

		Sleep(MS);
//		printf("\n�������������......");
//		getchar();
		system("pause");
		fflush(stdin);
		Sleep(MS);

	}
}

// ָ����ʼ��
void initializationAssign (int i) {
	struct AddressList *people = &addressList[i];
	people = &addressList[i];
	people->flag = 0;
	people->address = malloc(100);
	people->address = "(null)";
	people->comment = malloc(100);
	people->comment = "(null)";
	people->name = malloc(100);
	people->name = "(null)";
	people->phone = malloc(100);
	people->phone = "(null)";
}

// ��ʼ���ṹ��
void initialization () {
	int i;
	for (i = 4; i < PEOPLE; i++) {
		initializationAssign(i);
	}
}

// ����
void restart () {
	fflush(stdin);
	printf("\n����ִ�У����Ժ�....\n");
	color(1);
	Sleep(MS);
	printf("\n�ɹ���\n");
	Sleep(MS);
	system("cls");
	longjmp(buf,1); // ��ת����ͷ
}


// ��ɫ
void color (int x) {
	int i;
	if (x < 1) {
		printf("\nxֵ̫С\n");
		restart();
		return;
	}
	for (i = 0; i < x; i++) {
		system("color 10");
		system("color 20");
		system("color 30");
		system("color 40");
		system("color 50");
		system("color 60");
		system("color 06");
		system("color 05");
		system("color 04");
		system("color 03");
		system("color 02");
		system("color 01");
		system("color 07");
	}
}


// ��ӭ����
void welcome () {
	printf("�밴���������ϵͳ......");
//	getchar();
	getch();
	fflush(stdin);
	begin_t = clock();	//��ȡ��ʼʱ��
	printf("\n���ڿ��������Ժ�\n");
	color(2);
	puts("\n\t\t��ӭ����~\t\t");
	Sleep(MS);
	end_t = clock();
	total_t = (double)(end_t - begin_t) / CLOCKS_PER_SEC;
	printf("���ο���ʱ����%.3f��\n", total_t);

}

// ��ʾ���˵�
void menu () {
	puts("\n\t---------------------------------");
	Sleep(MS);
	puts("\t=\t���װ�ͨѶ¼ϵͳ\t=");
	puts("\t=\t������ſ�ѡ���Ӧ����\t=");
	Sleep(MS);
	puts("\t=\t1����ʾ���˵�\t\t=");
	Sleep(MS);
	puts("\t=\t2������ͨѶ¼��Ϣ\t=");
	Sleep(MS);
	puts("\t=\t3����ʾͨѶ¼��Ϣ\t=");
	Sleep(MS);
	puts("\t=\t4������ͨѶ¼\t\t=");
	Sleep(MS);
	puts("\t=\t5���޸�ͨѶ¼\t\t=");
	Sleep(MS);
	puts("\t=\t6��ɾ��ͨѶ¼\t\t=");
	Sleep(MS);
	puts("\t=\t7������˵��\t\t=");
	Sleep(MS);
	puts("\t=\t8������\t\t\t=");
	Sleep(MS);
	puts("\t=\t   �˳�������0\t\t=");
	Sleep(MS);
	puts("\t---------------------------------\n");
}

// �����ַ���
char receiveChar () {
	char x;
	printf("\n\t������:  ");
	fscanf(stdin, "%c", &x);
	fflush(stdin);
	if (x == '\n') {
		printf("\a\n����һ�£��������˻س�\n");
	}
	return x;
}

// ִ����Ӧ����
void run (int order) {
	switch (order) {

		case 0 :
			byebye();
			break;
		case 1 :
			printf("\n�����㲻ѡ1, ��Ҳ����ʾ���˵�����������\n");
			Sleep(MS);
			menu();
			break;
		case 2 :
			create();
			break;
		case 3 :
			show();
			break;
		case 4 :
			find();
			break;
		case 5 :
			alter();
			break;
		case 6 :
			deletion();
			break;
		case 7 :
			help();
			break;
		case 8 :
			printf("\n���������ʼ����. . .");
//			getchar();
			getch();
			// ������������fflush��
			restart();
			break;
		default :
			printf("\n�����ڴ�����");
			restart();
			break;
	}
}

// �˳�
void byebye () {
	printf("\n��⵽��������0�����Ҫ�˳��𣿣�����\n");
	Sleep(MS);
	printf("ȷ���˳�������y, ��������Ĭ���ֶ�~~~:  ");
	char x = receiveChar();
	if (x == 'y' || x == 'Y') {
		int i;
		for (i = 0; i < 30; i++) {
			puts("");
			Sleep(MS);
		}
		printf("\n\t================");
		printf("\n\t==��ӭ�ٴι���==");
		printf("\n\t================");
		for (i = 0; i < 15; i++) {
			puts("");
			Sleep(MS);
		}
		end_t = clock();
		total_t = (double)(end_t - begin_t) / CLOCKS_PER_SEC;
		printf("����ʹ��ʱ����%d��%d��",(int)total_t / 60, (int)total_t % 60);
		Sleep(1000);
		exit(0);
	}

	// ���˳�
	Sleep(MS);
	printf("\n�ҾͲµ����ֶ��ˡ�����\n");
}

// �����ַ���
char* receiveString (int size) {
	char *str = malloc(size);
	fgets(str, size, stdin);
	char *x;
	x = str;
	if (*x == '\n') {
		strcpy(str, "(null)");
		return NULL;
	} else {
		while (*++x != '\n');
		*x = '\0';
	}
	fflush(stdin);
	return str;
}

// ����ָ����ŵ���ϵ��
int createAssign (int i) {
	if (i < 0 || i > PEOPLE) {
		// �±����bug
		printf("\n����������ô���ء�û������bug");
		Sleep(MS);
		printf("\n����Ϊ����Ա̫���ˣ�û�н����bug");
		Sleep(MS);
		printf("\n����Ȥ�Ļ��Լ���Դ�����");
		Sleep(MS);
		printf("�Ժ�����ϵͳ");
		Sleep(MS);
		Sleep(1000);
		restart();
		return 0;
	} else {
		char *x;
		struct AddressList *people = &addressList[i];

		name:
		Sleep(MS);
		printf("\n\t������������");
		if ((people->name = receiveString(20)) == NULL) {
			printf("\n��û�����ؾͻس��ˣ���\n");
			goto name;
		}

		phone:
		Sleep(MS);
		printf("\n\t�������ֻ��ţ�");
		if ((people->phone = receiveString(30)) == NULL) {
			printf("\n��û�����ؾͻس��ˣ���\n");
			goto phone;
		}

		address:
		Sleep(MS);
		printf("\n\t�������ַ��");
		if ((people->address = receiveString(50)) == NULL) {
			printf("\n��û�����ؾͻس��ˣ���\n");
			goto address;
		}

		comment:
		Sleep(MS);
		printf("\n\t��ע��");
		if ((people->comment = receiveString(200)) == NULL) {
			printf("\n��û�����ؾͻس��ˣ���\n");
			goto comment;
		}

		// ��flag��Ϊ1�����ѱ�ʹ��
		people->flag = 1;
	}
	return 1;
}

// ����ͨѶ¼��Ϣ
void create () {
	int i;
	for (i = 0; i < PEOPLE; i++) {
		if (addressList[i].flag == 0) break;
		else if (i == PEOPLE-1 && addressList[i].flag == 1) {
			Sleep(MS);
			printf("\nû�пռ��ˣ���ɾ����ϵ�˻�����ϵ����Ա����VIP\n");
			return;
		}
	}

	if (createAssign(i) == 0) {
		printf("\n����ʧ�ܣ�����ϵ����Ա\n");
		return;	//����ʧ��
	}
	Sleep(MS);
	printf("\n�����ɹ�\n");

	Sleep(MS);
	printf("\n�Ƿ������ӣ�\n");
	Sleep(MS);
	printf("�������������y���������������");
	char y = receiveChar();
	if (y == 'y' || y == 'Y') {
		fflush(stdin);
		create();
		return;
	}
}

// ��ʾָ����ϵ��
void assignShow (int i) {
	if (i < 0 || i >= PEOPLE) {
		printf("\n����ϵ����Ա������bug�ˣ���������һ��");
		restart();
	}
	struct AddressList *people = &addressList[i];
	printf("\n��ţ�%d\n", i+1);
	Sleep(MS);
	printf("\n  ������\t%s", people->name);
	Sleep(MS);
	printf("\n  ���룺\t%s", people->phone);
	Sleep(MS);
	printf("\n  ��ַ��\t%s", people->address);
	Sleep(MS);
	printf("\n  ��ע��\t%s", people->comment);
	Sleep(MS);
	printf("\n");
}

// ��ʾͨѶ¼��Ϣ
void show () {
//	int order;
	struct AddressList *people;
	printf("\nȫ����ʾ������1");
	printf("\n˳����ʾȫ��������2");
	printf("\n����������ָ�������ʾ\n");
//	printf("\n������:  "); // receiveChar���Ѿ�����ʾ�������ˣ� 
	char order = receiveChar();
//	fscanf(stdin, "%d", &order);
//	fflush(stdin);
	if (order == '1') {
		int i;
		for (i = 0; i < PEOPLE; i++) {
			people = &addressList[i];
			if (people->flag == 1) {
				assignShow(i);
			}
		}

	} else if (order == '2') {
		int i;
		for (i = 0; i < PEOPLE; i++) {
			people = &addressList[i];
			if (people->flag == 1) {
				assignShow(i);
				printf("\n���������ʾ��һ��......");
				getch();
				fflush(stdin);
			}
		}
		printf("\n��ʾ���\n");
	} else {
		int i;
ReturnShow : 	//������ʾ ��Ǵ�
		printf("\n��Ҫ��ʾ�ڼ�λ(1-%d)��", PEOPLE);
		fflush(stdin);
		if ((fscanf(stdin, "%d", &i)) == 1) {
			if (i >= 1 && i <= PEOPLE) {
				assignShow(i-1);
			} else {
				printf("\n�������������㿴�����ǲ��������");
				printf("\n��������һ�°�");
				goto ReturnShow;
			}
		} else {
			printf("\n�����������˻����ҳ�bug��...");
			printf("\n������һ��ϵͳ��");
			restart();
		}
		fflush(stdin);
		printf("\n�Ƿ��������Ų��ң�\n");
		printf("����y�����ǣ��������������");
		char y = receiveChar();
		if (y == 'y' || y == 'Y') {
			goto ReturnShow;
		}
		fflush(stdin);
	}

}

// ����ͨѶ¼
void find () {
	printf("\n��ʱֻʵ���ֻ��Ų���\n");
	printf("�������ֻ��ţ�");
	char *phone = malloc(30);
	fscanf(stdin, "%s", phone);
	fflush(stdin);
	int i, num = 0;
	int x[PEOPLE];
	struct AddressList *people;
	for (i = 0; i < PEOPLE; i++) {
		people = &addressList[i];
		if (people->flag == 0) continue;
		if (strcmp(people->phone, phone) == 0) {
			x[num++] = i;
		}
	}
	if (num > 0) {
		printf("\n���ҵ�%dλ��\n", num);
		for (i = 0; i < num; i++) {
			assignShow(x[i]);
		}
	} else {
		printf("\n�Ҳ���Ŷ��Ҫ��Ҫ�����½�һ���أ�");
		Sleep(MS);
		printf("\n����y�½��������������½�\n");
		Sleep(MS);
		char y = receiveChar();
		if (y == 'y' || y == 'Y') {
			run(2);
			return;
		}
		printf("\n�õģ����½�\n");
	}
}

// �޸�ͨѶ¼
void alter () {
	printf("\n������Ҫ�޸ĵ���ϵ�˱��(1-%d)��", PEOPLE);
	int no;
	fscanf(stdin, "%d", &no);
	fflush(stdin);
	if (no > 0 && no <= PEOPLE) {
		struct AddressList *people = &addressList[no-1];
		printf("\n���Ϊ%d����ϵ����Ϣ���£�", no);
		assignShow(no-1);
		printf("\n��ȷ��Ҫ�޸������ϵ����");
		printf("\nȷ��������y, ����������ȡ��:  ");
		char y = receiveChar();
		if (y == 'y' || y == 'Y') {
			fflush(stdin);
			createAssign(no-1);
			printf("\n���޸�\n");
		}
		fflush(stdin);
	} else {
		printf("\n�üһ��������ʲô�����ҵ���������");
		Sleep(500);
		restart();
	}
}

// ɾ��ͨѶ¼
void deletion () {
	printf("\n������Ҫɾ������ϵ�˱��(1-%d)��", PEOPLE);
	int no;
	fscanf(stdin, "%d", &no);
	fflush(stdin);
	if (no > 0 && no <= PEOPLE) {
		struct AddressList *people = &addressList[no-1];
		if (people->flag == 1) {
			printf("\n���Ϊ%d����ϵ����Ϣ���£�", no);
			assignShow(no-1);
			printf("\n��ȷ��Ҫɾ�������ϵ����");
			printf("\nȷ��ɾ��������y, ����������ȡ��:  ");
			char y = receiveChar();
			if (y == 'y' || y == 'Y') {
				initializationAssign(no-1);
				printf("��ɾ��\n");
			}

		} else {
			printf("\n���Ϊ%d������û����Ϣ������ɾ����\n", no);
//			printf("\n���ţ������Լ�ͨ�����ҿ����ǲ��ǣ��ǺǺ�~~");
		}
	} else {
		printf("\n�üһ��������ʲô�����ҵ���������");
		Sleep(500);
		restart();
		return;
	}
}

// ����˵��
void help () {
	Sleep(MS);
	printf("\n����ʱС�ģ�����������ַ����ܻ�����ϵͳ������ʱ������");
	Sleep(MS);
	printf("\n������Ĭ�ϴ�����λ��ϵ��");
	Sleep(MS);
	printf("\n������û��ʹ���ļ��洢��ÿ���������ö��ỹԭ��Ĭ��ֵ");
	Sleep(MS);
	printf("\n������Կ��ܳ��ֵ�bug���˴���������ʽ�ǡ�������");
	Sleep(MS);
	printf("\n�����������ַ������ֿ�������ո��Ҳ�����������ݽ����жϣ����ֻ��ſ��������ַ���");
	Sleep(MS);
	printf("\n������Ϊ��ֹһЩ����Ҫ��bug���������̫���ᱻ�ص�");
	Sleep(MS);
	printf("\n");
	Sleep(MS);
}

