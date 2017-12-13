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
int LinkListMerge(Node<ElemType> elem[], int p, int q ) {
    // 归并以p和q为链表头指针的有序链表 
    int k = 0;   // k为结果链表的头结点指针
    while (p !=-1 && q !=-1)
        if (elem[p].data <= elem[q].data) { 
            elem[k].next = p;
            k = p;
            p = elem[p].next; 
        }
        else {
            elem[k].next = q;
            k = q; 
            q = elem[q].next; 
        }
    if (p == -1)   
       elem[k].next = q; 
    else   
       elem[k].next = p;
    return elem[0].next;
}

template <class ElemType>
int LinkListMergeSort(Node<ElemType> elem[], int low, int high) {
    //对low~high区间，以中点mid为界, 分别对左半部和右半部进行表归并排序后，再进行两路归并
    if (low >= high)
        return low;
    int mid = (low + high) / 2, p, q;
    p = LinkListMergeSort(elem, low, mid);
    q = LinkListMergeSort(elem, mid+1, high);
    return LinkListMerge(elem, p, q);
}


#endif

