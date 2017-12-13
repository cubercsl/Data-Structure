#include "BinarySortTree.h"			// 二叉排序树类

int main(void)
{
	BinarySortTree<int> bt;
	int elem[] = {39, 68, 11, 23, 46, 34, 75, 86, 8, 71};
	int n = 10;
	
	for (int i = 0; i < n; i++)
		bt.Insert(elem[i]);			// 根据elem数组中的元素构造二叉排序树

	cout << "原二叉排序树:" << endl;
	DisplayBTWithTreeShape(bt);
	cout << endl;
	system("PAUSE");			

    char c = 'x';
    int x;

    while (c != '0')	{
        cout << endl << "1. 插入元素.";
        cout << endl << "2. 查找元素.";
        cout << endl << "3. 删除元素.";
        cout << endl << "4. 先序遍历.";
        cout << endl << "5. 中序遍历.";
        cout << endl << "6. 后序遍历.";
        cout << endl << "7. 显示二叉排序树.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~7):";
		cin >> c;
		switch (c) 	{
		    case '1':
            	cout << endl << "输入插入元素的值:";
			    cin >> x;
			    bt.Insert(x);
			    break;
           	case '2':
              	cout << endl << "输入查找元素的值:";
			    cin >> x;
			    if (bt.Find(x) == NULL)
                   	cout << endl << "元素不存在.";
              	else
                   	cout << endl << "元素存在.";
			    break;
		    case '3':
              	cout << endl << "输入删除元素的值:";
			    cin >> x;
			    bt.Delete(x);
			    break;
	         case '4':
				cout << endl;
				bt.PreOrder(Write<int>);
				break;
	         case '5':
				cout << endl;
				bt.InOrder(Write<int>);
				break;
	         case '6':
				cout << endl;
				bt.PostOrder(Write<int>);
				break;
	         case '7':
				cout << endl;
				DisplayBTWithTreeShape(bt);
				break;
		}
	}

	system("PAUSE");				
	return 0;							
}

