#include "SimpleSelectionSort.h"	// 简单选择排序算法

int main(void)
{
	int a[] = {55, 63, 38, 21, 63, 92, 16, 46, 87, 72};
	int n = 10;
	cout << "排序前:";
	Display(a, n);					 
	SimpleSelectionSort(a, n);		// 简单选择排序
	cout << "排序后:";
	Display(a, n);					

	system("PAUSE");				
	return 0;					
}
