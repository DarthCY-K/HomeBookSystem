#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <Windows.h>

int read_TimesUser = 0;
int read_TimesBook = 0;

struct UserInf
{
	char User_Account[10];
	char User_Password[20];
	char User_Email[20];
	int index = 0;
	int Admin = 0;

}UserInf[100];

struct BookInf
{
	long book_Number;
	char book_Name[20];
	char author_Name[10];
	long RuKu_Time = 0;
	long ChuBan_Time = 0;
	int index = 0;
	int exsist = 0;
}BookInf[100];

int UserInfReadF();
int UserInfSaveF(int i);
int UserInfSave_All_F();
int BookInfReadF();
int BookInfSaveF(int i);
int BookInfSave_All_F();

void LoginF();
void RegisterF();
void FindPassword();

void UserSystem();
	void LiuLan();
	void JieYue();
	void GuiHuan();
	void ChaXun();
	void CuiHuan();


void AdminSystem();
	void YiSun();
	void ShuKuInfF();
		void ChuKu();
		void RuKu();
int main()
{
	if (read_TimesUser == 0)
	{
		if (UserInfReadF() == 0)
			read_TimesUser++;
		else
			printf("UserInf.darthcy 文件信息读取失败，请联系管理员\n");
	}

	int LogOrReg = 0;
	printf("欢迎进入家庭图书管理系统，请先登录\n");
	printf("登录(1)\t注册(2)\n");
	scanf("%d", &LogOrReg);
	switch (LogOrReg)
	{
	case 1:
		LoginF();
		break;
	case 2:
		RegisterF();
		break;
	default:
		printf("输入有误,请重新输入\n");
		main();
		break;
	}
	return 0;
}

int UserInfReadF()
{
	int i = 0;
	FILE* fp;
	if (fopen_s(&fp, "UserInf.darthcy", "r"))
	{
		printf("can not open the file\n");
		return 1;									//文件打开失败，返回一个1
	}
	while (!feof(fp) && i < 100)
	{
		fscanf(fp, "%s", UserInf[i].User_Account);
		fscanf(fp, "%s", UserInf[i].User_Password);
		fscanf(fp, "%s", UserInf[i].User_Email);
		fscanf(fp, "%d", &UserInf[i].index);
		fscanf(fp, "%d", &UserInf[i].Admin);
		i++;
	}
	fclose(fp);
	return 0;										//用户信息写入成功，返回一个0
}

int UserInfSaveF(int i)
{
	FILE* fp;
	if (fopen_s(&fp, "UserInf.darthcy", "a"))
	{
		printf("can not open the file\n");
		return 1;									//文件打开失败，返回一个1
	}
	bool doOnce = false;
	if(!feof(fp))
		do {
				fprintf(fp, "%s\t", UserInf[i].User_Account);
				fprintf(fp, "%s\t", UserInf[i].User_Password);
				fprintf(fp, "%s\t", UserInf[i].User_Email);
				fprintf(fp, "%d\t", UserInf[i].index);
				fprintf(fp, "%d\n", UserInf[i].Admin);
		} while (doOnce != false);
	fclose(fp);
	return 0;
}

int UserInfSave_All_F()
{
	int i = 0;
	FILE* fp;
	if (fopen_s(&fp, "UserInf.darthcy", "w"))
	{
		printf("can not open the file\n");
		return 1;									//文件打开失败，返回一个1
	}
	while (!feof(fp) && i < 100 && UserInf[i].index == 1)
	{
		fprintf(fp, "%s\t", UserInf[i].User_Account);
		fprintf(fp, "%s\t", UserInf[i].User_Password);
		fprintf(fp, "%s\t", UserInf[i].User_Email);
		fprintf(fp, "%d\t", UserInf[i].index);
		fprintf(fp, "%d\n", UserInf[i].Admin);
		i++;
	}
	fclose(fp);
	return 0;
}

int BookInfSaveF(int i)
{
	FILE* fp;
	if (fopen_s(&fp, "BookInf.darthcy", "a"))
	{
		printf("can not open the file\n");
		return 1;									//文件打开失败，返回一个1
	}
	bool doOnce = false;
	if (!feof(fp))
	{
		do {
			fprintf(fp, "%ld\t", BookInf[i].book_Number);
			fprintf(fp, "%s\t", BookInf[i].book_Name);
			fprintf(fp, "%s\t", BookInf[i].author_Name);
			fprintf(fp, "%ld\t", BookInf[i].RuKu_Time);
			fprintf(fp, "%ld\t", BookInf[i].ChuBan_Time);
			fprintf(fp, "%d\t", BookInf[i].index);
			fprintf(fp, "%d\n", BookInf[i].exsist);
		} while (doOnce != false);
	}
	fclose(fp);
	return 0;
}

