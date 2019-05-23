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
			printf("UserInf.darthcy �ļ���Ϣ��ȡʧ�ܣ�����ϵ����Ա\n");
	}

	int LogOrReg = 0;
	printf("��ӭ�����ͥͼ�����ϵͳ�����ȵ�¼\n");
	printf("��¼(1)\tע��(2)\n");
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
		printf("��������,����������\n");
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
		return 1;									//�ļ���ʧ�ܣ�����һ��1
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
	return 0;										//�û���Ϣд��ɹ�������һ��0
}

int UserInfSaveF(int i)
{
	FILE* fp;
	if (fopen_s(&fp, "UserInf.darthcy", "a"))
	{
		printf("can not open the file\n");
		return 1;									//�ļ���ʧ�ܣ�����һ��1
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
		return 1;									//�ļ���ʧ�ܣ�����һ��1
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
		return 1;									//�ļ���ʧ�ܣ�����һ��1
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

int BookInfSave_All_F()		//�ļ���ȫ��д
{
	int i = 0;
	FILE* fp;
	if (fopen_s(&fp, "BookInf.darthcy", "w"))
	{
		printf("can not open the file\n");
		return 1;									//�ļ���ʧ�ܣ�����һ��1
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
	printf("�������û��������룺\n");
	printf("�û�����");
	scanf("%s", Input_regAccont);
	
	CheckExName:for (int i = 0; i < 100; i++)
	{
		if (strcmp(Input_regAccont, UserInf[i].User_Account) == 0)
		{
			printf("��⵽�û����������û���ͻ�����������룡\n");
			printf("�û�����");
			scanf("%s", Input_regAccont);
			goto CheckExName;
		}
		else
			break;
	}

	printf("���������룺");
	scanf("%s", Input_regPassword);
	printf("���������䣺");
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
				printf("ע��ɹ��������������˵�\n");
				main();
			}
			else
			{
				printf("ע��ʧ�ܣ�����ϵ����Ա\n");
				printf("�����������˵�\n");
				main();
			}
			exit(0);
		}
		else if (i == 99 && UserInf[i].index == 1)
		{
			printf("��ϵͳ��ע����������������ϵ����Ա���ӿ�ע������\n");
			printf("ע��ʧ�ܣ������������˵�\n");
			main();
			exit(0);
		}
	}
}

void LoginF()	//��¼����
{
	int i = 0;
	char Input_Account[20], Input_Password[20];	//�û�������˺ź�����
	printf("�������û���������\n");

	printf("�˺ţ�");
	scanf("%s", Input_Account);


CheckName:
	printf("��֤�У����Ժ�...\n");

	for (int i = 0; i < 100; i++)
	{
		if (strcmp(Input_Account, UserInf[i].User_Account) == 0)			//�û�����ȷ
		{
			printf("���룺");
			scanf("%s", Input_Password);
			
			CheckPass:
			if (strcmp(Input_Password, UserInf[i].User_Password) == 0)		//�û�����ȷ ������ȷ
			{

				if (UserInf[i].Admin == 0)
				{
					printf("��֤�ɹ������������ͥͼ��ϵͳ\n");
					UserSystem();
					exit(0);
				}
				else
				{
					printf("��֤�ɹ������������ͥͼ��ϵͳ��̨\n");
					AdminSystem();
					exit(0);
				}
			}
			else		//�û�����ȷ �������
					
			{
				int yOn = 0;
				printf("������������������������ѡ���һ�����\n");
				printf("1.��������\t2.�һ�����\n");
				scanf("%d", &yOn);
				if (yOn == 1)
				{
					printf("���������룺");
					scanf("%s", Input_Password);
					goto CheckPass;		//����������֤
				}
				else
				{
					FindPassword();		//ǰ���һ����뺯��
					exit(0);
				}
			}
		}
		else		//�û�������
		{
			for (int j = 0; j < 10; j++)
				if (strcmp(Input_Account, UserInf[j].User_Account) == 0)
				{
					j = 10;
				}
				else if (j == 9 && strcmp(Input_Account, UserInf[j].User_Account) != 0)
				{
					printf("���û������ڣ������������û�����");
					scanf("%s", Input_Account);
					goto CheckName;		//�����û�����֤

				}
		}
	}
}

