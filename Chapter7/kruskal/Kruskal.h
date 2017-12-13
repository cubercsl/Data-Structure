#ifndef __KRUSKAL_H__
#define __KRUSKAL_H__
#include "AdjMatrixUndirNetwork.h"		// 邻接表无向网
#include "UFSets.h"		                // 并查类
#include "MineHeap.h"

// Kruskal边类
template <class ElemType, class WeightType>
class KruskalEdge
{
public:
	ElemType vertex1, vertex2;		// 边的顶点
	WeightType weight;				// 边的权值
	KruskalEdge(ElemType v1, ElemType v2, WeightType w);	// 构造函数
	KruskalEdge(){};	            // 构造函数
	KruskalEdge<ElemType, WeightType> &operator =(const KruskalEdge<ElemType, WeightType> &Ed); // 赋值语句重载
	bool operator <=(const KruskalEdge<ElemType, WeightType> &Ed);		// 重载<=关系运算 
	bool operator >(const KruskalEdge<ElemType, WeightType> &Ed);		// 重载>关系运算
};

template <class ElemType, class WeightType>
KruskalEdge<ElemType, WeightType>::KruskalEdge(ElemType v1, ElemType v2, WeightType w)
// 操作结果: 由顶点v1、v2和权w构造边——构造函数
{	// 构造函数
	vertex1 = v1;					// 顶点vertex1
	vertex2 = v2;					// 顶点vertex2
	weight = w;						// 权weight
}

template <class ElemType, class WeightType>
bool KruskalEdge<ElemType, WeightType>::operator <= (const KruskalEdge<ElemType, WeightType> &Ed)
// 操作结果：重载<=关系运算
{
	return (weight <= Ed.weight);
}

template <class ElemType, class WeightType>
bool KruskalEdge<ElemType, WeightType>::operator > (const KruskalEdge<ElemType, WeightType> &Ed)
// 操作结果：重载>关系运算
{
	return (weight > Ed.weight);
}


template<class ElemType,  class WeightType>
KruskalEdge<ElemType, WeightType> &KruskalEdge<ElemType, WeightType>::operator = (const KruskalEdge<ElemType, WeightType> &Ed)
// 操作结果：将栈copy赋值给当前栈--赋值语句重载
{
	if (&Ed != this)	{
	   vertex1 = Ed.vertex1;					// 顶点vertex1
	   vertex2 = Ed.vertex2;					// 顶点vertex2
	   weight = Ed.weight;						// 权weight
	}
	return *this;
}


template <class ElemType, class WeightType>
void MiniSpanTreeKruskal(const AdjMatrixUndirNetwork<ElemType, WeightType> &g)
// 初始条件：存在网g
// 操作结果：用Kruskal算法构造网g的最小代价生成树
{
	int count, VexNum = g.GetVexNum();
    KruskalEdge<ElemType, WeightType> KEdge;
 	MinHeap<KruskalEdge<ElemType, WeightType> > ha(g.GetEdgeNum());
    ElemType  *kVex, v1, v2;
	kVex = new ElemType[VexNum];	// 定义顶点数组,存储顶点信息 
	for (int i = 0; i < VexNum; i++)
	    g.GetElem(i, kVex[i]);
	UFSets<ElemType> f(kVex,VexNum);// 根据顶点数组构造并查集 
	for (int v = 0; v < g.GetVexNum(); v++)
		for (int u = g.FirstAdjVex(v); u >= 0; u = g.NextAdjVex(v, u))
			if (v < u)			{	// 将v < u的边插入到最小堆 
                g.GetElem(v, v1); 
                g.GetElem(u, v2);
                KEdge.vertex1 = v1;
                KEdge.vertex2 = v2;
                KEdge.weight = g.GetWeight(v,u);
				ha.Insert(KEdge);
			}
	count = 0;					    // 表示已经挑选的边数

	while (count < VexNum - 1)	{	
        ha.DeleteTop(KEdge);        // 从堆顶取一条边
		v1 = KEdge.vertex1;
        v2 = KEdge.vertex2;
		if (f.Differ(v1, v2))	{	// 边所依附的两顶点不在同一棵树上
			cout << "边:( " << v1 << ", " << v2 << " ) 权:" << KEdge.weight << endl ; // 输出边及权值
			f.Union(v1, v2);		// 将两个顶点所在的树合并成一棵树
			count++;
		}
	}
}

#endif

