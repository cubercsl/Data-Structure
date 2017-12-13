#ifndef __ADJ_LIST_NETWORK_VEX_H__
#define __ADJ_LIST_NETWORK_VEX_H__

// 邻接表网顶点结点类
template <class ElemType>
struct AdjListGraphVex
{
// 数据成员:
	ElemType data;						// 数据元素值
	AdjListGraphArc *firstarc;
		// 指向邻接链表边结点的指针

// 构造函数:
	AdjListGraphVex();				// 无参数的构造函数
	AdjListGraphVex(ElemType val, 
		AdjListGraphArc *adj = NULL);
		// 有参数的构造函数
};

// 邻接表网顶点结点类的实现部分
template <class ElemType>
AdjListGraphVex<ElemType>::AdjListGraphVex()
// 操作结果：构造一个空顶点结点——无参构造函数
{
	firstarc = NULL;	
}

template <class ElemType>
AdjListGraphVex<ElemType>::AdjListGraphVex(ElemType  val, 
	AdjListGraphArc *adj)
// 操作结果：构造数据为val,边为eg的顶点
{
	data = val;
	firstarc = adj;
}

#endif
