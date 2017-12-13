#include "DblLinkList.h"		// 双向循环链表类
 
int main(void)
{
	char c = '1';
    DblLinkList<double> la,lb;
    double e;
	int i;

    while (c != '0')	{
        cout << endl << "1. 生成线性表.";
        cout << endl << "2. 显示线性表.";
        cout << endl << "3. 取指定元素值.";
        cout << endl << "4. 设置元素值.";
        cout << endl << "5. 删除元素.";
        cout << endl << "6. 插入元素.";
        cout << endl << "7. 元素定位.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~7):";
		cin >> c;
		switch (c) 		{
			case '1':
                la.Clear();
				cout << endl << "输入e(e = 0时退出):";
				cin >> e;
				while (e != 0)				{
					la.InsertElem(la.GetLength() + 1, e);
					cin >> e;
				}
				break;
			case '2':
			    lb = la;
			    lb.Traverse(Write<double>);
				break;
			case '3':
			    cout << endl << "输入元素位置:";
			    cin >> i;
			    if (la.GetElem(i, e) == NOT_PRESENT) 
					cout << "元素不存储." << endl;
				else
					cout << "元素:" << e << endl;
			    break;
			case '4':
			    cout << endl << "输入位置:";
			    cin >> i;
			    cout << endl << "输入元素值:";
			    cin >> e;
				if (la.SetElem(i, e) == RANGE_ERROR)
					cout << "位置范围错." << endl;
				else
					cout << "设置成功." << endl;
			    break;
			case '5':
			    cout << endl << "输入位置:";
			    cin >> i;
			    if (la.DeleteElem(i, e) == RANGE_ERROR) 
					cout << "位置范围错." << endl;
				else
					cout << "被删除元素值:" << e << endl;
			    break;
			case '6':
			    cout << endl << "输入位置:";
			    cin >> i;
			    cout << endl << "输入元素值:";
			    cin >> e;
			    if (la.InsertElem(i, e) == RANGE_ERROR) 
					cout << "位置范围错." << endl;
				else
					cout << "成功:" << e << endl;
			    break;
			case '7':
			    cout << endl << "输入元素值:";
			    cin >> e;
			    i = la.LocateElem(e);
			    if (i == 0) 
					cout << "指定元素不存在." << endl;
				else
					cout << "指定元素的序号为：" << i << endl;
			    break;		
          }
	}

	system("PAUSE");			
	return 0;		
}
