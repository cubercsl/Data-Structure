#ifndef __BFS_H__
#define __BFS_H__
#include "AdjMatrixUndirGraph.h"		// 无向图邻接矩阵
#include "LinkQueue.h"					// 链队列

template <class ElemType>
void BFSTraverse(const AdjMatrixUndirGraph<ElemType> &g, void (*Visit)(const ElemType &))
// 初始条件：存在图g
// 操作结果：对图g进行广度优先遍历
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
		g.SetTag(v, UNVISITED); // 对每个顶点作未访问标志

	for (v = 0; v < g.GetVexNum(); v++)
		if (g.GetTag(v) == UNVISITED) 
			BFS(g, v , Visit); 	// 从尚未访问的顶点v开始进行广度优先搜索
}

template <class ElemType>
void BFS(const AdjMatrixUndirGraph<ElemType> &g, int v, void (*Visit)(const ElemType &))
// 初始条件：存在图g
// 操作结果：从顶点v出发进行广度优先搜索
{	
	LinkQueue<int> q;
    int u, w;
    ElemType e;
    g.SetTag(v, VISITED);						// 作访问标志
	g.GetElem(v, e);							// 取顶点v的数据元素值 
	Visit(e);									// 访问顶点v
	q.EnQueue(v);	                            // 顶点v入队 
	while (!q.IsEmpty())	{	
	   q.DelQueue(u);
	   for (w = g.FirstAdjVex(u); w != -1; w = g.NextAdjVex(u, w))
			if (g.GetTag(w) == UNVISITED){ // 对u尚未访问过的邻接顶点w进行访问
                g.SetTag(w, VISITED);	
	            g.GetElem(w, e);	
	            Visit(e);	
				q.EnQueue(w);
            }	
	}
}

#endif
