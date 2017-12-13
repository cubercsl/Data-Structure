#ifndef __ELEM_NODE_H__
#define __ELEM_NODE_H__


// 并查集元素结点类
template <class ElemType>
struct ElemNode 
{
// 数据成员:
	ElemType data;				// 数据域
	int parent;	                // 双亲域 
};

#endif


#ifndef __UFSETS_H__			// 如果没有定义__UFSETS_H__
#define __UFSETS_H__			// 那么定义__UFSETS_H__

// 并查集
template <class ElemType>
class UFSets
{
protected:
// 并查集的数据成员:
	ElemNode<ElemType> *sets;	         // 存储结点的双亲
	int size;					         // 结点个数

// 辅助函数
    int Find(ElemType e) const;		     // 查找元素e所在等价类的根
    int CollapsingFind(ElemType e) const;// 查找元素e所在等价类的根

public:
// 并查集的函数成员:
	UFSets(ElemType es[], int n);	     // 构造sz个单结点树(等价类)
	virtual ~UFSets();				     // 析构函数
	ElemType GetElem(int p)const;        // 取指定元素在数组中的下标 
	int GetOrder(ElemType e)const;       // 根据指定下标取元素值 
	void Union(ElemType a, ElemType b);	 // 合并a与b所在的等价类
	void WeightedUnion(ElemType a, ElemType b);	 // 根据结点多少合并a与b所在的等价类
    bool Differ(ElemType a, ElemType b); // 判断元素a、b是否在同一个等价类
	UFSets(const UFSets &copy);		     // 复制构造函数
	UFSets &operator =(const UFSets &copy);	// 赋值运算符
};

                                                                                                                                       
// 并查集的实现部分
template <class ElemType>
UFSets<ElemType>::UFSets(ElemType es[], int n)
// 操作结果：根据数组es中的元素，构造n个单元素等价类
{
	size = n;									// 设置容量
	sets = new ElemNode<ElemType>[size];		// 分配空间
	for (int i = 0; i < size; i++) {
        sets[i].data = es[i];
		sets[i].parent = -1;			
    }
}

template <class ElemType>
int UFSets<ElemType>::Find(ElemType e) const
// 操作结果：查找元素e所在树的根
{
    int p = 0;
    while (p < size && sets[p].data != e)
        p++;
	if (p == size)
		throw Error("元素不存在!");				// 抛出异常
	while (sets[p].parent > -1)
        p = sets[p].parent;                     // 查找根
	return p;					
}

template <class ElemType>
int UFSets<ElemType>::CollapsingFind(ElemType e) const
// 操作结果：带压缩路径功能，查找元素e所在树的根
{
    int i, k, p = 0;
    while (p < size && sets[p].data != e)
        p++;
	if (p == size)
		throw Error("元素不存在!");				// 抛出异常
    for(i = p ; sets[i].parent >= 0; i= sets[i].parent) ; //查找p的根结点的序号i
    while ( i!= sets[p].parent ) {  //从p开始向上逐层压缩
        k = sets[p].parent ;
        sets[p].parent = i;
        p = k; 
    }
    return i; 
}


template <class ElemType>
UFSets<ElemType>::~UFSets()
// 操作结果：释放对象占用的空间——析构函数
{
	delete []sets;							// 释放数组parent
}

template <class ElemType>
ElemType UFSets<ElemType>::GetElem(int p) const
// 操作结果：求下标为p的元素值 
{
	if (p < 0 || p >= size)
		throw Error("元素不存在!");			// 抛出异常
	return sets[p].data;					// 返回元素值
}

template <class ElemType>
int UFSets<ElemType>::GetOrder(ElemType e) const
// 操作结果：取指定元素e的下标 
{
    int p = 0;
    while (p < size && sets[p].data != e)
        p++;
	if (p == size)
		throw Error("元素不存在!");			// 抛出异常
	return p;							    // 返元素下标 
}

template <class ElemType>
void UFSets<ElemType>::Union(ElemType a, ElemType b)
// 操作结果：合并a与b所在的等价类
{
	int r1 = Find(a);					// 查找a所在等价类的根		
	int r2 = Find(b);					// 查找b所在等价类的根		
	if (r1 != r2) {
       sets[r1].parent += sets[r2].parent;
       sets[r2].parent = r1;	        // 合并等价类
    }
}

template <class ElemType>
void UFSets<ElemType>::WeightedUnion(ElemType a, ElemType b)
// 操作结果：根据结点多少合并a与b所在的等价类
{
	int r1 = Find(a);					// 查找a所在等价类的根		
	int r2 = Find(b);					// 查找b所在等价类的根		
	if (r1 != r2) {
       int  temp = sets[r1].parent + sets[r2].parent;
       if (sets[r1].parent <= sets[r2].parent ) {
           sets[r2].parent = r1;          
           sets[r1].parent = temp;  
       }
       else {  
           sets[r1].parent = r2;       //r1中的结点个数少，r1指向r2 
           sets[r2].parent = temp;       
       }
    }
}

template <class ElemType>
bool UFSets<ElemType>::Differ(ElemType a, ElemType b)
// 操作结果：如果a与b不在同一等价类上，返回true，否则返回false
{
	int root1 = Find(a);				    // 查找a所在等价类的根		
	int root2 = Find(b);					// 查找b所在等价类的根		
	return root1 != root2;					
}

template <class ElemType>
UFSets<ElemType>::UFSets(const UFSets &copy)
// 操作结果：由copy构造新对象——复制构造函数
{
	size = copy.size;						// 设置容量
	sets = new ElemNode<ElemType>[size];	// 分配空间
	for (int i = 0; i < size; i++) 
		sets[i] = copy.sets[i];             // 复制每个元素
}

template <class ElemType>
UFSets<ElemType> &UFSets<ElemType>::operator=(const UFSets<ElemType> &copy)
// 操作结果：将copy赋值给当前对象——赋值运算符
{
	if (&copy != this)	{
		size = copy.size;					// 设置容量
		delete []sets;						// 释放原空间
	    sets = new ElemNode<ElemType>[size];// 分配新空间
	    for (int i = 0; i < size; i++) 
		    sets[i] = copy.sets[i];			// 复制每个元素
	}
	return *this;
}

#endif
