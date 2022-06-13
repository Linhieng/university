#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <setjmp.h>	//理解为增强版goto，可以跨越函数 
#include <time.h>
#include <conio.h> //getch()

#define MS 10
#define PEOPLE 50

void initializationAssign ();// 指定初始化
void initialization ();// 初始化结构体
void restart ();// 重启
void color (int x);// 颜色
void welcome ();// 欢迎界面
void menu ();// 显示主菜单
char receiveChar ();// 接收字符
void run (int order);// 执行相应命令
void byebye ();// 退出
char* receiveString (int size);// 接收字符串
int createAssign (int i);// 创建指定编号的联系人
void create ();// 创建通讯录信息
void assignShow (int i);// 显示指定联系人
void show ();// 显示通讯录信息
void find ();// 查找通讯录
void alter ();// 修改通讯录
void deletion ();// 删除通讯录
void help();// 帮助说明


// 通讯录结构体
struct AddressList {
	char *name;		//名字
	char *phone;	//手机号码
	char *address;	//地址
	char *comment;	//备注
	int flag;		//是否已添加
} addressList[PEOPLE] = {
	{"管理员", "19866770000", "中国广东湛江", "程序管理员", 1},
	{"服务商", "110", "中国广东公安局", "有问题请打此电话", 1},
	{"神秘号码", "15967891501", "未知地址", "不要打！不要打！不要打！", 1},
	{"紧急求救", "120", "医院", "没事不要打", 1}
};

clock_t begin_t, end_t;// 定义时间
double total_t;// 时间差
jmp_buf buf;// 增强版goto


// 主函数调用
int main (void) {
	system("title 通讯录管理系统");
	// 初始化结构体
	void initialization();

	// 欢迎
	welcome();

	// 增强版goto标识，重启时回到此处
	if (setjmp(buf) != 0) fflush(stdin);

	while (1) {
		// 菜单
		menu();
		Sleep(MS);
		// 接收命令
		int order;
		worseInput:	//输入非法字符时重新输入
		order = (int)receiveChar();
		if (order >= '0' && order <= '8') {
			run(order-48);
		} else if (order == '\n') {
//			printf("\n都没有输入，按回车干什么？？？重新输入！\n");
			printf("\n未检测到有效命令，请重新输入\n"); 
			Sleep(MS);
			goto worseInput;
		} else {
			printf("\n检测到不存在的命令，请重新输入\n");
			Sleep(MS);
			goto worseInput;
		}

		Sleep(MS);
//		printf("\n输入任意键继续......");
//		getchar();
		system("pause");
		fflush(stdin);
		Sleep(MS);

	}
}

// 指定初始化
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

// 初始化结构体
void initialization () {
	int i;
	for (i = 4; i < PEOPLE; i++) {
		initializationAssign(i);
	}
}

// 重启
void restart () {
	fflush(stdin);
	printf("\n正在执行，请稍后....\n");
	color(1);
	Sleep(MS);
	printf("\n成功！\n");
	Sleep(MS);
	system("cls");
	longjmp(buf,1); // 跳转到开头
}


