#include "SeqList.h"	// 顺序表类

int main(void)
{
	char a[] = {'A','C','E','G','I'}, b[] = {'A','B','C','D','H','I','J'},e; 
	SeqList<char> la(a,5,50), lb(b,7,50), lc(50);
	
	for (int i = 1; i <= la.GetLength(); i++)	{
		la.GetElem(i, e);		// 取出la中第i个元素e
		if (lb.LocateElem(e))   // 如果e在lb中存储,将其插入到lc中
			lc.InsertElem(e); 
	}
	
	cout << "集合A:";
	la.Traverse(Write);		    // 显示集合A
	cout << endl;

	cout << "集合B:";
	lb.Traverse(Write);		    // 显示集合B
	cout << endl;

	cout << "集合C:";
	lc.Traverse(Write);		    // 显示集合C
	cout << endl;

	system("PAUSE");            // 调用库函数system()暂停系统运行 
	return 0;                   // 返回操作系统
}
