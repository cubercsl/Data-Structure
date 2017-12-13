#include "Polynomial.h"	// 多项式类
int main(void)
{
	char c = '1';
    Polynomial fa, fb, fc;
    PolyItem it;

    while (c != '0'){
        cout << endl << "1. 生成多项式.";
        cout << endl << "2. 显示多项式.";
        cout << endl << "3. 多项式加法.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~3):";
		cin >> c;
		switch (c) 	{
			case '1':
				cout << endl << "输入(coef, expn)(expn = -1时退出):" << endl;
				cin >> it.coef >> it.expn;
				while (it.expn != -1)	{
					fa.InsItem(it);
					cin >> it.coef >> it.expn;
				}
				break;
			case '2':
				cout << endl;
			    fa.Display();
			    cout << endl;
				break;
			case '3':
				// 输入fa
				fa.SetZero();		// 将fa设置为0
				cout << endl << "输入第一个多项式每项的系数和指数(coef, expn)(e = -1时退出):" << endl;
				cin >> it.coef >> it.expn;
				while (it.expn != -1)	{
					fa.InsItem(it);
					cin >> it.coef >> it.expn;
				}
			    
				// 输入fb
				fb.SetZero();		// 将fb设置为0
				cout << endl << "输入第二个多项式每项的系数和指数(coef, expn)(e = -1时退出):" << endl;
				cin >> it.coef >> it.expn;
				while (it.expn != -1)	{
					fb.InsItem(it);
					cin >> it.coef >> it.expn;
				}
			    
				fc = fa + fb;
			    cout << "fa:" << endl;			// 显示fa
				fa.Display();
			    cout << endl;			

			    cout << "fb:" << endl;			// 显示fa
				fb.Display();
			    cout << endl;			

			    cout << "fa + fb:" << endl;		// 显示fc = fa + fb
				fc.Display();
			    cout << endl;			
				break;
		}
	}
	system("PAUSE");				// 调用库函数system()
	return 0;						// 返回值0, 返回操作系统
}
