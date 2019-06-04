#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

int read_TimesUser = 0;
int read_TimesBook = 0;

struct UserInf
{
	char User_Name[32];	//用户名字
	char User_Password[20];	//用户密码
	char User_Email[20];	//用户邮箱
	int books_Have = 0;	//拥有的书籍数
	long books_Have_Number[5] = { 0,0,0,0,0 };	//拥有的书籍的编号，0为空
	int index = 0;	//0表示不存在
	int Admin = 0;	//0表示不是管理员

}UserInf[100];	//用户信息结构体

struct BookInf
{
	long book_Number = 0;		//书籍编号即为结构体[]中内容
	char book_Name[20];	//书名
	char author_Name[32];	//作者名
	long RuKu_Time = 0;	//入库时间
	long ChuBan_Time = 0;	//出版时间
	long JieChu_Time = 0;	//被借出时的时间
	int index = 0;	//0表示不存在 1表示在库 2表示借出 3表示遗损
}BookInf[100];


int UserInfReadF();
int UserInfSaveF(int i);
int UserInfSave_All_F();

int BookInfReadF();
int BookInfSaveF(int i);
int BookInfSave_All_F();

void LoginF();
void RegisterF();
void FindPassword(int i);

void UserSystem(int UserIndex);
	void LiuLan(int UserIndex);
	void JieYue(int UserIndex);
	void GuiHuan(int UserIndex);
	void ChaXun(int UserIndex);
	void CuiHuan(int UserIndex);


void AdminSystem(int UserIndex);
	void YiSun(int UserIndex);
	void ShuKuInfF(int UserIndex);
		void ChuKu(int UserIndex);
		void RuKu(int UserIndex);

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
	if(fp)
	while (!feof(fp) && i < 100)
	{
		fscanf(fp, "%s", UserInf[i].User_Name);
		fscanf(fp, "%s", UserInf[i].User_Password);
		fscanf(fp, "%s", UserInf[i].User_Email);
		fscanf(fp, "%d", &UserInf[i].index);
		fscanf(fp, "%d", &UserInf[i].Admin);
		fscanf(fp, "%d", &UserInf[i].books_Have);
		fscanf(fp, "%ld", &UserInf[i].books_Have_Number[0]);
		fscanf(fp, "%ld", &UserInf[i].books_Have_Number[1]);
		fscanf(fp, "%ld", &UserInf[i].books_Have_Number[2]);
		fscanf(fp, "%ld", &UserInf[i].books_Have_Number[3]);
		fscanf(fp, "%ld", &UserInf[i].books_Have_Number[4]);
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
			fprintf(fp, "%s     ", UserInf[i].User_Name);
			fprintf(fp, "%s     ", UserInf[i].User_Password);
			fprintf(fp, "%s     ", UserInf[i].User_Email);
			fprintf(fp, "%d     ", UserInf[i].index);
			fprintf(fp, "%d     ", UserInf[i].Admin);
			fprintf(fp, "%d     ", UserInf[i].books_Have);
			fprintf(fp, "%ld ", UserInf[i].books_Have_Number[0]);
			fprintf(fp, "%ld ", UserInf[i].books_Have_Number[1]);
			fprintf(fp, "%ld ", UserInf[i].books_Have_Number[2]);
			fprintf(fp, "%ld ", UserInf[i].books_Have_Number[3]);
			fprintf(fp, "%ld\n", UserInf[i].books_Have_Number[4]);
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
		fprintf(fp, "%s     ", UserInf[i].User_Name);
		fprintf(fp, "%s     ", UserInf[i].User_Password);
		fprintf(fp, "%s     ", UserInf[i].User_Email);
		fprintf(fp, "%d     ", UserInf[i].index);
		fprintf(fp, "%d     ", UserInf[i].Admin);
		fprintf(fp, "%d     ", UserInf[i].books_Have);
		fprintf(fp, "%ld ", UserInf[i].books_Have_Number[0]);
		fprintf(fp, "%ld ", UserInf[i].books_Have_Number[1]);
		fprintf(fp, "%ld ", UserInf[i].books_Have_Number[2]);
		fprintf(fp, "%ld ", UserInf[i].books_Have_Number[3]);
		fprintf(fp, "%ld\n", UserInf[i].books_Have_Number[4]);
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
			fprintf(fp, "%ld     ", BookInf[i].book_Number);
			fprintf(fp, "%s     ", BookInf[i].book_Name);
			fprintf(fp, "%s     ", BookInf[i].author_Name);
			fprintf(fp, "%ld     ", BookInf[i].RuKu_Time);
			fprintf(fp, "%ld     ", BookInf[i].ChuBan_Time);
			fprintf(fp, "%ld     ", BookInf[i].JieChu_Time);
			fprintf(fp, "%d\n", BookInf[i].index);
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
	while (!feof(fp) && i < 100 && BookInf[i].index != 0)
	{
		fprintf(fp, "%ld     ", BookInf[i].book_Number);
		fprintf(fp, "%s     ", BookInf[i].book_Name);
		fprintf(fp, "%s     ", BookInf[i].author_Name);
		fprintf(fp, "%ld     ", BookInf[i].RuKu_Time);
		fprintf(fp, "%ld     ", BookInf[i].ChuBan_Time);
		fprintf(fp, "%ld     ", BookInf[i].JieChu_Time);
		fprintf(fp, "%d\n", BookInf[i].index);
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
		fscanf(fp, "%ld", &BookInf[i].JieChu_Time);
		fscanf(fp, "%d", &BookInf[i].index);
		i++;
	}
	fclose(fp);
	return 0;
}



