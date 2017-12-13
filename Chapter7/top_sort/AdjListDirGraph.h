#ifndef __ADJ_LIST_GRAPH_H__
#define __ADJ_LIST_GRAPH_H__
#include "Assistance.h"					// 辅助软件包
#include "AdjListDirGraphArc.h"			// 有向图邻接表的边结点类
#include "AdjListDirGraphVex.h"			// 有向图邻接表的顶点结点类

// 有向图的邻接表类
template <class ElemType>
class AdjListDirGraph
{
protected:
// 邻接表的数据成员:
	int vexNum, vexMaxNum, arcNum;			// 顶点数目、允许的顶点最大数目和边数
	AdjListGraphVex<ElemType> *vexTable;	// 顶点表
	mutable Status *tag;			        // 标志数组				

public:
// 邻接表的函数成员:
	AdjListDirGraph(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE);
		// 以数组es[]为顶点数据,顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,
        // 边数为0构造有向图
	AdjListDirGraph(int vertexMaxNum = DEFAULT_SIZE);
		// 构造允许的顶点最大数目为vertexMaxNum,顶点数和边数为0的有向图
	~AdjListDirGraph();						// 析构函数
	void Clear();			                    // 清空有向图			 
	bool IsEmpty();                             // 判断有向图是否为空 
	int GetOrder(ElemType &e) const;            // 求顶点e的序号	
	Status GetElem(int v, ElemType &e) const;   // 求顶点v的元素值	
	Status SetElem(int v, const ElemType &e);   // 设置顶点v的元素值为e
	int GetVexNum() const;						// 求有向图的顶点个数			 
	int GetArcNum() const;						// 求有向图的边数个数			 
	int FirstAdjVex(int v) const;				// 求有向图中顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		// 求有向图中顶点v1的相对于v2的下一个邻接点			 
	Status InsertVex(const ElemType &e);		// 插入元素值为e的顶点		 
	void InsertArc(int v1, int v2);				// 插入从顶点v1到v2的边			 
	void DeleteVex(const ElemType &e);			// 删除元素值为e的顶点			 
	void DeleteArc(int v1, int v2);			    // 删除从顶点为v1到v2的边			 
	Status GetTag(int v) const;				    // 求顶点v的标志		 
	void SetTag(int v, Status tag) const;	    // 设置顶点v的标志为tag	 
	AdjListDirGraph(const AdjListDirGraph<ElemType> &g);	// 复制构造函数
	AdjListDirGraph<ElemType> &operator =
		(const AdjListDirGraph<ElemType> &g); // 重载赋值运算符 
    void Display();	// 显示有向图的邻接表 
};

// 有向图的邻接表类的实现部分
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(ElemType es[],
       int vertexNum, int vertexMaxNum)
// 操作结果：构造顶点数据为es[],顶点数为numVex,顶点个数为vertexNum,边数为0的有向图
{
	if (vertexMaxNum < 0)
    	throw Error("允许的顶点最大数目不能为负!");        // 抛出异常

	if (vertexMaxNum < vertexNum)
    	throw Error("顶点数目不能大于允许的顶点最大数目!");// 抛出异常

	vexNum = vertexNum;			
	vexMaxNum = vertexMaxNum; 
	arcNum = 0;
	
	tag = new Status[vexMaxNum];
	vexTable = new AdjListGraphVex<ElemType>[vexMaxNum];
 
	for (int v = 0; v < vexNum; v++)  {
		tag[v] = UNVISITED;
		vexTable[v].data = es[v];
		vexTable[v].firstarc = NULL;
	}
}

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(int vertexMaxNum)
// 操作结果：构造顶点最大数目为vertexMaxNum的空有向图
{
	if (vertexMaxNum < 0)
    	throw Error("允许的顶点最大数目不能为负!");// 抛出异常

	vexNum = 0;			
	vexMaxNum = vertexMaxNum;
	arcNum = 0;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListGraphVex<ElemType>[vexMaxNum];
}

template <class ElemType>
AdjListDirGraph<ElemType>::~AdjListDirGraph()
// 操作结果：释放邻接表有向图所占用空间
{
    Clear();                                // 释放边结点
	delete []tag;							// 释放标志
	delete []vexTable;						// 释放邻接表
}

