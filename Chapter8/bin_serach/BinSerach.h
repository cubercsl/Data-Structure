#ifndef __BIN_SERACH_H__
#define __BIN_SERACH_H__
#include "Assistance.h"					// 辅助软件包

template <class ElemType>
int BinSerach(ElemType elem[], int n, ElemType key)
// 操作结果: 迭代算法，在有序表中查找其关键字的值等于key的元素,如查找成功,则返回此元素的序号,否则返回-1
{
	int low = 0, high = n -1;		// 设置查找区间的左右边界
	int mid;
	
	while (low <= high)	{
		mid = (low + high) / 2;	    // 计算区间中间位置

		cout << "跟元素" << elem[mid] << "比较" << endl;   // 为跟踪查找过程 
		
		if (key == elem[mid])	
			return mid;             // 查找成功
		else if (key <= elem[mid])	
			high = mid - 1;         // 继续在左半区间进行查找
		else	
			low = mid + 1;          // 继续在右半区间进行查找
	}

	return -1;	                    // 查找失败
}

template <class ElemType>
int BinSerach(ElemType elem[], int low, int high, ElemType key)
// 操作结果: 递归算法，在有序表中查找其关键字的值等于key的元素,如查找成功,则返回此元素的序号,否则返回-1
{
	int mid;
	
	if (low > high)
        mid = -1; // 查找失败
    else {
		mid = (low + high) / 2;	    // 计算区间中间位置

		cout << "跟元素" << elem[mid] << "比较" << endl;  // 为跟踪查找过程 

		if (key < elem[mid])	
			mid = BinSerach(elem, low, mid - 1, key); // 继续在左半区间进行查找
		else if (key > elem[mid])	
			mid = BinSerach(elem, mid + 1, high, key);// 继续在右半区间进行查找
	}

	return mid;	                   
}


#endif
