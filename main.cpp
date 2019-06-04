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
	char User_Name[32];	//�û�����
	char User_Password[20];	//�û�����
	char User_Email[20];	//�û�����
	int books_Have = 0;	//ӵ�е��鼮��
	long books_Have_Number[5] = { 0,0,0,0,0 };	//ӵ�е��鼮�ı�ţ�0Ϊ��
	int index = 0;	//0��ʾ������
	int Admin = 0;	//0��ʾ���ǹ���Ա

}UserInf[100];	//�û���Ϣ�ṹ��

struct BookInf
{
	long book_Number = 0;		//�鼮��ż�Ϊ�ṹ��[]������
	char book_Name[20];	//����
	char author_Name[32];	//������
	long RuKu_Time = 0;	//���ʱ��
	long ChuBan_Time = 0;	//����ʱ��
	long JieChu_Time = 0;	//�����ʱ��ʱ��
	int index = 0;	//0��ʾ������ 1��ʾ�ڿ� 2��ʾ��� 3��ʾ����
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
		return 1;									//�ļ���ʧ�ܣ�����һ��1
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
		return 1;									//�ļ���ʧ�ܣ�����һ��1
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

int BookInfSave_All_F()		//�ļ���ȫ��д
{
	int i = 0;
	FILE* fp;
	if (fopen_s(&fp, "BookInf.darthcy", "w"))
	{
		printf("can not open the file\n");
		return 1;									//�ļ���ʧ�ܣ�����һ��1
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
	printf("�������û���������\n");
	printf("�û�����");
	getchar();
	gets_s(Input_regName,32);
	
	CheckExName:for (int i = 0; i < 100; i++)
	{
		if (strcmp(Input_regName, UserInf[i].User_Name) == 0)
		{
			printf("��⵽�û����������û���ͻ�����������룡\n");
			printf("�û�����");
			scanf("%s", Input_regName);
			goto CheckExName;
		}
		else
			break;
	}

	printf("���������룺");
	gets_s(Input_regPassword, 20);
	printf("���������䣺");
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
		if (strcmp(Input_Account, UserInf[i].User_Name) == 0)			//�û�����ȷ
		{
			printf("���룺");
			scanf("%s", Input_Password);
			
			CheckPass:
			if (strcmp(Input_Password, UserInf[i].User_Password) == 0)		//�û�����ȷ ������ȷ
			{

				if (UserInf[i].Admin == 0)
				{
					printf("��֤�ɹ������������ͥͼ��ϵͳ\n");
					UserSystem(i);
					exit(0);
				}
				else
				{
					printf("��֤�ɹ������������ͥͼ��ϵͳ��̨\n");
					AdminSystem(i);
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
					FindPassword(i);		//ǰ���һ����뺯��
					exit(0);
				}
			}
		}
		else		//�û�������
		{
			for (int j = 0; j < 10; j++)
				if (strcmp(Input_Account, UserInf[j].User_Name) == 0)
				{
					j = 10;
				}
				else if (j == 9 && strcmp(Input_Account, UserInf[j].User_Name) != 0)
				{
					printf("���û������ڣ������������û�����");
					scanf("%s", Input_Account);
					goto CheckName;		//�����û�����֤

				}
		}
	}
}

void FindPassword(int i)
{
	char Input_Email[20];
	int SpecialNumber = 4527, Input_SpecialNumber = 0;

	printf("��Ҫ�һ����룬������ע��ʱ��ʹ�õ����䣬���ǽ��ᷢ��һ�ݰ������������ʼ���ע������\n");
CheckEmail:printf("������ע�����䣺");
	scanf("%s", Input_Email);

	if (strcmp(Input_Email, UserInf[i].User_Email) == 0)
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

			if (UserInfSave_All_F() == 0)
			{
				printf("�޸ĳɹ������������˺���֤ϵͳ\n");
				LoginF();
				return;// exit(0);
			}
			else
			{
				printf("UserInf.darthcy �ļ�����ʧ�ܣ�����ϵ����Ա\n");
				printf("�����������˵�\n");
				main();
				return;// exit(0);
			}
			return;

		}
		else
		{
			printf("���������֤ʧ�ܣ����������룡\n");
			goto Re_specNumber;
		}
			

	}
	else
	{
		int yOn;
		printf("ע����������Ƿ��ٴ����룿\n");
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




void UserSystem(int UserIndex)
{
	int Choice = 0;
	if (read_TimesBook == 0)
	{
		if (BookInfReadF() == 0)
			read_TimesBook++;
		else
			printf("BookInf.darthcy �ļ���ȡʧ�ܣ�����ϵ����Ա\n");
	}		
	printf("\n��ӭ�����û�ϵͳ��%s,��ѡ������Ҫ�Ĺ���\n",UserInf[UserIndex].User_Name);
	printf("1.���\t2.����\t3.�黹\t4.��ѯ\n5.�߻�\n");
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
			printf("����������������룺");
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
			printf("�鼮��ţ�%ld\n",BookInf[i].book_Number);
			printf("�鼮���֣�%s\n",BookInf[i].book_Name);
			printf("�鼮���ߣ�%s\n", BookInf[i].author_Name);
			printf("����ʱ�䣺%ld\n", BookInf[i].ChuBan_Time);
			printf("�鼮״̬��");
			if (BookInf[i].index == 2)
				printf("���\n\n");
			else if (BookInf[i].index == 3)
				printf("����\n\n");
			else if (BookInf[i].index == 1)
				printf("�ڿ�\n\n");
		}
	}
	printf("\n�Ƿ���ʽ���ģ��?\n");
	printf("1.��     2.��\n");
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
			printf("��������,����������:");
			scanf("%d", &Choice);
			goto ReInputChoice_LiuLan;
	}

}

