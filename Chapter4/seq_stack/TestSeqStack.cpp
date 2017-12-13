#include "SeqStack.h"	// 顺序栈类

int main(void)
{
	char c = '1';
    SeqStack<int> sa;
    int x;

    while (c != '0')
	{
        cout << endl << "1. 生成栈.";
        cout << endl << "2. 显示栈.";
        cout << endl << "3. 入栈.";
        cout << endl << "4. 出栈.";
        cout << endl << "5. 取栈顶.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~5):";
		cin >> c;
		switch (c) 	{
			case '1':
				sa.Clear();
 				cout << "输入e(e = 0时退出)" << endl ;
 				cin >> x;
				while (x != 0)	{
					sa.Push(x);
					cin >> x;
				}
				break;
	       case '2':
				cout << endl;
			    sa.Traverse(Write<int>);
				break;
		   case '3':
			    cout << endl << "输入元素值:";
			    cin >> x;
			    if (sa.Push(x) == SUCCESS)
			           cout << endl << "入栈成功." << endl;
                else
                       cout << endl << "空间不够，入栈失败." << endl;
			    break;
           case '4':
			    if (sa.Pop(x) == SUCCESS)
			           cout << endl << "栈顶元素值为：" << x << "." << endl;
                else
                       cout << endl << "栈为空。 " << endl;
			    break;
           case '5':
			    if (sa.Top(x) == SUCCESS)
			           cout << endl << "栈顶元素值为：" << x << "." << endl;
                else
                       cout << endl << "栈为空。 " << endl;
			    break;
		}
	}

	system("PAUSE"); 
	return 0;    
}