int BookInfSave_All_F()		//文件完全覆写
{
	int i = 0;
	FILE* fp;
	if (fopen_s(&fp, "BookInf.darthcy", "w"))
	{
		printf("can not open the file\n");
		return 1;									//文件打开失败，返回一个1
	}
	while (!feof(fp) && i < 100 && BookInf[i].exsist == 1)
	{
			fprintf(fp, "%ld\t", BookInf[i].book_Number);
			fprintf(fp, "%s\t", BookInf[i].book_Name);
			fprintf(fp, "%s\t", BookInf[i].author_Name);
			fprintf(fp, "%ld\t", BookInf[i].RuKu_Time);
			fprintf(fp, "%ld\t", BookInf[i].ChuBan_Time);
			fprintf(fp, "%d\t", BookInf[i].index);
			fprintf(fp, "%d\n", BookInf[i].exsist);
			i++;
	}
	fclose(fp);
	return 0;
}

int BookInfReadF()
{
	int i = 0;
	FILE* fp;
	if (fopen_s(&fp, "BookInf.darthcy", "r"))
	{
		printf("can not open the file\n");
		return 1;
	}
	while (!feof(fp) && i < 100)
	{
		fscanf(fp, "%ld", &BookInf[i].book_Number);
		fscanf(fp, "%s", BookInf[i].book_Name);
		fscanf(fp, "%s", BookInf[i].author_Name);
		fscanf(fp, "%ld", &BookInf[i].RuKu_Time);
		fscanf(fp, "%ld", &BookInf[i].ChuBan_Time);
		fscanf(fp, "%d", &BookInf[i].index);
		fscanf(fp, "%d", &BookInf[i].exsist);
		i++;
	}
	fclose(fp);
	return 0;
}



void RegisterF()
{
	char Input_regAccont[20], Input_regPassword[20], Input_regEmail[20];
	printf("请输入用户名和密码：\n");
	printf("用户名：");
	scanf("%s", Input_regAccont);
	
	CheckExName:for (int i = 0; i < 100; i++)
	{
		if (strcmp(Input_regAccont, UserInf[i].User_Account) == 0)
		{
			printf("检测到用户名与已有用户冲突，请重新输入！\n");
			printf("用户名：");
			scanf("%s", Input_regAccont);
			goto CheckExName;
		}
		else
			break;
	}

	printf("请输入密码：");
	scanf("%s", Input_regPassword);
	printf("请输入邮箱：");
	scanf("%s", Input_regEmail);

	for (int i = 0; i < 100; i++)
	{
		if (UserInf[i].index == 0)
		{
			strcpy(UserInf[i].User_Account, Input_regAccont);
			strcpy(UserInf[i].User_Password, Input_regPassword);
			strcpy(UserInf[i].User_Email, Input_regEmail);
			UserInf[i].index = 1;

			if (UserInfSaveF(i) == 0)
			{
				printf("注册成功，即将返回主菜单\n");
				main();
			}
			else
			{
				printf("注册失败，请联系管理员\n");
				printf("即将返回主菜单\n");
				main();
			}
			exit(0);
		}
		else if (i == 99 && UserInf[i].index == 1)
		{
			printf("此系统可注册人数已满，请联系管理员增加可注册数量\n");
			printf("注册失败，即将返回主菜单\n");
			main();
			exit(0);
		}
	}
}

void LoginF()	//登录函数
{
	int i = 0;
	char Input_Account[20], Input_Password[20];	//用户输入的账号和密码
	printf("请输入用户名和密码\n");

	printf("账号：");
	scanf("%s", Input_Account);


CheckName:
	printf("验证中，请稍后...\n");

	for (int i = 0; i < 100; i++)
	{
		if (strcmp(Input_Account, UserInf[i].User_Account) == 0)			//用户名正确
		{
			printf("密码：");
			scanf("%s", Input_Password);
			
			CheckPass:
			if (strcmp(Input_Password, UserInf[i].User_Password) == 0)		//用户名正确 密码正确
			{

				if (UserInf[i].Admin == 0)
				{
					printf("认证成功，即将进入家庭图书系统\n");
					UserSystem();
					exit(0);
				}
				else
				{
					printf("认证成功，即将进入家庭图书系统后台\n");
					AdminSystem();
					exit(0);
				}
			}
			else		//用户名正确 密码错误
					
			{
				int yOn = 0;
				printf("密码输入错误，请重新输入或是选择找回密码\n");
				printf("1.重新输入\t2.找回密码\n");
				scanf("%d", &yOn);
				if (yOn == 1)
				{
					printf("请输入密码：");
					scanf("%s", Input_Password);
					goto CheckPass;		//返回密码验证
				}
				else
				{
					FindPassword();		//前往找回密码函数
					exit(0);
				}
			}
		}
		else		//用户名错误
		{
			for (int j = 0; j < 10; j++)
				if (strcmp(Input_Account, UserInf[j].User_Account) == 0)
				{
					j = 10;
				}
				else if (j == 9 && strcmp(Input_Account, UserInf[j].User_Account) != 0)
				{
					printf("此用户不存在，请重新输入用户名：");
					scanf("%s", Input_Account);
					goto CheckName;		//返回用户名验证

				}
		}
	}
}