void JieYue(int UserIndex)	//����ģ��
{
	if (UserInf[UserIndex].books_Have >= 5)
	{
		printf("��ǰ�Ѵﵽ����������,�뻹��һ������������\n");
		UserSystem(UserIndex);
		return;
	}

	int input_bookNumber;
	Re_bookNumber:
	printf("��������ţ�");
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
			printf("�鼮 [%s] �ɹ������\n", BookInf[input_bookNumber].book_Name);
		else
			printf("BookInf.darthcy �����Ϣ����ʧ�ܣ�����ϵ����Ա\n");

		printf("�����˳�ϵͳ\n");
		UserSystem(UserIndex);// exit(0);
	}
	else if (BookInf[input_bookNumber].index == 2)
	{
		printf("���� [%s] ��ǰ�ѽ��/���⣬�������ʧ�ܣ�\n", BookInf[input_bookNumber].book_Name);
		UserSystem(UserIndex);//exit(0);
	}
	else
	{
		printf("�������Ų����ڣ�����������\n");
		goto Re_bookNumber;
	}

}

void GuiHuan(int UserIndex)
{
	long Input_book_Number;
Re_GuiHuan:
	printf("��������ţ�");
	scanf("%ld", &Input_book_Number);
	for (int i = 0; i < 100; i++)
	{
		if (Input_book_Number == BookInf[i].book_Number)
		{
			if (BookInf[i].index == 1)
			{
				printf("�鼮��%s�����ڿ⣬����黹\n", BookInf[i].book_Name);
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

				printf("�鼮[%s]�黹�ɹ�������������һ���˵�\n", BookInf[i].book_Name);
				UserSystem(UserIndex);
				exit(0);
			}
		}
		else if (i == 99 && Input_book_Number != BookInf[i].book_Number)
		{
			printf("δ������в�ѯ���鼮���Ϊ%ld���鼮������������\n", Input_book_Number);
			goto Re_GuiHuan;
		}
	}
}

