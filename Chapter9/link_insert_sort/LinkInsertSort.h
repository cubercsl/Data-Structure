#ifndef __INSERT_SORT_H__
#define __INSERT_SORT_H__
#include "Assistance.h"				// 辅助软件包

template <class ElemType>
struct Node
{
       ElemType data;
       int next;
};


template <class ElemType>
void LinkInsertSort(Node<ElemType> elem[])
// 操作结果:对用静态链表elem中的元素进行插入排序
{
	int p, q, pre, r;			
    
    p = elem[0].next;
    elem[0].next = -1;
    while (p != -1) {
         q = elem[0].next;
         pre = 0;
         while (q != -1 && elem[q].data <= elem[p].data) {
               pre = q;
               q = elem[q].next;
         }
         r = elem[p].next;
         elem[p].next = q;
         elem[pre].next = p;
         p = r;
	}
}

#endif

