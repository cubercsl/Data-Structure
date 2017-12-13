#ifndef __TOPSORT_H__
#define __TOPSORT_H__

#include "AdjListDirGraph.h"			// 邻接矩阵有向图

template <class ElemType>
void StatIndegree(const AdjListDirGraph<ElemType> &g, int *indegree)
// 操作结果：统计图g各顶点的入度
{
	for (int v = 0; v < g.GetVexNum(); v++)	// 初始化入度为0
		indegree[v] = 0;

	for (int v = 0; v < g.GetVexNum(); v++)// 遍历图的顶点
		for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u))
			indegree[u]++;
}

template <class ElemType>
Status TopSort(const AdjListDirGraph<ElemType> &g)
// 初始条件：存在有向图g
// 操作结果：如g无回路,则输出g的顶点的一个拓扑序列,并返回SUCCESS,否则返回FAIL
{
	int *indegree = new int[g.GetVexNum()];	// 顶点入度数组		
	int v, u, count = 0, top = -1;
	ElemType e;
	StatIndegree(g, indegree);				// 统计顶点的入度
	

	for (v = 0; v < g.GetVexNum(); v++)
		if (indegree[v] == 0)  {            // 入度为0的顶点入栈 
			indegree[v] = top;
            top = v;
        }

	while (top != -1)	{	// 栈非空
		v = top;
        top = indegree[v];
		g.GetElem(v, e);
		cout << e << "  ";
		count++;			// 对输出顶点进行记数
		for (u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u))
			// 对v的每个邻接点u入度减1
			if (--indegree[u] == 0)	{// u入度为0,将u入栈
			   indegree[u] = top;
               top = u;
            }
	}
	delete []indegree;						// 释放indegree所占用的存储空间

	if (count < g.GetVexNum()) return FAIL;	// 图g有回路
	else return SUCCESS;					// 拓扑排序成功
}

#endif