void FindPassword()
{
	char Input_Email[20];
	int SpecialNumber = 4527, Input_SpecialNumber = 0;

	printf("若要找回密码，请输入注册时所使用的邮箱，我们将会发送一份包含特殊代码的邮件至注册邮箱\n");
CheckEmail:printf("请输入注册邮箱：");
	scanf("%s", Input_Email);

	for (int i = 0; i < 100; i++)
	{
		if (Input_Email == UserInf[i].User_Email)
		{
			printf("特殊代码已发送至邮箱，请查收\n");
			Re_specNumber:
			printf("请输入特殊代码：");
			scanf("%d", &Input_SpecialNumber);

			if (Input_SpecialNumber == SpecialNumber)
			{
				printf("特殊代码验证成功\n");
				printf("请输入新密码：");
				scanf("%s", UserInf[i].User_Password);

				if (UserInfSaveF(i) == 0)
				{
					printf("修改成功！即将返回账号验证系统\n");
					LoginF();
					exit(0);
				}
				else
				{
					printf("UserInf.darthcy 文件保存失败，请联系管理员\n");
					printf("即将返回主菜单\n");
					main();
					exit(0);
				}
				exit(0);

			}
			else
			{
				printf("特殊代码验证失败，请重新输入！\n");
				goto Re_specNumber;
			}
			

		}
		else if (Input_Email == UserInf[i].User_Email && i == 99)
		{
			int yOn;
			printf("未查询到此注册邮箱，是否再次输入？\n");
			printf("1.是/t2.否\n");
			scanf("%d", &yOn);
			if (yOn == 1)
				goto CheckEmail;
			else
			{
				main();
				exit(0);
			}
			
		}

	}
	

}




void UserSystem()
{
	int Choice = 0;
	if (read_TimesBook == 0)
	{
		if (BookInfReadF() == 0)
			read_TimesBook++;
		else
			printf("BookInf.darthcy 文件读取失败，请联系管理员\n");
	}		
	printf("\n欢迎登入用户系统，请选择您需要的功能\n");
	printf("1.浏览\t2.借阅\t3.归还\t4.查询\n5.催还\n");
	scanf("%d", &Choice);
	ChoseW:switch (Choice)
	{
		case 1:
			LiuLan();
			break;
		case 2:
			JieYue();
			break;
		case 3:
		case 4:
		case 5:
		default:
			printf("输入错误，请重新输入：");
			scanf("%d", &Choice);
			goto ChoseW;
	}
	return;
}

void LiuLan()
{
	for (int i = 0; i < 100; i++)
	{
		if (BookInf[i].exsist == true)
		{
			printf("书籍编号：%l\n",BookInf[i].book_Number);
			printf("书籍名字：%s\n",BookInf[i].book_Name);
			printf("是否借出：");
			if (BookInf[i].index == 0)
				printf("否\n");
			else
				printf("是\n");
		}
	}
}

void JieYue()	//借阅模块
{
	long input_bookNumber;

	Re_bookNumber:
	printf("请输入书号：");
	getchar();
	scanf("%l", &input_bookNumber);
	for (int i = 0; i < 10; i++)
	{
		if (input_bookNumber == BookInf[i].book_Number)
		{
			if (BookInf[i].index == 1)
			{
				BookInf[i].index = 0;
				if (BookInfSaveF(i) == 0)
					printf("书籍 [%s] 成功借出！\n",BookInf[i].book_Name);
				else
					printf("BookInf.darthcy 变更信息保存失败，请联系管理员\n");
				printf("即将退出系统\n");
				return;// exit(0);
			}
			else
			{
				printf("本书 [%s] 当前已出库，借出失败！\n",BookInf[i].book_Name);
				printf("即将退出系统\n");
				return;//exit(0);
			}
		}
		else
		{
			if (i == 9 && input_bookNumber != BookInf[i].book_Number)
			{
				printf("未找到相关书籍，请重新输入书号！\n");
				getchar();
				goto Re_bookNumber;
			}
		}
	}
	return;
}

