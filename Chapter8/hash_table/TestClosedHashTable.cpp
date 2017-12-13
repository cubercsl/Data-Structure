#include "ClosedHashTable.h"				// 散列表类

int main(void)
{
	ClosedHashTable<int, int> ht(20, 19);
	int elem[] = {19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10, 79};
	int k, n = 12;
	Status state;
	
	for (int i = 0; i < n; i++)
		ht.Insert(elem[i]);				// 插入结点

	cout << "初始Hash表(#位置表示空，*位置表示删除过元素):" << endl;
	ht.Traverse(Write);
	cout << endl;
	
    char c = 'x';
    int x;

    while (c != '0')	{
        cout << endl << "1. 插入元素.";
        cout << endl << "2. 查找元素.";
        cout << endl << "3. 删除元素.";
        cout << endl << "4. 显示Hash表.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~4):";
		cin >> c;
		switch (c) 	{
		    case '1':
            	cout << endl << "输入插入元素的值:";
			    cin >> x;
			    if ((state = ht.Insert(x)) == SUCCESS)
                  	cout << endl << "插入成功.";
              	else if (state == OVER_FLOW)
                   	cout << endl << "表已满.";
              	else 
                   	cout << endl << "元素已存在.";
			    break;
           	case '2':
              	cout << endl << "输入查找元素的值:";
			    cin >> x;
			    if ((k = ht.Search(x)) == -1)
                   	cout << endl << "元素不存在.";
              	else
                   	cout << endl << "元素的位置是" << k;
			    break;
		    case '3':
              	cout << endl << "输入删除元素的值:";
			    cin >> x;
			    if (ht.Delete(x))
                   	cout << endl << "删除成功.";
              	else
                   	cout << endl << "元素不存在.";
			    break;
	         case '4':
				cout << endl;
			    ht.Traverse(Write<int>);
				break;
		}
	}
	
	system("PAUSE");			
	return 0;					
}

