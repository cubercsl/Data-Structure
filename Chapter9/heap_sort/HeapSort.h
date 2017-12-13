#ifndef __HEAP_SORT_H__
#define __HEAP_SORT_H__
#include "Assistance.h"				// 辅助软件包

template <class ElemType>
void FilterDown(ElemType elem[], int low, int high)
// 操作结果:将以low为根的子树调整成为一个最大堆
{
    int f = low, i = 2 * low + 1;
    ElemType e = elem[low];
    while (i <= high) {			// f为被调整结点,i为f的最大孩子
		if (i < high && elem[i] < elem[i + 1])	
			i++;				// f有右孩子，且右孩子的值更大, i指向右孩子
		if (e < elem[i])	{	// 孩子的值大于其双亲，则进行向下调整 
			elem[f] = elem[i];
            f = i;
            i = 2 * f + 1;
		}
		else 
            break;
	}
	elem[f] = e;
}

template <class ElemType>
void HeapSort(ElemType elem[], int n)
// 操作结果:对数组elem进行堆排序
{
	int i;
	for (i = (n-2)/2; i >= 0; --i) // 初始建堆，将elem[0 .. n - 1]调整成最大堆
		FilterDown(elem, i, n - 1);
    cout << "初始堆："; 
    Display(elem, n);			   // 显示初始堆 

	for (i = n - 1; i > 0; --i)	{  // 第i趟堆排序
		Swap(elem[0], elem[i]);		
			// 将堆顶元素和当前未经排序的子序列elem[0 .. i]中最后一个元素交换
		FilterDown(elem, 0, i - 1);	// 将elem[0 .. i - 1]重新调整为最大堆
        cout << "第" << n - i << "趟堆排序结果："; 
        Display(elem, n);			// 显示中间结果 
	}
}

#endif

