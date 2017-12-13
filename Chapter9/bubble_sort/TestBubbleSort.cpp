#include "BubbleSort.h"			// 冒泡排序算法

int main(void)
{
	int a[] = {55, 63, 38, 21, 63, 92, 16, 46, 87, 72};
	int n = 10;
	cout << "排序前:";
	Display(a, n);				// 显示数组a的内容 
	BubbleSort(a, n);			// 冒泡排序
	cout << "排序后:";
	Display(a, n);				// 显示a数组a的内容 

	system("PAUSE");			// 调用库函数system()
	return 0;					// 返回值0, 返回操作系统
}
