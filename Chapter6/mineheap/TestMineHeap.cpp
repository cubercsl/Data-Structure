#include "MineHeap.h"

int main()
{
	int a[12]={80,57,99,35,23,11,74,29,62,16};
	MinHeap<int> ha(a,20,10);
	int e;
	char c = 'x'; 
	cout<<endl;
	
	cout << "最小堆序列为：" << endl;
	ha.Traverse(Write<int>);
	cout << endl << endl;	

    while (c != '0')	{
        cout << endl << "1. 插入元素.";
        cout << endl << "2. 删除堆顶元素.";
        cout << endl << "3. 显示堆.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~3):";
		cin >> c;
		switch (c) 	{
		    case '1':
            	cout << endl << "输入插入元素的值:";
			    cin >> e;
				ha.Insert(e);
			    break;
           	case '2':
				ha.DeleteTop(e);
				cout<<"删除的堆顶元素为:"<<e<<endl;
			    break;
		    case '3':
				cout << endl;
				ha.Traverse(Write<int>);
				break;
		}
	}

	
	system("pause");
	return 0;
}