void RegisterF()
{
	char Input_regName[20], Input_regPassword[20], Input_regEmail[20];
	printf("请输入用户名和密码\n");
	printf("用户名：");
	getchar();
	gets_s(Input_regName,32);
	
	CheckExName:for (int i = 0; i < 100; i++)
	{
		if (strcmp(Input_regName, UserInf[i].User_Name) == 0)
		{
			printf("检测到用户名与已有用户冲突，请重新输入！\n");
			printf("用户名：");
			scanf("%s", Input_regName);
			goto CheckExName;
		}
		else
			break;
	}

	printf("请输入密码：");
	gets_s(Input_regPassword, 20);
	printf("请输入邮箱：");
	gets_s(Input_regEmail, 20);

	for (int i = 0; i < 100; i++)
	{
		if (UserInf[i].index == 0)
		{
			strcpy(UserInf[i].User_Name, Input_regName);
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
		if (strcmp(Input_Account, UserInf[i].User_Name) == 0)			//用户名正确
		{
			printf("密码：");
			scanf("%s", Input_Password);
			
			CheckPass:
			if (strcmp(Input_Password, UserInf[i].User_Password) == 0)		//用户名正确 密码正确
			{

				if (UserInf[i].Admin == 0)
				{
					printf("认证成功，即将进入家庭图书系统\n");
					UserSystem(i);
					exit(0);
				}
				else
				{
					printf("认证成功，即将进入家庭图书系统后台\n");
					AdminSystem(i);
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
					FindPassword(i);		//前往找回密码函数
					exit(0);
				}
			}
		}
		else		//用户名错误
		{
			for (int j = 0; j < 10; j++)
				if (strcmp(Input_Account, UserInf[j].User_Name) == 0)
				{
					j = 10;
				}
				else if (j == 9 && strcmp(Input_Account, UserInf[j].User_Name) != 0)
				{
					printf("此用户不存在，请重新输入用户名：");
					scanf("%s", Input_Account);
					goto CheckName;		//返回用户名验证

				}
		}
	}
}

void FindPassword(int i)
{
	char Input_Email[20];
	int SpecialNumber = 4527, Input_SpecialNumber = 0;

	printf("若要找回密码，请输入注册时所使用的邮箱，我们将会发送一份包含特殊代码的邮件至注册邮箱\n");
CheckEmail:printf("请输入注册邮箱：");
	scanf("%s", Input_Email);

	if (strcmp(Input_Email, UserInf[i].User_Email) == 0)
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

			if (UserInfSave_All_F() == 0)
			{
				printf("修改成功！即将返回账号验证系统\n");
				LoginF();
				return;// exit(0);
			}
			else
			{
				printf("UserInf.darthcy 文件保存失败，请联系管理员\n");
				printf("即将返回主菜单\n");
				main();
				return;// exit(0);
			}
			return;

		}
		else
		{
			printf("特殊代码验证失败，请重新输入！\n");
			goto Re_specNumber;
		}
			

	}
	else
	{
		int yOn;
		printf("注册邮箱错误，是否再次输入？\n");
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




void UserSystem(int UserIndex)
{
	int Choice = 0;
	if (read_TimesBook == 0)
	{
		if (BookInfReadF() == 0)
			read_TimesBook++;
		else
			printf("BookInf.darthcy 文件读取失败，请联系管理员\n");
	}		
	printf("\n欢迎登入用户系统，%s,请选择您需要的功能\n",UserInf[UserIndex].User_Name);
	printf("1.浏览\t2.借阅\t3.归还\t4.查询\n5.催还\n");
	scanf("%d", &Choice);
	ChoseW:switch (Choice)
	{
		case 1:
			LiuLan(UserIndex);
			break;
		case 2:
			CuiHuan(UserIndex);
			JieYue(UserIndex);
			break;
		case 3:
			GuiHuan(UserIndex);
			break;
		case 4:
			CuiHuan(UserIndex);
			break;
		case 5:
		default:
			printf("输入错误，请重新输入：");
			scanf("%d", &Choice);
			goto ChoseW;
	}
	return;
}

void LiuLan(int UserIndex)
{
	int Choice = 3;
	for (int i = 0; i < 100; i++)
	{
		if (BookInf[i].index != 0)
		{
			printf("书籍编号：%ld\n",BookInf[i].book_Number);
			printf("书籍名字：%s\n",BookInf[i].book_Name);
			printf("书籍作者：%s\n", BookInf[i].author_Name);
			printf("出版时间：%ld\n", BookInf[i].ChuBan_Time);
			printf("书籍状态：");
			if (BookInf[i].index == 2)
				printf("借出\n\n");
			else if (BookInf[i].index == 3)
				printf("遗损\n\n");
			else if (BookInf[i].index == 1)
				printf("在库\n\n");
		}
	}
	printf("\n是否访问借阅模块?\n");
	printf("1.是     2.否\n");
	scanf("%d", &Choice);
ReInputChoice_LiuLan:
	switch (Choice)
	{
		case 1:
			CuiHuan(UserIndex);
			JieYue(UserIndex);
			break;
		case 2:
			UserSystem(UserIndex);
			break;
		case 3:
			printf("错误输入,请重新输入:");
			scanf("%d", &Choice);
			goto ReInputChoice_LiuLan;
	}

}

void JieYue(int UserIndex)	//借阅模块
{
	if (UserInf[UserIndex].books_Have >= 5)
	{
		printf("当前已达到最大借书数量,请还完一部分再来借阅\n");
		UserSystem(UserIndex);
		return;
	}

	int input_bookNumber;
	Re_bookNumber:
	printf("请输入书号：");
	scanf("%d", &input_bookNumber);
	input_bookNumber--;
	if (BookInf[input_bookNumber].index == 1)
	{
		time_t CurrentTime = time(NULL);
		BookInf[input_bookNumber].JieChu_Time = CurrentTime;
		BookInf[input_bookNumber].index = 2;
		UserInf[UserIndex].books_Have++;
		for (int j = 0; j < 5; j++)
		{
			if (UserInf[UserIndex].books_Have_Number[j] == 0)
			{
				UserInf[UserIndex].books_Have_Number[j] = input_bookNumber + 1;
				j = 5;
			}
		}

		if (BookInfSave_All_F() == 0 && UserInfSave_All_F() == 0)
			printf("书籍 [%s] 成功借出！\n", BookInf[input_bookNumber].book_Name);
		else
			printf("BookInf.darthcy 变更信息保存失败，请联系管理员\n");

		printf("即将退出系统\n");
		UserSystem(UserIndex);// exit(0);
	}
	else if (BookInf[input_bookNumber].index == 2)
	{
		printf("本书 [%s] 当前已借出/出库，借出操作失败！\n", BookInf[input_bookNumber].book_Name);
		UserSystem(UserIndex);//exit(0);
	}
	else
	{
		printf("输入的书号不存在，请重新输入\n");
		goto Re_bookNumber;
	}

}

void GuiHuan(int UserIndex)
{
	long Input_book_Number;
Re_GuiHuan:
	printf("请输入书号：");
	scanf("%ld", &Input_book_Number);
	for (int i = 0; i < 100; i++)
	{
		if (Input_book_Number == BookInf[i].book_Number)
		{
			if (BookInf[i].index == 1)
			{
				printf("书籍《%s》已在库，无需归还\n", BookInf[i].book_Name);
				goto Re_GuiHuan;
			}
			else
			{
				BookInf[i].JieChu_Time = 0;
				BookInf[i].index = 1;
				UserInf[UserIndex].books_Have--;
				for (int j = 0; j < 5; j++)
				{
					if (UserInf[UserIndex].books_Have_Number[j] == BookInf[i].book_Number)
					{
						UserInf[UserIndex].books_Have_Number[j] = 0;
						j = 5;
					}
				}
			}
				


			if (BookInfSave_All_F() == 0 && UserInfSave_All_F() == 0)
			{

				printf("书籍[%s]归还成功，即将返回上一级菜单\n", BookInf[i].book_Name);
				UserSystem(UserIndex);
				exit(0);
			}
		}
		else if (i == 99 && Input_book_Number != BookInf[i].book_Number)
		{
			printf("未在书库中查询到书籍编号为%ld的书籍，请重新输入\n", Input_book_Number);
			goto Re_GuiHuan;
		}
	}
}

void ChaXun(int UserIndex)
{
	int Choice = 0;

ReInput_Choice_ChaXun_0:
	printf("您已进入信息查询模块，%s，请输入需要的功能\n",UserInf[UserIndex].User_Name);
	printf("1.查看书籍\t2.查看阅读记录\n");
	scanf("%d", &Choice);

	if (Choice == 1)
	{
		long Input_bookNumber = 0;
		printf("您已进入书籍信息查看模块\n");
	ReInput_bookNumber_ChaXun_0:
		printf("请输入书号：");
		scanf("%ld", &Input_bookNumber);

		for (int i = 0; i < 100; i++)
		{
			if (BookInf[i].book_Number == Input_bookNumber)
			{
				if (BookInf[i].index == 1)
				{
					printf("书籍编号：%ld\n", BookInf[i].book_Number);
					printf("书籍名字：%s\n", BookInf[i].book_Name);
					printf("书籍作者：%s\n", BookInf[i].author_Name);
					printf("出版时间：%ld\n", BookInf[i].ChuBan_Time);
					printf("书籍状态：在库\n");
				}
				else if (BookInf[i].index == 2)
				{
					printf("书籍编号：%ld\n", BookInf[i].book_Number);
					printf("书籍名字：%s\n", BookInf[i].book_Name);
					printf("书籍作者：%s\n", BookInf[i].author_Name);
					printf("出版时间：%ld\n", BookInf[i].ChuBan_Time);
					printf("书籍状态：借出\n");
				}
				else if (BookInf[i].index == 3)
				{
					printf("书籍编号：%ld\n", BookInf[i].book_Number);
					printf("书籍名字：%s\n", BookInf[i].book_Name);
					printf("书籍作者：%s\n", BookInf[i].author_Name);
					printf("出版时间：%ld\n", BookInf[i].ChuBan_Time);
					printf("书籍状态：遗损\n");
				}
				i = 100;
			}
			else if (i = 99)
			{
				int Choice = 0;
				printf("输入的书号不存在\n");
				printf("1.用户模块\t2.再次输入\n");
				printf("请输入需要的功能：");
				scanf("%d", &Choice);
				if (Choice == 1)
					UserSystem(UserIndex);
				else if (Choice == 2)
					goto ReInput_bookNumber_ChaXun_0;
				break;
			}
		}
	}
	else if (Choice == 2)
	{
		char Input_userName[32];
		printf("您已进入用户信息查询模块\n");
ReInput_UserName_ChaXun_0:
		printf("请输入用户名：");
		getchar();
		fflush(stdin);
		gets_s(Input_userName, 32);

		for (int i = 0; i < 100; i++)
		{
			if (strcmp(UserInf[i].User_Name, Input_userName) == 0)
			{
				printf("用户编号：%s", UserInf[i].User_Name);
				printf("用户邮箱：%s", UserInf[i].User_Email);
				printf("用户已借书数量：%d", UserInf[i].books_Have);
				if (UserInf[i].books_Have != 0)
				{
					for (int j = 0; j < 5; j++)
					{
						if (UserInf[i].books_Have_Number[j] != 0)
						{
							for (int k = 0; k < 100; k++)
							{
								if (UserInf[i].books_Have_Number[j] == BookInf[k].book_Number)
								{
									printf("书籍编号：%ld\n", BookInf[k].book_Number);
									printf("书籍名字：%s\n", BookInf[k].book_Name);
									printf("书籍作者：%s\n", BookInf[k].author_Name);
									printf("出版时间：%ld\n", BookInf[k].ChuBan_Time);
									k = 100;
								}
							}
						}
					}
				}
				i = 100;
			}
			else if (i == 99)
			{
				int Choice = 0;
				printf("找不到输入的用户名，请选择\n");
			ReInput_Choice_ChaXun_2:
				printf("1.重新输入用户名\t2.返回用户界面\n");
				scanf("%d", &Choice);
				if (Choice == 1)
					goto ReInput_UserName_ChaXun_0;
				else if (Choice == 2)
					UserSystem(UserIndex);
				else
				{
					printf("输入有误，请重新输入\n");
					goto ReInput_Choice_ChaXun_2;
				}

			}

		}
	}
	else
	{
		int Choice = 0;
		printf("输入有误，请选择\n");
		printf("1.返回查询模块\t2.返回用户界面\n");
		printf("请输入：");
		scanf("%d", &Choice);

ReInput_Choice_ChaXun_1:
		if (Choice == 1)
			goto ReInput_Choice_ChaXun_0;
		else if (Choice == 2)
			UserSystem(UserIndex);
		else
		{
			printf("输入有误，请重新输入：");
			scanf("%d", &Choice);
			goto ReInput_Choice_ChaXun_1;
		}
	}
}

void CuiHuan(int UserIndex)
{
	time_t CurrentTime = time(NULL);
	if (UserInf[UserIndex].books_Have != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (BookInf[UserInf[UserIndex].books_Have_Number[i]].index == 2 && UserInf[UserIndex].books_Have_Number[i] != 0 && ((CurrentTime - BookInf[UserInf[UserIndex].books_Have_Number[i]].JieChu_Time) / 3600 / 24) > 30)
			{
				printf("您借出的书籍[%s]已经借出了 %ld 天,超出了规定的30天时间，在归还之前不能继续借书，请尽快归还\n", BookInf[UserInf[UserIndex].books_Have_Number[i] - 1].book_Name, (CurrentTime - BookInf[UserInf[UserIndex].books_Have_Number[i]].JieChu_Time - BookInf[UserInf[UserIndex].books_Have_Number[i] - 1].JieChu_Time) / 3600 / 24);
			}
		}
	}
}


