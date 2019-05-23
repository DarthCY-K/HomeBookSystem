#include <iostream>
#include <string>

using namespace std;

class UserInterface
{
public:
	
	int op_Code = 0;

	void EnterUser()
	{	
		
		cout << "身份验证成功" << endl << "您的身份为：用户" << endl << "根据您的权限等级，本系统提供以下服务：" << endl;
		cout << "1.浏览\t2.借阅\t3.归还\t4.查询" << endl << "5.催还" << endl;
		cout << "请输入您需要的服务代码：";
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