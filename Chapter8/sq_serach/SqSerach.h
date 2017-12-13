#ifndef __SQ_SERACH_H__
#define __SQ_SERACH_H__
#include "Assistance.h"					// 辅助软件包

template <class ElemType>
int SqSerach(ElemType elem[], int n, ElemType key)
// 操作结果: 在顺序表中查找关键字的值等于key的元素,如查找成功,则返回此元素在顺序表的下标,否则返回-1
{
	int i;		  // 循环控制变量 
	for (i = 0; i < n && elem[i] != key; i++)
	   		cout << "跟元素" << elem[i] << "比较" << endl;  // 为跟踪查找过程 
	if (i < n)	  
		return i; // 查找成功，返回下标 
	else	
		return -1;// 查找失败，返回-1
}

#endif