void AdminSystem(int UserIndex)
{
	int Choice = 0;
	if (read_TimesBook == 0)
	{
		if (BookInfReadF() == 0)
			read_TimesBook++;
		else
			printf("BookInf.darthcy 文件读取失败，请联系管理员\n");
	}
	printf("\n欢迎登入管理系统,%s，请选择您需要的功能\n",UserInf[UserIndex].User_Name);
	printf("1.书库信息\t2.遗损处理\t3.一键删库\n");
	scanf("%d", &Choice);
	ChoseW_admin:switch (Choice)
	{
		case 1:
			ShuKuInfF(UserIndex);
			break;
		case 2:
			YiSun(UserIndex);
			break;
		case 3:
			printf("本功能尚未开放\n");
			AdminSystem(UserIndex);
			break;
		default:
			printf("输入错误，请重新输入：");
			scanf("%d", &Choice);
			goto ChoseW_admin;
	}
}

void YiSun(int UserIndex)
{
	long Input_BookNumber = 0;
	printf("您已进入书籍遗损系统，管理员 %s\n", UserInf[UserIndex].User_Name);
ReInput_YiSun:
	printf("请输入遗损处理编号：");
	scanf("%ld", &Input_BookNumber);
	if (BookInf[Input_BookNumber].index != 0)
	{
		if (BookInf[Input_BookNumber].index == 1)
		{
			BookInf[Input_BookNumber].index = 3;
			if (BookInfSave_All_F() == 0)
			{
				int Choice = 0;
				printf("书籍[%s]遗损标记成功，请选择\n", BookInf[Input_BookNumber].book_Name);
				printf("1.返回书库信息界面\t2.返回管理员界面\t3.重新输入\t4.关闭程序\n");
			ReInput_Choice_YiSun_0:
				scanf("%d", &Choice);
				switch (Choice)
				{
				case 1:
					ShuKuInfF(UserIndex);
					break;
				case 2:
					AdminSystem(UserIndex);
					break;
				case 3:
					goto ReInput_YiSun;
					break;
				case 4:
					exit(0);
				default:
					printf("输入有误，请重新输入：");
					goto ReInput_Choice_YiSun_0;
					break;
				}
			}
		}
		else
		{
			int Choice = 0;
			printf("本书已处于");
			if (BookInf[Input_BookNumber].index == 2)
				printf("[借出]");
			else if (BookInf[Input_BookNumber].index == 3)
				printf("[遗损]");
			printf("状态，手动遗损失败\n");

			printf("请输入选择：");
			printf("1.返回书库信息界面\t2.返回管理员界面\t3.重新输入\t4.关闭程序\n");
			scanf("%d", &Choice);
		ReInput_Choice_YiSun_1:
			scanf("%d", &Choice);
			switch (Choice)
			{
			case 1:
				ShuKuInfF(UserIndex);
				break;
			case 2:
				AdminSystem(UserIndex);
				break;
			case 3:
				goto ReInput_YiSun;
				break;
			case 4:
				exit(0);
			default:
				printf("输入有误，请重新输入：");
				goto ReInput_Choice_YiSun_1;
				break;
			}
		}
	}
}

