#include "LinkQueue.h"	// 链队列类

int main(void)
{
	char c = '1';
    LinkQueue<int> qa;
    int x;

    while (c != '0')
	{
        cout << endl << "1. 生成队列.";
        cout << endl << "2. 显示队列.";
        cout << endl << "3. 入队列.";
        cout << endl << "4. 出队列.";
        cout << endl << "5. 取队列头.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~5):";
		cin >> c;
		switch (c)		{
			case '1':
                qa.Clear(); 
				cout << endl << "输入e(e = 0时退出)";
				cin >> x;
				while (x != 0)	{
					qa.EnQueue(x);
					cin >> x;
				}
				break;
	       case '2':
				cout << endl;
			    qa.Traverse(Write<int>);
				break;
		   case '3':
			    cout << endl << "输入元素值:";
			    cin >> x;
			    qa.EnQueue(x);
			    break;
           case '4':
			    qa.DelQueue(x);
			    cout << endl << "队头元素值为 " << x << " ." << endl;
			    break;
           case '5':
			    qa.GetHead(x);
			    cout << endl << "队头元素值为 " << x << " ." << endl;
			    break;
		}
	}

	system("PAUSE");
	return 0; 
}


