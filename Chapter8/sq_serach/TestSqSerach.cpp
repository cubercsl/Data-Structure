#include "SqSerach.h"		// 顺序查找头文件

int main(void)
{
	int elem[] = {61, 82, 104, 55, 116, 73, 45, 23, 98};
	int n =9;
	int k, p;
	char c = 'x';
	
	cout << "查找表为：" << endl;
	Display(elem, n);			

	while (c != '0')	{
        cout << endl << "1. 查找元素.";
        cout << endl << "2. 显示查找表.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~2):";
		cin >> c;
		switch (c) 	{
		    case '1':
            	cout << endl << "输入要元素的值:";
			    cin >> k;
				p = SqSerach(elem, n, k);
				if (p >= 0)	// 查找成功
					cout << "查找成功,元素" << k << "的位置为:" << p << endl;
				else		// 查找失败
					cout << "查找失败!" << endl;
			    break;
           	case '2':
			    Display(elem, n);			
			    break;
		}
	}

	system("PAUSE");
	return 0;
}