void ChaXun(int UserIndex)
{
	int Choice = 0;

ReInput_Choice_ChaXun_0:
	printf("���ѽ�����Ϣ��ѯģ�飬%s����������Ҫ�Ĺ���\n",UserInf[UserIndex].User_Name);
	printf("1.�鿴�鼮\t2.�鿴�Ķ���¼\n");
	scanf("%d", &Choice);

	if (Choice == 1)
	{
		long Input_bookNumber = 0;
		printf("���ѽ����鼮��Ϣ�鿴ģ��\n");
	ReInput_bookNumber_ChaXun_0:
		printf("��������ţ�");
		scanf("%ld", &Input_bookNumber);

		for (int i = 0; i < 100; i++)
		{
			if (BookInf[i].book_Number == Input_bookNumber)
			{
				if (BookInf[i].index == 1)
				{
					printf("�鼮��ţ�%ld\n", BookInf[i].book_Number);
					printf("�鼮���֣�%s\n", BookInf[i].book_Name);
					printf("�鼮���ߣ�%s\n", BookInf[i].author_Name);
					printf("����ʱ�䣺%ld\n", BookInf[i].ChuBan_Time);
					printf("�鼮״̬���ڿ�\n");
				}
				else if (BookInf[i].index == 2)
				{
					printf("�鼮��ţ�%ld\n", BookInf[i].book_Number);
					printf("�鼮���֣�%s\n", BookInf[i].book_Name);
					printf("�鼮���ߣ�%s\n", BookInf[i].author_Name);
					printf("����ʱ�䣺%ld\n", BookInf[i].ChuBan_Time);
					printf("�鼮״̬�����\n");
				}
				else if (BookInf[i].index == 3)
				{
					printf("�鼮��ţ�%ld\n", BookInf[i].book_Number);
					printf("�鼮���֣�%s\n", BookInf[i].book_Name);
					printf("�鼮���ߣ�%s\n", BookInf[i].author_Name);
					printf("����ʱ�䣺%ld\n", BookInf[i].ChuBan_Time);
					printf("�鼮״̬������\n");
				}
				i = 100;
			}
			else if (i = 99)
			{
				int Choice = 0;
				printf("�������Ų�����\n");
				printf("1.�û�ģ��\t2.�ٴ�����\n");
				printf("��������Ҫ�Ĺ��ܣ�");
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
		printf("���ѽ����û���Ϣ��ѯģ��\n");
ReInput_UserName_ChaXun_0:
		printf("�������û�����");
		getchar();
		fflush(stdin);
		gets_s(Input_userName, 32);

		for (int i = 0; i < 100; i++)
		{
			if (strcmp(UserInf[i].User_Name, Input_userName) == 0)
			{
				printf("�û���ţ�%s", UserInf[i].User_Name);
				printf("�û����䣺%s", UserInf[i].User_Email);
				printf("�û��ѽ���������%d", UserInf[i].books_Have);
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
									printf("�鼮��ţ�%ld\n", BookInf[k].book_Number);
									printf("�鼮���֣�%s\n", BookInf[k].book_Name);
									printf("�鼮���ߣ�%s\n", BookInf[k].author_Name);
									printf("����ʱ�䣺%ld\n", BookInf[k].ChuBan_Time);
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
				printf("�Ҳ���������û�������ѡ��\n");
			ReInput_Choice_ChaXun_2:
				printf("1.���������û���\t2.�����û�����\n");
				scanf("%d", &Choice);
				if (Choice == 1)
					goto ReInput_UserName_ChaXun_0;
				else if (Choice == 2)
					UserSystem(UserIndex);
				else
				{
					printf("������������������\n");
					goto ReInput_Choice_ChaXun_2;
				}

			}

		}
	}
	else
	{
		int Choice = 0;
		printf("����������ѡ��\n");
		printf("1.���ز�ѯģ��\t2.�����û�����\n");
		printf("�����룺");
		scanf("%d", &Choice);

ReInput_Choice_ChaXun_1:
		if (Choice == 1)
			goto ReInput_Choice_ChaXun_0;
		else if (Choice == 2)
			UserSystem(UserIndex);
		else
		{
			printf("�����������������룺");
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
				printf("��������鼮[%s]�Ѿ������ %ld ��,�����˹涨��30��ʱ�䣬�ڹ黹֮ǰ���ܼ������飬�뾡��黹\n", BookInf[UserInf[UserIndex].books_Have_Number[i] - 1].book_Name, (CurrentTime - BookInf[UserInf[UserIndex].books_Have_Number[i]].JieChu_Time - BookInf[UserInf[UserIndex].books_Have_Number[i] - 1].JieChu_Time) / 3600 / 24);
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
			printf("BookInf.darthcy �ļ���ȡʧ�ܣ�����ϵ����Ա\n");
	}
	printf("\n��ӭ�������ϵͳ,%s����ѡ������Ҫ�Ĺ���\n",UserInf[UserIndex].User_Name);
	printf("1.�����Ϣ\t2.������\t3.һ��ɾ��\n");
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
			printf("��������δ����\n");
			AdminSystem(UserIndex);
			break;
		default:
			printf("����������������룺");
			scanf("%d", &Choice);
			goto ChoseW_admin;
	}
}

void YiSun(int UserIndex)
{
	long Input_BookNumber = 0;
	printf("���ѽ����鼮����ϵͳ������Ա %s\n", UserInf[UserIndex].User_Name);
ReInput_YiSun:
	printf("�������������ţ�");
	scanf("%ld", &Input_BookNumber);
	if (BookInf[Input_BookNumber].index != 0)
	{
		if (BookInf[Input_BookNumber].index == 1)
		{
			BookInf[Input_BookNumber].index = 3;
			if (BookInfSave_All_F() == 0)
			{
				int Choice = 0;
				printf("�鼮[%s]�����ǳɹ�����ѡ��\n", BookInf[Input_BookNumber].book_Name);
				printf("1.���������Ϣ����\t2.���ع���Ա����\t3.��������\t4.�رճ���\n");
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
					printf("�����������������룺");
					goto ReInput_Choice_YiSun_0;
					break;
				}
			}
		}
		else
		{
			int Choice = 0;
			printf("�����Ѵ���");
			if (BookInf[Input_BookNumber].index == 2)
				printf("[���]");
			else if (BookInf[Input_BookNumber].index == 3)
				printf("[����]");
			printf("״̬���ֶ�����ʧ��\n");

			printf("������ѡ��");
			printf("1.���������Ϣ����\t2.���ع���Ա����\t3.��������\t4.�رճ���\n");
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
				printf("�����������������룺");
				goto ReInput_Choice_YiSun_1;
				break;
			}
		}
	}
}

