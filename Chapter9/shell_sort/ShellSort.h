#ifndef __SHELL_SORT_H__
#define __SHELL_SORT_H__

#include "Assistance.h"				// 辅助软件包
template <class ElemType>
void ShellSort(ElemType elem[], int n)
// 操作结果: 取步长序列n/2,n/4,n/8,...,1.对数组elem进行Shell排序
{
    int i, j, d = n / 2;            // 初始步长取n/2 
    ElemType e;
	while (d > 0) {
       for (i = d ; i < n; i++)	{	// 步长为d时的插入排序
		  e = elem[i];		        // 取下标为i的元素 
		  j = i - d; 
          while (j >= 0 && e < elem[j]) { 
			 elem[j + d] = elem[j];	// 将子序列中比e大的计录都后移
             j -= d;
          }	
		  elem[j + d] = e;			// 将下标为i的元素插入到子序列的适当位置
       }
	   cout << "步长为" << d << "时希尔排序的结果："; 
       Display(elem, n);			// 显示中间结果 
       d = d / 2;                   // 缩短步长 
	}
}

#endif