void FindPassword()
{
	char Input_Email[20];
	int SpecialNumber = 4527, Input_SpecialNumber = 0;

	printf("��Ҫ�һ����룬������ע��ʱ��ʹ�õ����䣬���ǽ��ᷢ��һ�ݰ������������ʼ���ע������\n");
CheckEmail:printf("������ע�����䣺");
	scanf("%s", Input_Email);

	for (int i = 0; i < 100; i++)
	{
		if (Input_Email == UserInf[i].User_Email)
		{
			printf("��������ѷ��������䣬�����\n");
			Re_specNumber:
			printf("������������룺");
			scanf("%d", &Input_SpecialNumber);

			if (Input_SpecialNumber == SpecialNumber)
			{
				printf("���������֤�ɹ�\n");
				printf("�����������룺");
				scanf("%s", UserInf[i].User_Password);

				if (UserInfSaveF(i) == 0)
				{
					printf("�޸ĳɹ������������˺���֤ϵͳ\n");
					LoginF();
					exit(0);
				}
				else
				{
					printf("UserInf.darthcy �ļ�����ʧ�ܣ�����ϵ����Ա\n");
					printf("�����������˵�\n");
					main();
					exit(0);
				}
				exit(0);

			}
			else
			{
				printf("���������֤ʧ�ܣ����������룡\n");
				goto Re_specNumber;
			}
			

		}
		else if (Input_Email == UserInf[i].User_Email && i == 99)
		{
			int yOn;
			printf("δ��ѯ����ע�����䣬�Ƿ��ٴ����룿\n");
			printf("1.��/t2.��\n");
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
			printf("BookInf.darthcy �ļ���ȡʧ�ܣ�����ϵ����Ա\n");
	}		
	printf("\n��ӭ�����û�ϵͳ����ѡ������Ҫ�Ĺ���\n");
	printf("1.���\t2.����\t3.�黹\t4.��ѯ\n5.�߻�\n");
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
			printf("����������������룺");
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
			printf("�鼮��ţ�%l\n",BookInf[i].book_Number);
			printf("�鼮���֣�%s\n",BookInf[i].book_Name);
			printf("�Ƿ�����");
			if (BookInf[i].index == 0)
				printf("��\n");
			else
				printf("��\n");
		}
	}
}

void JieYue()	//����ģ��
{
	long input_bookNumber;

	Re_bookNumber:
	printf("��������ţ�");
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
					printf("�鼮 [%s] �ɹ������\n",BookInf[i].book_Name);
				else
					printf("BookInf.darthcy �����Ϣ����ʧ�ܣ�����ϵ����Ա\n");
				printf("�����˳�ϵͳ\n");
				return;// exit(0);
			}
			else
			{
				printf("���� [%s] ��ǰ�ѳ��⣬���ʧ�ܣ�\n",BookInf[i].book_Name);
				printf("�����˳�ϵͳ\n");
				return;//exit(0);
			}
		}
		else
		{
			if (i == 9 && input_bookNumber != BookInf[i].book_Number)
			{
				printf("δ�ҵ�����鼮��������������ţ�\n");
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
			printf("BookInf.darthcy �ļ���ȡʧ�ܣ�����ϵ����Ա\n");
	}
	printf("\n��ӭ�������ϵͳ����ѡ������Ҫ�Ĺ���\n");
	printf("1.�����Ϣ\t2.������\t3.һ��ɾ��\n");
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
			printf("��������δ����\n");
			AdminSystem();
			break;
		default:
			printf("����������������룺");
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
	printf("���ѽ��������Ϣϵͳ������Ա����ѡ����Ҫʹ�õĹ��ܣ�\n");
	Ru$Chu_ReInput:
	printf("1.���\t2.����\n");
	scanf("%d", &choose);
	getchar();				//������
	switch (choose)
	{
		case 1:
			RuKu();
			break;
		case 2:
			ChuKu();
			break;
		case 3:
			printf("������������������\n");
			goto Ru$Chu_ReInput;
	}
	return;
}

void RuKu()
{
	long Input_book_Number;
	char Input_book_Name[20], Input_author_Name[10];
	long Input_RuKu_Time = 0, Input_ChuBan_Time = 0;

	printf("����Ա�����ѽ����������ģ��");
	ReInput_Book_Number:
	printf("\n�������鼮��ţ�");
	scanf("%ld", &Input_book_Number);
	for (int i = 0; i < 100; i++)
	{
		if (Input_book_Number == BookInf[i].book_Number)
		{
			printf("�鼮��ź������鼮��ų�ͻ������������\n");
			goto ReInput_Book_Number;
		}

	}
	printf("\n�������鼮���ƣ�");
	scanf("%s", Input_book_Name, 20);
	for (int i = 0; i < 100; i++)
	{
		if (strcmp(Input_book_Name, BookInf[i].book_Name) == 0)
		{
			printf("�鼮���ƺ������鼮���Ƴ�ͻ������������\n");
			goto ReInput_Book_Number;
		}

	}
	printf("\n�������������ƣ�");
	scanf("%s", Input_author_Name,10);

	printf("\n���������ʱ�䣺");
	scanf("%ld", &Input_ChuBan_Time);

	printf("\n���������ʱ�䣺");
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
				printf("�鼮���ɹ����������ز˵�\n");
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
	printf("��������Ҫ������鼮��ţ�");
	scanf("%ld", &Input_book_Number);
	for (int i = 0; i < 100; i++)
	{
		if (Input_book_Number == BookInf[i].book_Number)
		{
			BookInf[i].index = 0;
			if (BookInfSave_All_F() == 0)
			{
				printf("�鼮����ɹ����������ز˵�\n");
				ShuKuInfF();
				exit(0);
			}
		}
		else if (i == 99 && Input_book_Number != BookInf[i].book_Number)
		{
			printf("δ�ڿ����ҵ���Ӧ����鼮������������\n");
			goto ReInput_ChuKu_Number;
		}
	}
}