void ShuKuInfF(int UserIndex)
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
			RuKu(UserIndex);
			break;
		case 2:
			ChuKu(UserIndex);
			break;
		case 3:
			printf("输入有误，请重新输入\n");
			goto Ru$Chu_ReInput;
	}
	return;
}

void RuKu(int UserIndex)
{
	int Input_book_Number;
	char Input_book_Name[20], Input_author_Name[10];
	long Input_RuKu_Time = 0, Input_ChuBan_Time = 0;

	printf("管理员,%s，您已进入新书入库模块",UserInf[UserIndex].User_Name);
	ReInput_Book_Number:
	printf("\n请输入书籍编号：");
	scanf("%d", &Input_book_Number);

	for (int i = Input_book_Number; i < 100; i++)
	{
		if (BookInf[i].book_Number != 0)
		{
			printf("此编号[%ld]已经有书，即将进入下一编号\n", Input_book_Number);
			i++;
		}
		else
		{
			Input_book_Number = i;
			i = 100;
		}
			
	}

	printf("\n请输入书籍名称：");
	getchar();
	fflush(stdin);
	gets_s(Input_book_Name, 20);
	for (int i = 0; i < 100; i++)
	{
		if (strcmp(Input_book_Name, BookInf[i].book_Name) == 0)
		{
			int Choice = 0;
			printf("书籍名称和已有书籍名称冲突，请选择\n");
			printf("1.返回书库信息界面\t2.返回管理员界面\t3.重新输入\t4.关闭程序\n");
		ReInput_Choice_RuKu_0:
			scanf("%d", &Choice);
			switch (Choice)
			{
			case 1:
				ShuKuInfF(UserIndex);
				break;
			case 2:
				AdminSystem(UserIndex);
				break;
			case 3:
				goto ReInput_Book_Number;
				break;
			case 4:
				exit(0);
			default:
				printf("输入有误，请重新输入：");
				goto ReInput_Choice_RuKu_0;
				break;
			}
			goto ReInput_Book_Number;
		}

	}
	printf("\n请输入作者名称：");
	gets_s(Input_author_Name, 32);

	printf("\n请输入出版时间：");
	scanf("%ld", &Input_ChuBan_Time);

	printf("\n请输入入库时间：");
	scanf("%ld", &Input_RuKu_Time);




	for (int i = 0; i < 100; i++)
	{
		if (BookInf[i].index == 0)
		{
			int Choice = 0;
			BookInf[i].book_Number = Input_book_Number;
			strcpy(BookInf[i].book_Name, Input_book_Name);
			strcpy(BookInf[i].author_Name, Input_author_Name);
			BookInf[i].RuKu_Time = Input_RuKu_Time;
			BookInf[i].ChuBan_Time = Input_ChuBan_Time;
			BookInf[i].index = 1;
			if (BookInfSaveF(i) == 0)
			{
				printf("书籍入库成功，请选择\n");
				printf("1.返回书库信息界面\t2.返回管理员界面\t3.继续入库\t4.关闭程序\n");
			ReInput_Choice_RuKu_1:
				scanf("%d", &Choice);
				switch (Choice)
				{
				case 1:
					ShuKuInfF(UserIndex);
					break;
				case 2:
					AdminSystem(UserIndex);
					break;
				case 3:
					goto ReInput_Book_Number;
					break;
				case 4:
					exit(0);
				default:
					printf("输入有误，请重新输入：");
					goto ReInput_Choice_RuKu_1;
					break;
				}
				exit(0);
			}
		}
	}
}

