#ifndef __ADJ_MATRIX_UNDIR_GRAPH_H__
#define __ADJ_MATRIX_UNDIR_GRAPH_H__
#include "Assistance.h"                 // 辅助软件包

// 无向图的邻接矩阵类
template <class ElemType, class WeightType>
class AdjMatrixUndirNetwork 
{
protected:
// 邻接矩阵的数据成员:
	int vexNum, vexMaxNum, edgeNum;			// 顶点数目、允许的顶点最大数目和边数
	int **arcs;							// 存放边信息邻接矩阵
	ElemType *vertexes;						// 存放顶点信息的数组 
	Status *tag;							// 标志数组
	WeightType infinity;					// 无穷大

public:
// 邻接矩阵类型的方法声明:
	AdjMatrixUndirNetwork(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE,
							WeightType infinit = (WeightType)DEFAULT_INFINITY);	
		// 以数组es[]为顶点,顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,边数为0的无向图
	AdjMatrixUndirNetwork(int vertexMaxNum = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);	
		// 构造允许的顶点最大数目为vertexMaxNum,边数为0的无向图
	~AdjMatrixUndirNetwork();					// 析构函数
	void Clear();			              // 清空图			 
	bool IsEmpty();                 // 判断无向图是否为空 
	int GetOrder(ElemType &e) const;// 求顶点的序号	
	Status GetElem(int v, ElemType &e) const;// 求顶点的元素值	
	Status SetElem(int v, const ElemType &e);// 设置顶点的元素值
	WeightType GetInfinity() const;				// 返回无穷大			 
	int GetVexNum() const;					// 返回顶点个数			 
	int GetEdgeNum() const;					// 返回边数			 
	int FirstAdjVex(int v) const;		// 返回顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		 // 返回顶点v1的相对于v2的下一个邻接点			 
	void InsertVex(const ElemType &e);			 // 插入元素值为e的顶点		 
	void DeleteVex(const ElemType &e);			 // 删除元素值为e的顶点			 
	void InsertArc(int v1, int v2, WeightType w);	// 插入顶点为v1和v2,权为w的边			 
	void DeleteArc(int v1, int v2);			// 删除顶点为v1和v2的边			 
	WeightType GetWeight(int v1, int v2) const;	// 返回顶点为v1和v2的边的权值
	Status GetTag(int v) const;			         // 返回顶点v的标志		 
	void SetTag(int v, Status val) const;	   // 设置顶点v的标志为val		 
	AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork<ElemType, WeightType> &g);	// 复制构造函数
	AdjMatrixUndirNetwork<ElemType, WeightType> &operator =(const AdjMatrixUndirNetwork<ElemType, WeightType> &g); 
		// 赋值语句重载
  void Display();	                         // 显示邻接矩阵无向图
};

