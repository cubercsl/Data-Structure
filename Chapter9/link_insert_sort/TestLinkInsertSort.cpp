#include "LinkInsertSort.h"	    	// 静态链表上的插入排序算法

int main(void)
{
	int a[] = {55, 63, 38, 21, 63, 92, 16, 46, 87, 72};
	int n = 10, p;
    Node<int> *table;              	// 静态链表

    table = new Node<int>[n + 1];
    for (p = 1; p <= n; p++){		// 根据数组a中的元素构造静态链表 
        table[p].data = a[p - 1];
        table[p - 1].next = p;
    }
    table[n].next = -1;

	
	cout << "排序前:";
    for (p = table[0].next; p != -1; p = table[p].next)
        cout << table[p].data << "   ";
    cout << endl;  
      
	LinkInsertSort(table);		   // 静态链表上的插入排序
	
	cout << "排序后:";
    for (p = table[0].next; p != -1; p = table[p].next)
        cout << table[p].data << "   ";
    cout << endl;    

	system("PAUSE");				
	return 0;						
}