// 颜色
void color (int x) {
	int i;
	if (x < 1) {
		printf("\nx值太小\n");
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


// 欢迎界面
void welcome () {
	printf("请按任意键开启系统......");
//	getchar();
	getch();
	fflush(stdin);
	begin_t = clock();	//获取初始时间
	printf("\n正在开启，请稍后\n");
	color(2);
	puts("\n\t\t欢迎进入~\t\t");
	Sleep(MS);
	end_t = clock();
	total_t = (double)(end_t - begin_t) / CLOCKS_PER_SEC;
	printf("本次开机时长：%.3f秒\n", total_t);

}

// 显示主菜单
void menu () {
	puts("\n\t---------------------------------");
	Sleep(MS);
	puts("\t=\t简易版通讯录系统\t=");
	puts("\t=\t输入序号可选择对应功能\t=");
	Sleep(MS);
	puts("\t=\t1、显示主菜单\t\t=");
	Sleep(MS);
	puts("\t=\t2、创建通讯录信息\t=");
	Sleep(MS);
	puts("\t=\t3、显示通讯录信息\t=");
	Sleep(MS);
	puts("\t=\t4、查找通讯录\t\t=");
	Sleep(MS);
	puts("\t=\t5、修改通讯录\t\t=");
	Sleep(MS);
	puts("\t=\t6、删除通讯录\t\t=");
	Sleep(MS);
	puts("\t=\t7、帮助说明\t\t=");
	Sleep(MS);
	puts("\t=\t8、清屏\t\t\t=");
	Sleep(MS);
	puts("\t=\t   退出请输入0\t\t=");
	Sleep(MS);
	puts("\t---------------------------------\n");
}

// 接收字符：
char receiveChar () {
	char x;
	printf("\n\t请输入:  ");
	fscanf(stdin, "%c", &x);
	fflush(stdin);
	if (x == '\n') {
		printf("\a\n提醒一下，你输入了回车\n");
	}
	return x;
}

// 执行相应命令
void run (int order) {
	switch (order) {

		case 0 :
			byebye();
			break;
		case 1 :
			printf("\n哎，你不选1, 我也会显示主菜单的啦。。。\n");
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
			printf("\n按任意键开始清屏. . .");
//			getchar();
			getch();
			// 重启函数中有fflush了
			restart();
			break;
		default :
			printf("\n不存在此命令");
			restart();
			break;
	}
}

// 退出
void byebye () {
	printf("\n检测到你输入了0，真的要退出吗？？？？\n");
	Sleep(MS);
	printf("确定退出请输入y, 输入其他默认手抖~~~:  ");
	char x = receiveChar();
	if (x == 'y' || x == 'Y') {
		int i;
		for (i = 0; i < 30; i++) {
			puts("");
			Sleep(MS);
		}
		printf("\n\t================");
		printf("\n\t==欢迎再次光临==");
		printf("\n\t================");
		for (i = 0; i < 15; i++) {
			puts("");
			Sleep(MS);
		}
		end_t = clock();
		total_t = (double)(end_t - begin_t) / CLOCKS_PER_SEC;
		printf("本次使用时长：%d分%d秒",(int)total_t / 60, (int)total_t % 60);
		Sleep(1000);
		exit(0);
	}

	// 不退出
	Sleep(MS);
	printf("\n我就猜到你手抖了。。。\n");
}

// 接收字符串
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

// 创建指定编号的联系人
int createAssign (int i) {
	if (i < 0 || i > PEOPLE) {
		// 下标溢出bug
		printf("\n你干嘛添加那么多呢。没错，这是bug");
		Sleep(MS);
		printf("\n但因为程序员太懒了，没有解决该bug");
		Sleep(MS);
		printf("\n感兴趣的话自己看源代码吧");
		Sleep(MS);
		printf("稍后将重启系统");
		Sleep(MS);
		Sleep(1000);
		restart();
		return 0;
	} else {
		char *x;
		struct AddressList *people = &addressList[i];

		name:
		Sleep(MS);
		printf("\n\t请输入姓名：");
		if ((people->name = receiveString(20)) == NULL) {
			printf("\n还没输入呢就回车了？？\n");
			goto name;
		}

		phone:
		Sleep(MS);
		printf("\n\t请输入手机号：");
		if ((people->phone = receiveString(30)) == NULL) {
			printf("\n还没输入呢就回车了？？\n");
			goto phone;
		}

		address:
		Sleep(MS);
		printf("\n\t请输入地址：");
		if ((people->address = receiveString(50)) == NULL) {
			printf("\n还没输入呢就回车了？？\n");
			goto address;
		}

		comment:
		Sleep(MS);
		printf("\n\t备注：");
		if ((people->comment = receiveString(200)) == NULL) {
			printf("\n还没输入呢就回车了？？\n");
			goto comment;
		}

		// 将flag改为1代表已被使用
		people->flag = 1;
	}
	return 1;
}

// 创建通讯录信息
void create () {
	int i;
	for (i = 0; i < PEOPLE; i++) {
		if (addressList[i].flag == 0) break;
		else if (i == PEOPLE-1 && addressList[i].flag == 1) {
			Sleep(MS);
			printf("\n没有空间了，请删除联系人或者联系管理员购买VIP\n");
			return;
		}
	}

	if (createAssign(i) == 0) {
		printf("\n创建失败，请联系管理员\n");
		return;	//创建失败
	}
	Sleep(MS);
	printf("\n创建成功\n");

	Sleep(MS);
	printf("\n是否继续添加？\n");
	Sleep(MS);
	printf("继续添加请输入y，输入其他则不添加");
	char y = receiveChar();
	if (y == 'y' || y == 'Y') {
		fflush(stdin);
		create();
		return;
	}
}

// 显示指定联系人
void assignShow (int i) {
	if (i < 0 || i >= PEOPLE) {
		printf("\n请联系程序员，出现bug了，重新启动一下");
		restart();
	}
	struct AddressList *people = &addressList[i];
	printf("\n编号：%d\n", i+1);
	Sleep(MS);
	printf("\n  姓名：\t%s", people->name);
	Sleep(MS);
	printf("\n  号码：\t%s", people->phone);
	Sleep(MS);
	printf("\n  地址：\t%s", people->address);
	Sleep(MS);
	printf("\n  备注：\t%s", people->comment);
	Sleep(MS);
	printf("\n");
}

// 显示通讯录信息
void show () {
//	int order;
	struct AddressList *people;
	printf("\n全部显示请输入1");
	printf("\n顺序显示全部请输入2");
	printf("\n输入其他则按指定编号显示\n");
//	printf("\n请输入:  "); // receiveChar中已经有提示请输入了！ 
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
				printf("\n按任意键显示下一个......");
				getch();
				fflush(stdin);
			}
		}
		printf("\n显示完毕\n");
	} else {
		int i;
ReturnShow : 	//继续显示 标记处
		printf("\n想要显示第几位(1-%d)：", PEOPLE);
		fflush(stdin);
		if ((fscanf(stdin, "%d", &i)) == 1) {
			if (i >= 1 && i <= PEOPLE) {
				assignShow(i-1);
			} else {
				printf("\n呃呃呃。。。你看看你是不是输错了");
				printf("\n重新输入一下吧");
				goto ReturnShow;
			}
		} else {
			printf("\n是你乱输入了还是我出bug了...");
			printf("\n我重启一下系统吧");
			restart();
		}
		fflush(stdin);
		printf("\n是否继续按编号查找？\n");
		printf("输入y代表是，输入其他代表否");
		char y = receiveChar();
		if (y == 'y' || y == 'Y') {
			goto ReturnShow;
		}
		fflush(stdin);
	}

}