void ChuKu(int UserIndex)
{
	long Input_book_Number;
	ReInput_ChuKu_Number:
	printf("请输入需要出库的书籍编号：");
	scanf("%ld", &Input_book_Number);
	for (int i = 0; i < 100; i++)
	{
		if (Input_book_Number == BookInf[i].book_Number && BookInf[i].index == 1)
		{
			BookInf[i].index = 0;
			if (BookInfSave_All_F() == 0)
			{
				int Choice = 0;
				printf("书籍出库成功，请选择需要的功能\n");
				printf("1.返回书库信息界面\t2.返回管理员界面\t3.继续出库\t4.关闭程序\n");
			ReInput_Choice_ChuKu:
				scanf("%d", &Choice);
				switch (Choice)
				{
				case 1:
					ShuKuInfF(UserIndex);
					break;
				case 2:
					AdminSystem(UserIndex);
					break;
				case 3:
					goto ReInput_ChuKu_Number;
					break;
				case 4:
					exit(0);
				default:
					printf("输入有误，请重新输入：");
					goto ReInput_Choice_ChuKu;
					break;
				}
				exit(0);
			}
		}
		else if (i == 99 && Input_book_Number != BookInf[i].book_Number)
		{
			int Choice = 0;
			printf("未在库中找到对应编号书籍，请选择\n");
			printf("1.返回书库信息界面\t2.返回管理员界面\t3.继续出库\t4.关闭程序\n");
		ReInput_Choice_ChuKu_2:
			scanf("%d", &Choice);
			switch (Choice)
			{
			case 1:
				ShuKuInfF(UserIndex);
				break;
			case 2:
				AdminSystem(UserIndex);
				break;
			case 3:
				goto ReInput_ChuKu_Number;
				break;
			case 4:
				exit(0);
			default:
				printf("输入有误，请重新输入：");
				goto ReInput_Choice_ChuKu_2;
				break;
			}
		}
		else if (BookInf[i].index != 1)
		{
			int Choice = 0;
			printf("书籍[%s]已借出/出库，手动出库失败\n", BookInf[i].book_Name);
			printf("1.返回书库信息界面\t2.返回管理员界面\t3.继续出库\t4.关闭程序\n");
		ReInput_Choice_ChuKu_3:
			scanf("%d", &Choice);
			switch (Choice)
			{
			case 1:
				ShuKuInfF(UserIndex);
				break;
			case 2:
				AdminSystem(UserIndex);
				break;
			case 3:
				goto ReInput_ChuKu_Number;
				break;
			case 4:
				exit(0);
			default:
				printf("输入有误，请重新输入：");
				goto ReInput_Choice_ChuKu_3;
				break;
			}
		}
	}
}