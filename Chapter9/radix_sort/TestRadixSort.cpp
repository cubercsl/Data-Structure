#include "RadixSort.h"				// 基数排序算法

int main(void)
{
	int a[] = {432, 820, 53, 786, 481, 529, 314, 608, 764, 104};
	int n = 10, r = 10, d = 3, p;
    Node<int> *table;              // 静态链表

    table = new Node<int>[n + 1];
    for (p = 1; p <= n; p++){
        table[p].data = a[p - 1];
        table[p - 1].next = p;
    }
    table[n].next = -1;

	cout << "排序前:";
    for (p = table[0].next; p != -1; p = table[p].next)
        cout << table[p].data << "   ";
    cout << endl; 
     
	RadixSort(table, d, r);			// 基数排序

	cout << "排序后:";
    for (p = table[0].next; p != -1; p = table[p].next)
        cout << table[p].data << "   ";
    cout << endl;    

	system("PAUSE");				
	return 0;						
}
