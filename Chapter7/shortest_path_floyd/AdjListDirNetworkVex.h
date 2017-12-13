#ifndef __ADJ_LIST_NETWORK_VEX_H__
#define __ADJ_LIST_NETWORK_VEX_H__

// 邻接表网顶点结点类
template <class ElemType, class WeightType>
struct AdjListNetWorkVex
{
// 数据成员:
	ElemType data;						// 数据元素值
	AdjListNetworkArc<WeightType> *firstarc;
		// 指向邻接链表边结点的指针

// 构造函数:
	AdjListNetWorkVex();				// 无参数的构造函数
	AdjListNetWorkVex(ElemType val, 
		AdjListNetworkArc<WeightType> *adj = NULL);
		// 有参数的构造函数
};

// 邻接表网顶点结点类的实现部分
template <class ElemType, class WeightType>
AdjListNetWorkVex<ElemType, WeightType>::AdjListNetWorkVex()
// 操作结果：构造一个空顶点结点——无参构造函数
{
	firstarc = NULL;	
}

template <class ElemType, class WeightType>
AdjListNetWorkVex<ElemType, WeightType>::AdjListNetWorkVex(ElemType  val, 
	AdjListNetworkArc<WeightType> *adj)
// 操作结果：构造数据为val,边为eg的顶点
{
	data = val;
	firstarc = adj;
}

#endif