// 无向图的邻接矩阵类的实现部分
template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(ElemType es[], int vertexNum, int vertexMaxNum, WeightType infinit)
// 操作结果：构造数据元素为es[],顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,边数为0的无向图
{
	if (vertexMaxNum < 0)
    	throw Error("允许的顶点最大数目不能为负!");        // 抛出异常

	if (vertexMaxNum < vertexNum)
    	throw Error("顶点数目不能大于允许的顶点最大数目!");// 抛出异常

	vexNum = vertexNum;			
	vexMaxNum = vertexMaxNum; 
	edgeNum = 0;	
	infinity = infinit;
	
	vertexes = new ElemType[vexMaxNum];     	// 生成生成顶点信息数组
	tag = new Status[vexMaxNum];			 	// 生成标志数组
	arcs = (int **)new int *[vexMaxNum];     	// 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++) 
		arcs[v] = new int[vexMaxNum];	

	for (int v = 0; v < vexNum; v++) {
		vertexes[v] = es[v];
		tag[v] = UNVISITED;
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = infinity;
		arcs[v][v] = 0;
	}
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(int vertexMaxNum, WeightType infinit)
// 操作结果：构造允许顶点的最大数目为vertexMaxNum的空无向图
{
	if (vertexMaxNum < 0)
    	throw Error("允许的顶点最大数目不能为负!");// 抛出异常

	vexNum = 0;			
	vexMaxNum = vertexMaxNum;
	edgeNum = 0;	
	infinity = infinit;

	vertexes = new ElemType[vexMaxNum];     // 生成生成顶点信息数组
	tag = new Status[vexMaxNum];			      // 生成标志数组
	arcs = (int **)new int *[vexMaxNum];    // 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++) 
		arcs[v] = new int[vexMaxNum];	
 }

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::Clear()
// 操作结果：把无向图的顶点数和边数设置为0.			 
{
    vexNum = 0;
	edgeNum = 0;	
}

template <class ElemType, class WeightType>
bool AdjMatrixUndirNetwork<ElemType, WeightType>::IsEmpty()
// 操作结果：如果无向图为空返回true,否则返回false.
{
	return vexNum == 0;
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::~AdjMatrixUndirNetwork()
// 操作结果：释放对象所占用的空间
{
	delete []vertexes;					// 释放顶点数据
	delete []tag;						    // 释放标志

	for (int v = 0; v < vexMaxNum; v++)	// 释放邻接矩阵的行
		delete []arcs[v];
	delete []arcs;					    // 释放邻接矩阵
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetOrder(ElemType &e) const
// 操作结果：求顶点e的序号.顶点的序号从0开始，图中不存在顶点e时，返回-1. 
{
    for (int v = 0; v < vexNum; v++)
        if (vertexes[v] == e)
		   return v;	    // 顶点e存在,返回它的序号 
	return -1;	        // 顶点e不存在,返回-1
}	

template <class ElemType, class WeightType>
Status AdjMatrixUndirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &e) const
// 操作结果：求序号为v的顶点值, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数
// 通过e取得顶点值，并返回ENTRY_FOUND；否则函数返回NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;	// v范围错,返回元素不存在
	else	{
		e = vertexes[v];	  // 将顶点v的元素值赋给e
		return ENTRY_FOUND;	// 返回元素存在
	}
}	

template <class ElemType, class WeightType>
Status AdjMatrixUndirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &e)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;	// v范围错,返回位置错
	else	{
		vertexes[v] = e;		// 将顶点元素的值改为e 
		return SUCCESS;		  // 返回修改成功
	}
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirNetwork<ElemType, WeightType>::GetInfinity() const
// 操作结果：返回无穷大
{
	return infinity;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetEdgeNum() const
// 操作结果：返回边数
{
	return edgeNum;
}		 

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第1个邻接点的序号		 
{
	if (v < 0 || v >= vexNum)
       throw Error("v不合法!");// 抛出异常

	for (int u = 0; u < vexNum; u++)
		if (arcs[v][u] != 0 && arcs[v][u] != infinity)
       		return u;

	return -1;					// 返回-1表示无邻接点
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点			 
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw
       Error("v1不能等于v2!");		// 抛出异常

	for (int u = v2 + 1; u < vexNum; u++)
		if (arcs[v1][u] != 0 && arcs[v1][u] != infinity)
       		return u;

	return -1;						// 返回-1表示无下一个邻接点
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::InsertVex(const ElemType &e)
// 操作结果：插入顶点e			 
{
	if (vexNum == vexMaxNum)
    throw Error("图的顶点数不能超过允许的最大数!");	// 抛出异常

	vertexes[vexNum] = e;
	tag[vexNum] = UNVISITED;
	
	for (int v = 0; v < vexNum; v++) {
		arcs[vexNum][v] = infinity;
		arcs[v][vexNum] = infinity;
  	}
  	arcs[vexNum][vexNum] = 0;
  	vexNum++;
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w)
// 操作结果：插入依附顶点v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum)
    throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
    throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
    throw Error("v1不能等于v2!");// 抛出异常

	if (arcs[v1][v2] == infinity)	{	  // 原无向图中没有边(v1, v2) 
	   edgeNum++;
	   arcs[v1][v2] = w;	
       arcs[v2][v1] = w;
    }
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::DeleteVex(const ElemType &e)
// 操作结果：删除元素为e的顶点			 
{
   int v;
   for (v = 0; v < vexNum; v++)
     if	(vertexes[v] == e)
        break;
   if (v == vexNum)
      throw Error("图中不存在要删除的顶点!");	// 抛出异常

   for (int u = 0; u < vexNum; u++)             // 删除与顶点e相关联的边 
	  if (u != v && arcs[v][u] != infinity) { 
		edgeNum--;
	    arcs[v][u] = infinity;	
        arcs[u][v] = infinity;	
    } 
	      
   vexNum--; 
   if (v < vexNum) {
      vertexes[v] = vertexes[vexNum];
	  tag[v] = tag[vexNum];
	  for (int u = 0; u <= vexNum; u++) 
		 arcs[v][u] = arcs[vexNum][u];
	  for (int u = 0; u <= vexNum; u++) 
         arcs[u][v] = arcs[u][vexNum];
   } 
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::DeleteArc(int v1, int v2)
// 操作结果：删除依附顶点v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum)
    throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
    throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
    throw Error("v1不能等于v2!");// 抛出异常

	if (arcs[v1][v2] != infinity)	{	// 原无向图存在边(v1, v2)
		edgeNum--;
	    arcs[v1][v2] = infinity;	
        arcs[v2][v1] = infinity;	
    } 
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// 操作结果：返回顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常

	return arcs[v1][v2];
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirNetwork<ElemType, WeightType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum)
    throw Error("v不合法!");	// 抛出异常

	return tag[v];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::SetTag(int v, Status val) const 
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum)
    throw Error("v不合法!");	// 抛出异常

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork<ElemType, WeightType> &g)
// 操作结果：由无向图的邻接矩阵g构造新无向图的邻接矩阵g——复制构造函数
{
	vexNum = g.vexNum;	
	vexMaxNum = g.vexMaxNum;
	edgeNum = g.edgeNum;	
	infinity = g.infinity;
	
	vertexes = new ElemType[vexMaxNum];		// 生成顶点数据数组
	tag = new Status[vexMaxNum];			// 生成标志数组
	arcs = (int **)new int *[vexMaxNum];	// 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++) 
		arcs[v] = new int[vexMaxNum];	

	for (int v = 0; v < vexNum; v++)	{	// 复制顶点数据数组
		vertexes[v] = g.vertexes[v];
		tag[v] = g.tag[v];
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = g.arcs[v][u];
	}
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType> &AdjMatrixUndirNetwork<ElemType, WeightType>::operator =(const AdjMatrixUndirNetwork<ElemType, WeightType> &g)
// 操作结果：将无向图的邻接矩阵g赋值给当前无向图的邻接矩阵——赋值语句重载
{
	if (&g != this)	{
		delete []vertexes;				// 释放顶点数据
		delete []tag;						  // 释放标志

	  	for (int v = 0; v < vexMaxNum; v++)	// 释放邻接矩阵的行
	 		delete []arcs[v];
    	delete []arcs;					  // 释放邻接矩阵
		vexNum = g.vexNum;	
    	vexMaxNum = g.vexMaxNum;
		edgeNum = g.edgeNum;	
		infinity = g.infinity;
	
		vertexes = new ElemType[vexMaxNum];	 // 生成顶点数据数组
		tag = new Status[vexMaxNum];			   // 生成标志数组
		arcs = (int **)new int *[vexMaxNum]; // 生成邻接矩阵
		for (int v = 0; v < vexMaxNum; v++) 
			arcs[v] = new int[vexMaxNum];	

		for (int v = 0; v < vexNum; v++)	{	 // 复制顶点数据数组
			vertexes[v] = g.vertexes[v];
			tag[v] = g.tag[v];
			for (int u = 0; u < vexNum; u++)
	    		arcs[v][u] = g.arcs[v][u];
		}
	}
	return *this;
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::Display()
// 操作结果: 显示邻接矩阵无向图
{
              
	for (int v = 0; v < vexNum; v++)
 		cout << "\t" << vertexes[v];
	cout << endl;

	for (int v = 0; v < vexNum; v++)	{
		cout << vertexes[v];
		for (int u = 0; u < vexNum; u++)
			if (arcs[v][u] == infinity)
				cout << "\t" << "∞";
			else
				cout << "\t" << arcs[v][u];
		cout << endl;
	}
}

#endif