// 查找通讯录
void find () {
	printf("\n暂时只实现手机号查找\n");
	printf("请输入手机号：");
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
		printf("\n共找到%d位：\n", num);
		for (i = 0; i < num; i++) {
			assignShow(x[i]);
		}
	} else {
		printf("\n找不到哦，要不要输入新建一个呢？");
		Sleep(MS);
		printf("\n输入y新建，输入其他则不新建\n");
		Sleep(MS);
		char y = receiveChar();
		if (y == 'y' || y == 'Y') {
			run(2);
			return;
		}
		printf("\n好的，不新建\n");
	}
}

// 修改通讯录
void alter () {
	printf("\n请输入要修改的联系人编号(1-%d)：", PEOPLE);
	int no;
	fscanf(stdin, "%d", &no);
	fflush(stdin);
	if (no > 0 && no <= PEOPLE) {
		struct AddressList *people = &addressList[no-1];
		printf("\n编号为%d的联系人信息如下：", no);
		assignShow(no-1);
		printf("\n你确定要修改这个联系人吗？");
		printf("\n确定请输入y, 输入其他则取消:  ");
		char y = receiveChar();
		if (y == 'y' || y == 'Y') {
			fflush(stdin);
			createAssign(no-1);
			printf("\n已修改\n");
		}
		fflush(stdin);
	} else {
		printf("\n好家伙，你输入了什么，害我得重新启动");
		Sleep(500);
		restart();
	}
}

// 删除通讯录
void deletion () {
	printf("\n请输入要删除的联系人编号(1-%d)：", PEOPLE);
	int no;
	fscanf(stdin, "%d", &no);
	fflush(stdin);
	if (no > 0 && no <= PEOPLE) {
		struct AddressList *people = &addressList[no-1];
		if (people->flag == 1) {
			printf("\n编号为%d的联系人信息如下：", no);
			assignShow(no-1);
			printf("\n你确定要删除这个联系人吗？");
			printf("\n确定删除请输入y, 输入其他则不取消:  ");
			char y = receiveChar();
			if (y == 'y' || y == 'Y') {
				initializationAssign(no-1);
				printf("已删除\n");
			}

		} else {
			printf("\n编号为%d处本就没有信息，不必删除！\n", no);
//			printf("\n不信？不信自己通过查找看看是不是！呵呵呵~~");
		}
	} else {
		printf("\n好家伙，你输入了什么，害我得重新启动");
		Sleep(500);
		restart();
		return;
	}
}

// 帮助说明
void help () {
	Sleep(MS);
	printf("\n输入时小心，如果乱输入字符可能会重启系统，重启时会清屏");
	Sleep(MS);
	printf("\n本程序默认存在四位联系人");
	Sleep(MS);
	printf("\n本程序没有使用文件存储，每次重新启用都会还原到默认值");
	Sleep(MS);
	printf("\n本程序对可能出现的bug做了处理，处理形式是“重启”");
	Sleep(MS);
	printf("\n本程序输入字符串部分可以输入空格，且不会对输入内容进行判断（如手机号可以输入字符）");
	Sleep(MS);
	printf("\n本程序为防止一些不必要的bug，输入语句太长会被截掉");
	Sleep(MS);
	printf("\n");
	Sleep(MS);
}