void ShuKuInfF(int UserIndex)
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
			RuKu(UserIndex);
			break;
		case 2:
			ChuKu(UserIndex);
			break;
		case 3:
			printf("������������������\n");
			goto Ru$Chu_ReInput;
	}
	return;
}

void RuKu(int UserIndex)
{
	int Input_book_Number;
	char Input_book_Name[20], Input_author_Name[10];
	long Input_RuKu_Time = 0, Input_ChuBan_Time = 0;

	printf("����Ա,%s�����ѽ����������ģ��",UserInf[UserIndex].User_Name);
	ReInput_Book_Number:
	printf("\n�������鼮��ţ�");
	scanf("%d", &Input_book_Number);

	for (int i = Input_book_Number; i < 100; i++)
	{
		if (BookInf[i].book_Number != 0)
		{
			printf("�˱��[%ld]�Ѿ����飬����������һ���\n", Input_book_Number);
			i++;
		}
		else
		{
			Input_book_Number = i;
			i = 100;
		}
			
	}

	printf("\n�������鼮���ƣ�");
	getchar();
	fflush(stdin);
	gets_s(Input_book_Name, 20);
	for (int i = 0; i < 100; i++)
	{
		if (strcmp(Input_book_Name, BookInf[i].book_Name) == 0)
		{
			int Choice = 0;
			printf("�鼮���ƺ������鼮���Ƴ�ͻ����ѡ��\n");
			printf("1.���������Ϣ����\t2.���ع���Ա����\t3.��������\t4.�رճ���\n");
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
				printf("�����������������룺");
				goto ReInput_Choice_RuKu_0;
				break;
			}
			goto ReInput_Book_Number;
		}

	}
	printf("\n�������������ƣ�");
	gets_s(Input_author_Name, 32);

	printf("\n���������ʱ�䣺");
	scanf("%ld", &Input_ChuBan_Time);

	printf("\n���������ʱ�䣺");
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
				printf("�鼮���ɹ�����ѡ��\n");
				printf("1.���������Ϣ����\t2.���ع���Ա����\t3.�������\t4.�رճ���\n");
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
					printf("�����������������룺");
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
	printf("��������Ҫ������鼮��ţ�");
	scanf("%ld", &Input_book_Number);
	for (int i = 0; i < 100; i++)
	{
		if (Input_book_Number == BookInf[i].book_Number && BookInf[i].index == 1)
		{
			BookInf[i].index = 0;
			if (BookInfSave_All_F() == 0)
			{
				int Choice = 0;
				printf("�鼮����ɹ�����ѡ����Ҫ�Ĺ���\n");
				printf("1.���������Ϣ����\t2.���ع���Ա����\t3.��������\t4.�رճ���\n");
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
					printf("�����������������룺");
					goto ReInput_Choice_ChuKu;
					break;
				}
				exit(0);
			}
		}
		else if (i == 99 && Input_book_Number != BookInf[i].book_Number)
		{
			int Choice = 0;
			printf("δ�ڿ����ҵ���Ӧ����鼮����ѡ��\n");
			printf("1.���������Ϣ����\t2.���ع���Ա����\t3.��������\t4.�رճ���\n");
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
				printf("�����������������룺");
				goto ReInput_Choice_ChuKu_2;
				break;
			}
		}
		else if (BookInf[i].index != 1)
		{
			int Choice = 0;
			printf("�鼮[%s]�ѽ��/���⣬�ֶ�����ʧ��\n", BookInf[i].book_Name);
			printf("1.���������Ϣ����\t2.���ع���Ա����\t3.��������\t4.�رճ���\n");
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
				printf("�����������������룺");
				goto ReInput_Choice_ChuKu_3;
				break;
			}
		}
	}
}