void GuiHuan()
{

}

void ChaXun()
{

}

void CuiHuan()
{

}


void AdminSystem()
{
	int Choice = 0;
	if (read_TimesBook == 0)
	{
		if (BookInfReadF() == 0)
			read_TimesBook++;
		else
			printf("BookInf.darthcy 文件读取失败，请联系管理员\n");
	}
	printf("\n欢迎登入管理系统，请选择您需要的功能\n");
	printf("1.书库信息\t2.遗损处理\t3.一键删库\n");
	scanf("%d", &Choice);
	ChoseW_admin:switch (Choice)
	{
		case 1:
			ShuKuInfF();
			break;
		case 2:
			YiSun();
			break;
		case 3:
			printf("本功能尚未开放\n");
			AdminSystem();
			break;
		default:
			printf("输入错误，请重新输入：");
			scanf("%d", &Choice);
			goto ChoseW_admin;
	}
}

void YiSun()
{

}

void ShuKuInfF()
{
	int choose = 0;
	printf("您已进入书库信息系统，管理员。请选择需要使用的功能：\n");
	Ru$Chu_ReInput:
	printf("1.入库\t2.出库\n");
	scanf("%d", &choose);
	getchar();				//缓冲区
	switch (choose)
	{
		case 1:
			RuKu();
			break;
		case 2:
			ChuKu();
			break;
		case 3:
			printf("输入有误，请重新输入\n");
			goto Ru$Chu_ReInput;
	}
	return;
}

void RuKu()
{
	long Input_book_Number;
	char Input_book_Name[20], Input_author_Name[10];
	long Input_RuKu_Time = 0, Input_ChuBan_Time = 0;

	printf("管理员，您已进入新书入库模块");
	ReInput_Book_Number:
	printf("\n请输入书籍编号：");
	scanf("%ld", &Input_book_Number);
	for (int i = 0; i < 100; i++)
	{
		if (Input_book_Number == BookInf[i].book_Number)
		{
			printf("书籍编号和已有书籍编号冲突，请重新输入\n");
			goto ReInput_Book_Number;
		}

	}
	printf("\n请输入书籍名称：");
	scanf("%s", Input_book_Name, 20);
	for (int i = 0; i < 100; i++)
	{
		if (strcmp(Input_book_Name, BookInf[i].book_Name) == 0)
		{
			printf("书籍名称和已有书籍名称冲突，请重新输入\n");
			goto ReInput_Book_Number;
		}

	}
	printf("\n请输入作者名称：");
	scanf("%s", Input_author_Name,10);

	printf("\n请输入出版时间：");
	scanf("%ld", &Input_ChuBan_Time);

	printf("\n请输入入库时间：");
	scanf("%ld", &Input_RuKu_Time);




	for (int i = 0; i < 10; i++)
	{
		if (BookInf[i].exsist == 0)
		{
			BookInf[i].book_Number = Input_book_Number;
			strcpy(BookInf[i].book_Name, Input_book_Name);
			strcpy(BookInf[i].author_Name, Input_author_Name);
			BookInf[i].RuKu_Time = Input_RuKu_Time;
			BookInf[i].ChuBan_Time = Input_ChuBan_Time;
			BookInf[i].index = 1;
			BookInf[i].exsist = 1;
			if (BookInfSaveF(i) == 0)
			{
				printf("书籍入库成功，即将返回菜单\n");
				ShuKuInfF();
				exit(0);
			}
		}
	}
}

void ChuKu()
{
	long Input_book_Number;
	ReInput_ChuKu_Number:
	printf("请输入需要出库的书籍编号：");
	scanf("%ld", &Input_book_Number);
	for (int i = 0; i < 100; i++)
	{
		if (Input_book_Number == BookInf[i].book_Number)
		{
			BookInf[i].index = 0;
			if (BookInfSave_All_F() == 0)
			{
				printf("书籍出库成功，即将返回菜单\n");
				ShuKuInfF();
				exit(0);
			}
		}
		else if (i == 99 && Input_book_Number != BookInf[i].book_Number)
		{
			printf("未在库中找到对应编号书籍，请重新输入\n");
			goto ReInput_ChuKu_Number;
		}
	}
}