template <class ElemType>
void AdjListDirGraph<ElemType>::Clear()
// 操作结果：释放所有的边结点，并把有向图的顶点数和边数设置为0.			 
{
	AdjListGraphArc *p;
	for (int v = 0; v < vexNum; v++)	{	// 释放边结点
	    p = vexTable[v].firstarc;
	    while (p != NULL) {
			vexTable[v].firstarc = p->nextArc;
			delete p;
			p = vexTable[v].firstarc;
        }	
	}
    vexNum = 0;
	arcNum = 0;	
}

template <class ElemType>
bool AdjListDirGraph<ElemType>::IsEmpty()
// 操作结果：如果有向图为空返回true,否则返回false.
{
	return vexNum == 0;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetOrder(ElemType &e) const
// 操作结果：求顶点e的序号.顶点的序号从0开始，图中不存在顶点e时返回-1. 
{
    int v;
    for (v = 0; v < vexNum; v++)
        if (e == vexTable[v].data)
           break;
           
	if (v < 0 || v >= vexNum)
		return -1;	// 顶点e不存在,返回-1
	else
		return v;	// 顶点e存在,返回它的序号 
}	

template <class ElemType>
Status AdjListDirGraph<ElemType>::GetElem(int v, ElemType &e) const
// 操作结果：求序号为v的顶点值, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数
//	通过e取得顶点值，并返回ENTRY_FOUND；否则函数返回NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;			// 元素不存在
	else	{
		e = vexTable[v].data;		// 将顶点v的元素值赋给e
		return ENTRY_FOUND;			// 元素存在
	}
}	

template <class ElemType>
Status AdjListDirGraph<ElemType>::SetElem(int v, const ElemType &e)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;			// 位置错
	else	{
		vexTable[v].data = e;		// 顶点元素
		return SUCCESS;				// 成功
	}
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetArcNum() const
// 操作结果：返回边数个数
{
	return arcNum;
}		 

template <class ElemType>
int AdjListDirGraph<ElemType>::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第一个邻接点			 
{
	if (v < 0 || v >= vexNum)
       throw Error("v不合法!");// 抛出异常

	if (vexTable[v].firstarc == NULL)
	   return -1;              // 不存在邻接点
	else
	   return vexTable[v].firstarc->adjVex;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点			 
{
	AdjListGraphArc *p;
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
       throw Error("v1不能等于v2!");// 抛出异常
	
	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex != v2)
	    p = p->nextArc;

	if (p == NULL || p->nextArc == NULL)
		return -1;                   // 不存在下一个邻接点
	else
		return p->nextArc->adjVex;
}

template <class ElemType>
Status AdjListDirGraph<ElemType>::InsertVex(const ElemType &e)
// 操作结果：在顶点表的表尾插入元素值为e的顶点。			 
{
	if (vexNum == vexMaxNum)
       return OVER_FLOW;			// 返回溢出 

	vexTable[vexNum].data = e;
	vexTable[vexNum].firstarc = NULL;
	tag[vexNum] = UNVISITED;
    vexNum++;
    return SUCCESS; 
}

template <class ElemType>
void AdjListDirGraph<ElemType>::InsertArc(int v1, int v2)
// 操作结果：插入顶点为v1和v2,权为w的边			 
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
       throw Error("v1不能等于v2!");// 抛出异常

	AdjListGraphArc *p, *q;
	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex != v2) {
		q = p;
		p = p->nextArc;
	}
	if (p == NULL) {
		if (vexTable[v1].firstarc == NULL)
    		vexTable[v1].firstarc = new AdjListGraphArc(v2);
    	else 
    		q->nextArc = new AdjListGraphArc(v2);
    			arcNum++;
	}
    else
       throw Error("这条边已经存在!");// 抛出异常
}

template <class ElemType>
void AdjListDirGraph<ElemType>::DeleteVex(const ElemType &e)
// 操作结果：删除元素值为e的顶点			 
{
    int v;
    AdjListGraphArc *p, *q;
    for (v = 0; v < vexNum; v++)
       if	(vexTable[v].data == e)
           break;
	if (v == vexNum)
       throw Error("图中不存在要删除的顶点!");	// 抛出异常

    for (int u = 0; u < vexNum; u++)           // 删除到达e的弧 
       if (u != v) 
          DeleteArc(u, v); 
          
	p = vexTable[v].firstarc;                  // 删除从e出发的弧 
	while (p != NULL) {
        vexTable[v].firstarc = p->nextArc;
        delete p;    
	    p = vexTable[v].firstarc;
		arcNum--;
	}

    vexNum--;
    vexTable[v].data = vexTable[vexNum].data;
    vexTable[v].firstarc = vexTable[vexNum].firstarc;
    vexTable[vexNum].firstarc = NULL;
    tag[v] = tag[vexNum];

    for (int u = 0; u < vexNum; u++)         
       if (u != v) {
	      p = vexTable[u].firstarc;
	      while (p != NULL) {
             if (p->adjVex == vexNum)
                p->adjVex = v;
             p = p->nextArc;
          }
       }   
}

