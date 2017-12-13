#ifndef __RADIX_SORT_H__
#define __RADIX_SORT_H__

#include "Assistance.h"				// 辅助软件包
template <class ElemType>
struct Node
{
       ElemType data;
       int next;
};


template <class ElemType>
void RadixSort (Node<ElemType> elem[], const int d, const int radix) {
// 初始条件: radix为基数,d为关键字位数
// 操作结果: 对elem表进行基数排序
    int e[radix], f[radix], p, i, j, k, power;
    for (i = 0; i < d; i++) {      //做d 趟分配、收集
       for (j = 0; j < radix; j++)
           f[j] = 0;               //初始化各分配队列
       power = (int)pow((double)radix, i);
       p = elem[0].next;          //初始化链表搜索指针
       while (p != -1) {           //逐个数据元素分配
           k = (elem[p].data / power) % radix;  //取当前数据元素关键字的第 i 位 
           if (f[k] == 0)
               f[k] = p;           //原链表为空时，数据元素入队首
           else                    //原链表非空时，数据元素入队尾
               elem[e[k]].next = p;
           e[k] = p;               //修改链尾指针
           p = elem[p].next;      //取链表中下一个结点
        }

        j = 0  ;                   //开始数据收集
        while (f[j] == 0)          //跳过空队列
            j++; 
        elem[0].next = f[j];    
        p = e[j];   
        for (k = j + 1; k < radix; k++)
            if (f[k] != 0) {       //回收每个非空队列链入
                elem[p].next = f[k]; 
                p = e[k];
            }
        elem[p].next = -1;

        cout << "按第" << i << "位排序的结果:";
        for (p = elem[0].next; p != -1; p = elem[p].next)
            cout << elem[p].data << "   ";
        cout << endl; 
    }
}

#endif

