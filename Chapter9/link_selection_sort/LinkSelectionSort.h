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
void LinkSelectionSort(Node<ElemType> elem[])
// 操作结果:对用静态链表elem中的元素进行选择排序
{
    int p, q, pp, pq, h ;
    h = p = elem[0].next;
    elem[0].next = -1;   	// 设置初始有序链表表头 
    while ( p != -1 ) {
        q = pq = pp = p;  	//设置初始搜索指针
        p = elem[p].next;
        while (p != -1) { 	//选出当前具最大关键字的数据元素，并由q指向
            if ( elem[p].data >= elem[q].data) {
                q = p ; 
                pq = pp ; 
            }
            pp = p ;
            p = elem[p].next;
       } 
       if ( h == q ) {   	//最大关键字的数据元素在待排序数据元素链表的表首
           h = elem[q].next;
           elem[q].next = elem[0].next;
           elem[0].next = q;
       } 
       else  {
           elem[pq].next = elem[q].next;
           elem[q].next = elem[0].next;
           elem[0].next = q;
          }
       p = h ;  //准备下一次选择
    }
}

#endif

