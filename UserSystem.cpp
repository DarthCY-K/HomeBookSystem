#include <iostream>
#include <string>

using namespace std;

class UserInterface
{
public:
	
	int op_Code = 0;

	void EnterUser()
	{	
		
		cout << "�����֤�ɹ�" << endl << "�������Ϊ���û�" << endl << "��������Ȩ�޵ȼ�����ϵͳ�ṩ���·���" << endl;
		cout << "1.���\t2.����\t3.�黹\t4.��ѯ" << endl << "5.�߻�" << endl;
		cout << "����������Ҫ�ķ�����룺";
		cin >> op_Code;

		switch (op_Code)
		{
			case 1:
				LiuLan();
				break;
		}
	}

private:
	int user_Password = 452710557;
	string user_Name = "DarthCY";


	void LiuLan()
	{

	}

	void JieYue(int book_Number)
	{

	}

	void GuiHuan(int book_Number)
	{

	}

	void ChaXun(int book_Number)
	{

	}

	void CuiHuan(int book_Number)
	{

	}

};