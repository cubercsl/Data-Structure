#ifndef __INSERT_SORT_H__
#define __INSERT_SORT_H__
#include "Assistance.h"			// 辅助软件包

template <class ElemType>
void StraightInsertSort(ElemType elem[], int n)
// 操作结果:对数组elem中的n个元素进行直接插入排序
{
	int i, j;							
	for (i = 1; i < n; i++)	{			// 第i趟直接插入排序
		ElemType e = elem[i];			// 取要插入的元素elem[i]
		for (j = i - 1; j >= 0 && e < elem[j]; j--)	// 将比e大的元素后移
			elem[j + 1] = elem[j];		// 后移
		elem[j + 1] = e;				// j+1为插入位置
	    cout << "第" << i << "趟直接插入排序的结果："; 
        Display(elem, n);				// 显示中间结果 
	}
}

#endif

