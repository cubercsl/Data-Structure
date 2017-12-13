#ifndef __TOPSORT_H__
#define __TOPSORT_H__

#include "LinkQueue.h"						// 队列
#include "LinkStack.h"						// 栈
#include "AdjListDirNetwork.h"			// 邻接矩阵有向网

template <class ElemType, class WeightType>
void StatIndegree(const AdjListDirNetwork<ElemType, WeightType> &g, int *indegree)
// 操作结果：统计网g各顶点的入度
{
	for (int v = 0; v < g.GetVexNum(); v++)
		indegree[v] = 0;	             // 初始化各顶点的入度为0

	for (int v = 0; v < g.GetVexNum(); v++)
		for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u))
			indegree[u]++;              // u为弧<v,u>的弧头顶点
}

template <class ElemType, class WeightType>
Status CriticalPath(const AdjListDirNetwork<ElemType, WeightType> &g)
// 初始条件：存在有向网g
// 操作结果：如g无回路,则输出g的关键活动,并返回SUCCESS,否则返回FAIL
{
	int *indegree = new int[g.GetVexNum()];	// 顶点入度数组
	WeightType *ve = new int[g.GetVexNum()];	// 事件最早发生时刻数组
	WeightType *vl = new int[g.GetVexNum()];  // 事件最迟发生时刻数组
	LinkQueue<int> q;					// 用于存储入度为0的顶点
	LinkStack<int> s;					// 用于实现逆扑序序列的栈
	int ee, el, u, v, count = 0;
	ElemType e1, e2;

	for (v = 0; v < g.GetVexNum(); v++) 	// 初始化事件最早发生时刻
		ve[v] = 0;
	StatIndegree(g, indegree);				// 统计顶点的入度
	for (v = 0; v < g.GetVexNum(); v++)	// 遍历顶点
		if (indegree[v] == 0)	// 建立入度为0的顶点队列
			q.EnQueue(v);

	while (!q.IsEmpty())	{	// 队列非空
		q.DelQueue(u);			// 取出一个入度为0的顶点
		s.Push(u);				// 顶点u入栈,以便得逆拓扑排序序列
		count++;				// 对顶点进行记数
		for (v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v))		{
            // v为弧<u,v>的弧头顶点,对u的每个邻接点入度减1
			if (--indegree[v] == 0)	// v入度为0,将v入队
				q.EnQueue(v);
			if (ve[u] + g.GetWeight(u, v) > ve[v])	// 修改ve[v]
				ve[v] = ve[u] + g.GetWeight(u, v);
		}
	}
	delete []indegree;			// 释放indegree所占用的存储空间

	if (count < g.GetVexNum()) 	{
		delete []ve;			// 释放ve所占用的存储空间
		return FAIL;			// 网g有回路
	}

	s.Top(u);								// 取出栈顶,栈顶为汇点
	for (v = 0; v < g.GetVexNum(); v++) 	// 初始化事件最迟发生时刻
		vl[v] = ve[u];

	while (!s.IsEmpty())      {	// s非空
		s.Pop(u);
		for (v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v))	// v为u的一个邻接点
			if (vl[v] - g.GetWeight(u, v) < vl[u])	// 修改vl[u]
				vl[u] = vl[v] - g.GetWeight(u, v);
	}

	for (u = 0; u < g.GetVexNum(); u++)	{	// 求ee, el和关键路径
		for (v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v))		{	// v为u的一个邻接点
			ee = ve[u]; el = vl[v] - g.GetWeight(u, v);
			if (ee == el)	{	// <u, v>为关键活动
				g.GetElem(u, e1);
				g.GetElem(v, e2);
				cout << "<" << e1 << "," << e2 << "> ";
			}
		}
	}
	
	delete []ve;				// 释放ve所占用的存储空间
	delete []vl;				// 释放vl所占用的存储空间
	return SUCCESS;				// 操作成功
}

#endif

