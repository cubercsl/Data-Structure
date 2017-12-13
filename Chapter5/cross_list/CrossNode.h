#ifndef __CRO_NODE_H__
#define __CRO_NODE_H__

#include "triple.h"						// 三元组类

// 十字链表非零元素结点类
template<class ElemType>
struct CrossNode
{
// 数据成员:
	Triple<ElemType> triElem;			// 三元组
	CrossNode<ElemType> *right, *down;	// 非零元素所在行表与列表的后继指针域

// 构造函数:
	CrossNode();						// 无参数的构造函数
	CrossNode(const Triple<ElemType> &e,// 有参数的构造函数
		CrossNode<ElemType> *rLink = NULL, CrossNode<ElemType> *dLink = NULL);	
};

// 十字链表非零元素结点类的实现部分
template<class ElemType>
CrossNode<ElemType>::CrossNode()
// 操作结果：构造指针域为空的结点
{
	right = NULL;	
	down = NULL;
}

template<class ElemType>
CrossNode<ElemType>::CrossNode(const Triple<ElemType> &e,
		CrossNode<ElemType> *rLink, CrossNode<ElemType> *dLink)
// 操作结果：已知三元组和指针域建立结点
{
	triElem.row = e.row;	
	triElem.col = e.col;	
	triElem.value = e.value;
	right = rLink;		
	down = dLink;			
}

#endif
