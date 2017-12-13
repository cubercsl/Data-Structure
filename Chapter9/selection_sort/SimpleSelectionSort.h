#ifndef __SIMPLE_SELECT_SORT_H__
#define __SIMPLE_SELECT_SORT_H__

#include "Assistance.h"				// 辅助软件包

template <class ElemType>
void SimpleSelectionSort(ElemType elem[], int n)
// 操作结果:对数组elem中n个元素进行简单选择排序
{
    int k; 
	for (int i = 0; i < n - 1; i++)	{	// 第i趟简单选择排序
		k = i;			    			// k记录elem[i .. n - 1]中最小元素小标
		for (int j = i + 1; j < n; j++)
			if (elem[j] < elem[k])
				k = j;
	    if (k != i)
		    Swap(elem[i], elem[k]);		// 交换elem[i], elem[k]
	    cout << "显示第" << i + 1 << "趟简单选择排序的结果："; 
        Display(elem, n);				// 显示中间结果 
	}
}

#endif

