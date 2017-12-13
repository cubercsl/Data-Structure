#include "BinSerach.h"					// 顺序查找头文件

int main(void)
{
	int elem[] = {8, 11, 23, 34, 39, 46, 68, 71, 86};
	int n =9;
	int k, p;
	char c = 'x';
	
	cout << "查找表为：" << endl;
	Display(elem, n);			

	while (c != '0')	{
        cout << endl << "1. 递归查找元素.";
        cout << endl << "2. 迭代查找元素.";
        cout << endl << "3. 显示查找表.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~3):";
		cin >> c;
		switch (c) 	{
		    case '1':
            	cout << endl << "输入要元素的值:";
			    cin >> k;
				p = BinSerach(elem, 0, n - 1, k);	// 递归的折半查找 
				if (p >= 0)	// 查找成功
					cout << "查找成功,元素" << k << "的位置为:" << p << endl;
				else		// 查找失败
					cout << "查找失败!" << endl;
			    break;
		    case '2':
            	cout << endl << "输入要元素的值:";
			    cin >> k;
				p = BinSerach(elem, n, k);	// 递归的折半查找 
				if (p >= 0)	// 查找成功
					cout << "查找成功,元素" << k << "的位置为:" << p << endl;
				else		// 查找失败
					cout << "查找失败!" << endl;
			    break;
           	case '3':
			    Display(elem, n);			
			    break;
		}
	}

	system("PAUSE");
	return 0;

}
