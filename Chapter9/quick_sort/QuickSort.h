#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include "Assistance.h"				// 辅助软件包
template <class ElemType>
void QuickSort(ElemType elem[], int low, int high, int n)
// 操作结果:对数组elem[low .. high]中的元素进行快速排序
{
    ElemType e = elem[low];				// 取枢轴元素 
    int i = low, j = high;
	while (i < j)	{
		while (i < j && elem[j] >= e)	// 使j右边的元素不小于枢轴元素
			j--;
		if (i < j)
            elem[i++] = elem[j];

		while (i < j && elem[i] <= e)	// 使i左边的元素不大于枢轴元素
			i++;
		if (i < j)
            elem[j--] = elem[i];
	}
	elem[i] = e;
    cout << "排序区间：" << low << "--" << high << ";中枢位置为：" << i << endl; 
    Display(elem, n);
    cout << endl;
    if (low < i-1)	QuickSort(elem, low, i - 1, n);		// 对子表elem[low, i - 1]递归排序
	if (i + 1 < high) QuickSort(elem, i + 1, high, n);	// 对子表elem[i + 1, high]递归排序
}

#endif