template <class ElemType>
void AdjListDirGraph<ElemType>::DeleteArc(int v1, int v2)
// 操作结果：删除顶点为v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw
       Error("v1不能等于v2!");		// 抛出异常

	AdjListGraphArc *p, *q;
	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex != v2) {
        q = p;
        p = p->nextArc;
    }
    if (p != NULL) {
	    if (vexTable[v1].firstarc == p)
            vexTable[v1].firstarc = p->nextArc;
        else
            q->nextArc = p->nextArc;
        delete p;    
		arcNum--;
	}
	else
       Error("v1到v2没有弧。");		// 抛出异常
}

template <class ElemType>
Status AdjListDirGraph<ElemType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum)
       throw Error("v不合法!");		// 抛出异常

	return tag[v];
}

template <class ElemType>
void AdjListDirGraph<ElemType>::SetTag(int v, Status val) const
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum)
       throw Error("v不合法!");		// 抛出异常

	tag[v] = val;
}

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(const AdjListDirGraph<ElemType> &g)
// 操作结果：由有向图的邻接矩阵g构造新有向图的邻接矩阵g——复制构造函数
{
	AdjListGraphArc *p, *q;
	vexNum = g.vexNum;
	vexMaxNum = g.vexMaxNum;	
	arcNum = g.arcNum;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListGraphVex<ElemType>[vexMaxNum];
	for (int v = 0; v < vexNum; v++)	{
		tag[v] = g.tag[v];
		vexTable[v].data = g.vexTable[v].data;
		vexTable[v].firstarc = NULL;
		p = g.vexTable[v].firstarc;
		while (p != NULL) 
           if (vexTable[v].firstarc == NULL) {
              vexTable[v].firstarc = new AdjListGraphArc(p->adjVex);	
              q = vexTable[v].firstarc;
              p = p->nextArc;
           }
           else {   
              q->nextArc = new AdjListGraphArc(p->adjVex);	
              q = q->nextArc;
              p = p->nextArc;
           }   
	}
}

template <class ElemType>
AdjListDirGraph<ElemType> &AdjListDirGraph<ElemType>::operator =(const AdjListDirGraph<ElemType> &g)
// 操作结果：将有向图的邻接矩阵g赋值给当前有向图的邻接矩阵——赋值语句重载
{
	if (&g != this)
	{
        Clear();                                    // 释放当前有向图边结点
	    delete []tag;								// 释放当前有向图标志数组 
	    delete []vexTable;							// 释放当前有向图顶点表 

	    AdjListGraphArc *p, *q;
	    vexNum = g.vexNum;
	    vexMaxNum = g.vexMaxNum;	
	    arcNum = g.arcNum;

	    tag = new Status[vexMaxNum];
	    vexTable = new AdjListGraphVex<ElemType>[vexMaxNum];
	    for (int v = 0; v < vexNum; v++)	{
		   tag[v] = g.tag[v];
		   vexTable[v].data = g.vexTable[v].data;
		   vexTable[v].firstarc = NULL;
		   p = g.vexTable[v].firstarc;
		   while (p != NULL) 
               if (vexTable[v].firstarc == NULL) {
                  vexTable[v].firstarc = new AdjListGraphArc(p->adjVex);	
                  q = vexTable[v].firstarc;
                  p = p->nextArc;
               }
               else {   
                  q->nextArc = new AdjListGraphArc(p->adjVex);	
                  q = q->nextArc;
                  p = p->nextArc;
               }   
	   }
    }
	return *this;
}

template <class ElemType>
void AdjListDirGraph<ElemType>::Display()
// 操作结果: 显示邻接矩阵有向图
{
	AdjListGraphArc *p;
    cout << "有向图共有" << vexNum << "个顶点，" << arcNum << "条边。" << endl; 
	for (int v = 0; v < vexNum; v++)	{	// 显示第v个邻接链表
		cout << v << ":\t" << vexTable[v].data;				// 显示顶点号
	    p = vexTable[v].firstarc;
	    while (p != NULL) {
        	cout << "-->(" << p->adjVex << ")";
            p = p->nextArc; 
		}
		cout << endl; 
	}
}

#endif
