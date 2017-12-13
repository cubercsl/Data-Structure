#ifndef __PRIM_H__
#define __PRIM_H__
#include "AdjMatrixUndirNetwork.h"	// 邻接矩阵无向网

template <class ElemType, class WeightType>
struct CloseArcType {
   WeightType lowweight;
   int nearvertex;
};

template <class ElemType, class WeightType>
void MiniSpanTreePrim(const AdjMatrixUndirNetwork<ElemType, WeightType> &g, int u0)
// 初始条件：存在网g,u0为g的一个顶点
// 操作结果：用Prim算法从u0出发构造网g的最小生成树
{
   WeightType min;
   ElemType v1, v2;
   int vexnum = g.GetVexNum();
   CloseArcType<ElemType, WeightType> * closearc;

   if (u0 < 0 || u0 >= vexnum)
      throw Error("顶点u0不存在!"); // 抛出异常

	int u, v, k;						// 表示顶点的临时变量 
	closearc = new CloseArcType<ElemType, WeightType>[vexnum];	// 分配存储空间
	for (v = 0; v < vexnum; v++)	{	// 初始化辅助数组adjVex，并对顶点作标志，此时U = {v0}
		closearc[v].nearvertex = u0;
		closearc[v].lowweight = g.GetWeight(u0, v);
	}
	closearc[u0].nearvertex = -1;
	closearc[u0].lowweight = 0;
	
	for (k = 1; k < vexnum; k++) {	// 选择生成树的其余g.GetVexNum() - 1个顶点
		min = g.GetInfinity();
        v = u0;// 选择使得边<w, adjVex[w]>为连接V-U到U的具有最小权值的边
		for (u = 0; u < vexnum; u++)
           if (closearc[u].lowweight != 0 && closearc[u].lowweight < min) {
			  v = u;
              min = closearc[u].lowweight;
	       }
 	    if (v != u0) {
           g.GetElem(closearc[v].nearvertex, v1);
           g.GetElem(v, v2);     
		   cout << "边:( " << v1 << ", " <<  v2 << " ) 权:" << min << endl ; // 输出边及权值
		   closearc[v].lowweight = 0;		// 将w并入U
		   for (u = g.FirstAdjVex(v); u != -1 ; u = g.NextAdjVex(v, u)) 	// 新顶点并入U后重新选择最小边
			  if (closearc[u].lowweight != 0 && (g.GetWeight(v, u) < closearc[u].lowweight))	{	// <v, w>为新的最小边
				closearc[u].lowweight = g.GetWeight(v, u);
				closearc[u].nearvertex = v;
			  }
		}
		
	}
	delete []closearc;			// 释放存储空间  
}

#endif

