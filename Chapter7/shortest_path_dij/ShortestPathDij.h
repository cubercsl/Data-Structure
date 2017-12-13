#ifndef __SHORTEST_PATH_DIJ_H__
#define __SHORTEST_PATH_DIJ_H__

#include "AdjListDirNetwork.h"			// 有向网邻接表 
#include "LinkStack.h"		            // 链式栈

template <class ElemType, class WeightType>
void DisplayPathAndDist(const AdjListDirNetwork<ElemType, WeightType> &g, int v0, int *path, WeightType *dist)
{
    ElemType e1, e2;
	WeightType infinity = g.GetInfinity();
    g.GetElem(v0, e1);
	for (int v1 = 0; v1 < g.GetVexNum(); v1++)	{
       cout << endl;
       g.GetElem(v1, e2);
       if (v1 != v0) 
	      if (dist[v1] < infinity )		{	// 存在从v0到v1最短路径
			 cout << "从顶点 " << e1 << " 到 " << e2 << ":";
			 cout << " 路径长度 = " << dist[v1];
			 cout << " 路径:";
			 LinkStack<int> s;	// 存储路上的顶点
			 int v = v1;
			 while (v != v0)	{
				s.Push(v);	// v为路径上的顶点
				v = path[v];// 取上路径上的前一个顶点
			 }
			 s.Push(v0);		// v是路径上起始点
			 while (!s.IsEmpty())			{	// 输出路上的顶点
				s.Pop(v);
                g.GetElem(v, e2);
				cout << e2 << " ";
			 }
		 }
	 	 else 	// 从v0到v1无路径
			cout << "从顶点 " << e1 << " 到 "  << e2 << "无路径";
   }
   cout << endl;
}


template <class ElemType, class WeightType>
void ShortestPathDij(const AdjListDirNetwork<ElemType, WeightType> &g, int v0, 
	int *path, WeightType *dist)
// 操作结果: 用Dijkstra算法求有向网g从顶点v0到其余顶点v的最短路径path和路径长度dist[v],
//	path[v]存储最短路径上终点的前一顶点的顶点号
{
	WeightType minVal, infinity = g.GetInfinity();
    int v, u;
	for (v = 0; v < g.GetVexNum(); v++){	// 初始化path和dist及顶点标志
 	    dist[v] = (v0 != v) ? g.GetWeight(v0, v) : 0;
   	    if (dist[v] == infinity)
            path[v] = -1;
        else 
            path[v] = v0;
		g.SetTag(v, UNVISITED);	// 置顶点标志
	}
	g.SetTag(v0, VISITED);		// U={v0}

	for (int i = 1; i < g.GetVexNum(); i++){	// 求g.GetVexNum() - 1个顶点的最短路径  
		minVal = infinity;
        u = v0;
		for (v = 0; v < g.GetVexNum(); v++)   // 查找最小的最短路径 
			if (g.GetTag(v) == UNVISITED && dist[v] < minVal)		{
            	// g.GetTag(v) == UNVISITED表示v∈V - U
				u = v;
				minVal = dist[v];
			}
		g.SetTag(u, VISITED);	// 将u并入U

		for (v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v))
			if (g.GetTag(v) == UNVISITED && minVal + g.GetWeight(u, v) < dist[v])	{
               	// 如v∈V - U且minVal + g.GetWeight(u, v) < dist[v],则修改dist[v]及path[v]
				dist[v] = minVal + g.GetWeight(u, v);
				path[v] = u;
			}
	}
}

#endif

