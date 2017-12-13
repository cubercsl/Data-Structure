#include "Calculator.h"

int main(void)
{
	char c = '1';

    while (c != '0')
	{
        cout << endl << "1. 后缀式的计算.";
        cout << endl << "2. 中缀式转换为后缀式.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~2):";
		cin >> c;
		switch (c) 	{
			case '1':
      			GetChar();              // 读取回车符 
      			try { 
		     		PostfixExpressionCalculation();
      			}
	    		catch (Error err)	{	// 捕捉并处理异常
	         		cout << endl;
		     		err.Show();			// 显示异常信息
	    		}
				break;
	       case '2':
      			GetChar();              // 读取回车符 
      			try { 
		     		InfixInToPostfix();
      			}
	    		catch (Error err)	{	// 捕捉并处理异常
	         		cout << endl;
		     		err.Show();			// 显示异常信息
	    		}
				break;
		}
	}

	system("PAUSE"); 
	return 0;   
}
