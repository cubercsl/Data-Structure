#include "LinkMergeSort.h"	    // 静态链表上的归并排序算法

int main(void)
{
	int a[] = {55, 63, 38, 21, 63, 92, 16, 46, 87, 72};
	int n = 10, p;
    Node<int> *table;              // 静态链表

    table = new Node<int>[n + 1];
    for (p = 1; p <= n; p++){
        table[p].data = a[p - 1];
        table[p].next = -1;
    }

	
	cout << "排序前:" << endl;
    for (p = 1; p <= n; p++)
        cout << "(" << table[p].data << "," << table[p].next << ")" << endl;
    cout << endl;  
      
	table[0].next = LinkListMergeSort(table, 1, n);		    // 静态链表上的归并排序
	
	cout << "排序后:";
    for (p = table[0].next; p != -1; p = table[p].next)
        cout << table[p].data << "   ";
    cout << endl;    

	system("PAUSE");				
	return 0;						
}
