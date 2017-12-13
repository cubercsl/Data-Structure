#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

#include "Assistance.h"				// 辅助软件包

template <class ElemType>
void Merge(ElemType elem[], int low, int mid, int high)
// 操作结果:将有序子序列elem[low .. mid]和elem[mid + 1 .. midhigh]归并为新的
//	有序序列elem[low .. high]
{
	ElemType *tmpElem = new ElemType[high+1]; // 定义临时数组
	int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high)
		// i为归并时elem[low .. mid]当前元素的下标,j为归并时elem[mid + 1 .. high]当前元素
		// 的下标,k为tmpElem中当前元素的下标
		if (elem[i] <= elem[j])		
			tmpElem[k++] = elem[i++];
		else
			tmpElem[k++] = elem[j++];

	while (i <= mid)				// 归并elem[low .. mid]中剩余元素
		tmpElem[k++] = elem[i++];

    while (j <= high)				// 归并elem[mid + 1 .. high]中剩余元素
		tmpElem[k++] = elem[j++];

	for (i = low; i <= high; i++)	// 将tmpElem[low .. high]复制到elem[low .. high]
		elem[i] = tmpElem[i];

	delete []tmpElem;				// 释放tmpElem所点用空间
}

template <class ElemType>
void RecursionMergeSort(ElemType elem[], int low, int high, int n)
// 操作结果:对elem[low .. high]进行归并排序
{
	if (low < high)	{	
		int mid = (low + high) / 2;			
			// 将elem[low .. high]平分为elem[low .. mid]和elem[mid + 1 .. high]
		RecursionMergeSort(elem, low, mid, n);	 
		  	// 对elem[low .. mid]进行归并排序
		RecursionMergeSort(elem, mid + 1, high, n);
			// 对elem[mid + 1 .. high]进行归并排序
		Merge(elem, low, mid, high);		 
		  	// 对elem[low .. mid]和elem[mid + 1 .. high]进行归并
        cout << "归并区间：" << low << "--" << high << endl; 
        Display(elem, n);
        cout << endl;
	}
}
#endif

