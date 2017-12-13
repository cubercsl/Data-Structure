#ifndef __SQ_BINNARY_TREE_H__
#define __SQ_BINNARY_TREE_H__
#include "Assistance.h"						// 辅助软件包
#include "LinkQueue.h"						// 链队列

// 顺序二叉树类
template <class ElemType>
class SqBinaryTree
{
protected:
//  顺序二叉树的数据成员:
	int maxSize;					       // 顺序二叉树的最大存储空间 
	int *tag;	                           // 结点使用标志
	ElemType *elems;					   // 结点存储空间

//	辅助函数:
	int NodeCount(int r) const;							// 统计以r为根的二叉树中结点个数
	void SetNodeEmpty(int p);							// 将结点p置空
	void Destroy(int r);								// 删除以r为根的二叉树
	void PreOrder(int r, void (*Visit)(const ElemType &)) const;// 先序遍历以r为根的二叉树
	void InOrder(int r, void (*Visit)(const ElemType &)) const;	// 中序遍历以r为根的二叉树
	void PostOrder(int r, void (*Visit)(const ElemType &)) const;// 后序遍历以r为根的二叉树
    int Height(int r) const;							// 求以r为根的二叉树的高度 

public:
//  顺序二叉树的函数成员:
	SqBinaryTree(int size = DEFAULT_SIZE);				// 构造函数
	virtual ~SqBinaryTree();							// 析构函数
	int GetRoot() const;					            // 求二叉树中根结点 
	bool IsNodeEmpty(int p) const;					    // 判断结点p是否为空
	Status GetElem(int p, ElemType &e);				    // 返回结点p的元素值
	Status SetElem(int p, const ElemType &e);			// 将结点p的值置为e
	bool IsEmpty() const;								// 判断二叉树是否为空
	void InOrder(void (*Visit)(const ElemType &)) const;// 中序遍历二叉树	
	void PreOrder(void (*Visit)(const ElemType &)) const;// 先序遍历二叉树
	void PostOrder(void (*Visit)(const ElemType &)) const;// 后序遍历二叉树
	void LevelOrder(void (*Visit)(const ElemType &)) const;// 层次遍历二叉树
	int NodeCount() const;								// 求二叉树的结点个数
	int LeftChild(const int p) const;					// 求二叉树中结点p的左孩子
	int RightChild(const int p) const;				    // 求二叉树中结点p的右孩子
	int LeftSibling(const int p) const;					// 求二叉树中结点p的左兄弟 
	int RightSibling(const int p) const;				// 求二叉树中结点p的右兄弟
	int Parent(const int p) const;					    // 求二叉树中结点p的双亲
	int Find(const ElemType &e) const;						// 查找二叉树中元素e 
	Status InsertLeftChild(int p, const ElemType &e);	// 插入元素作为结点p左孩子
	Status InsertRightChild(int p, const ElemType &e);  // 插入元素作为结点p右孩子
	Status DeleteLeftChild(int p);					    // 删除二叉树中结点p左子树
	Status DeleteRightChild(int p);					    // 删除二叉树中结点p右子村
	int	Height() const;									// 求二叉树的高
	SqBinaryTree(const ElemType &e, int size = DEFAULT_SIZE);   // 建立以e为根的二叉树
	SqBinaryTree(const SqBinaryTree<ElemType> &t);		    // 复制构造函数
	SqBinaryTree(ElemType es[], int ta[], int size = DEFAULT_SIZE);	
		// 由es[]、ta[]与size构造二叉树
	SqBinaryTree<ElemType> &operator=(const SqBinaryTree<ElemType>& t);		
		// 赋值运算符重载
};


template <class ElemType>
void DisplayBTWithTreeShape(int r, int level);
	//	按树状形式显示以r为根的二叉树，level为层次数，设根结点的层次数为1
template <class ElemType>
void DisplayBTWithTreeShape(SqBinaryTree<ElemType> &bt);
	//	树状形式显示二叉树 
template <class ElemType>
void CreateBinaryTree(ElemType es[], int ta[], int r, ElemType pre[], ElemType in[], 
	int preLeft, int preRight, int inLeft, int inRight);	
	// 已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造以r为根的二叉树
template <class ElemType>
SqBinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n, int size = DEFAULT_SIZE);
	// 已知先序和中序序列构造二叉树

// 顺序二叉树类的实现部分
template <class ElemType>
bool SqBinaryTree<ElemType>::IsNodeEmpty(int p) const
// 操作结果：如果结点p为空,则返回true,否则返回false
{
	if(p < 0 || p >= maxSize || tag[p] == 0)
        return true;	// 此时结点为空
	else
        return false;
}

template <class ElemType>
Status SqBinaryTree<ElemType>::GetElem(int p, ElemType &e)
// 操作结果：用e返回结点p的元素值,则操作成功,函数返回SUCCESS,否则返回FAIL
{
	if (IsNodeEmpty(p))
        return FAIL;                // 操作失败
	else	{
		e = elems[p];				// 用e返回结点p的元素值
		return SUCCESS;				// 操作成功
	}
}

template <class ElemType>
Status SqBinaryTree<ElemType>::SetElem(int p, const ElemType &e)
// 操作结果：如果不存在结点p,则返回FAIL,否则返回SUCCESS,并将结点p的值设置为e
{
	if (IsNodeEmpty(p))
        return FAIL;		        // 操作失败
	else	{	// 存在结点p
		elems[p] = e;				// 将结点p的值设置为e
		return SUCCESS;				// 返回SUCCESS
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::SetNodeEmpty(int p)
// 操作结果：将结点p置空
{
	if (p >= 0 && p < maxSize && (2 * p + 1 >= maxSize || tag[2 * p + 1] == 0)
        && (2 * p + 2 >= maxSize || tag[2 * p + 2] == 0))
        tag[p] = 0;	// 将p置空
}

template <class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree(int size)
// 操作结果：构造一棵空二叉树
{
	maxSize = size;			             // 设置二叉树的最大容量 
	elems = new ElemType[maxSize];	     // 分配数据元素的存储空间
	tag = new int[maxSize];	// 分配标记数组的存储空间
	for (int i = 0; i <maxSize; i++)	 // 将所有结点标识为空
		tag[i] = 0;
}

template <class ElemType>
SqBinaryTree<ElemType>::~SqBinaryTree()
// 操作结果：删除二叉树
{
	delete []elems;					// 释放元素存储空间
	delete []tag;					// 释放标记存储空间
}

template <class ElemType>
int SqBinaryTree<ElemType>::GetRoot() const
// 操作结果：返回二叉树的根结点 
{
	if (tag[0] == 1)
      return  0;
    else 
      return  -1 ; 
}

template <class ElemType>
bool SqBinaryTree<ElemType>::IsEmpty() const
// 操作结果：判断二叉树是否为空
{
	return IsNodeEmpty(0);
}

template <class ElemType>
void SqBinaryTree<ElemType>::PreOrder(int r, void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历以r为根的二叉树
{
	if (!IsNodeEmpty(r)) 	{	            // 根非空
		(*Visit)(elems[r]);			        // 访问根结点
		PreOrder(LeftChild(r), Visit);		// 遍历左子树
		PreOrder(RightChild(r), Visit);		// 遍历右子树
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历二叉树
{
	PreOrder(0, Visit);	
}	

template <class ElemType>
void SqBinaryTree<ElemType>::InOrder(int r, void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历以r为根的二叉树
{
	if (!IsNodeEmpty(r)) 	{	            // 根非空
		InOrder(LeftChild(r), Visit);		// 遍历左子树
		(*Visit)(elems[r]);					// 访问根结点
		InOrder(RightChild(r), Visit);		// 遍历右子树
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历二叉树
{
	InOrder(0, Visit);	
}	

template <class ElemType>
void SqBinaryTree<ElemType>::PostOrder(int r, void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历以r为根的二叉树
{
	if (!IsNodeEmpty(r)) 	{	            // 根非空
		PostOrder(LeftChild(r), Visit);		// 遍历左子树
		PostOrder(RightChild(r), Visit);	// 遍历右子树
		(*Visit)(elems[r]);					// 访问根结点
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::PostOrder(void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历二叉树
{
	PostOrder(0, Visit);	
}	

template <class ElemType>
void SqBinaryTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历二叉树
{
	LinkQueue<int> q;					// 定义辅助队列
	int t = 0;							// 从根结点开始进行层次遍历
	
	if (!IsNodeEmpty(t))
        q.EnQueue(t);		// 如果根非空,则入队
	while (!q.IsEmpty())	{	// q非空,说明还有结点未访问
		q.DelQueue(t);     
		(*Visit)(elems[t]);
		if (!IsNodeEmpty(LeftChild(t)))				// 左孩子非空
			q.EnQueue(LeftChild(t));				// 左孩子入队
		if (!IsNodeEmpty(RightChild(t)))			// 右孩子非空
			q.EnQueue(RightChild(t));			// 右孩子入队
	}
}

template <class ElemType>
int SqBinaryTree<ElemType>::Height(int r) const
// 操作结果：返回以r为根的二叉树的高
{
	if(IsNodeEmpty(r))		// 空二叉树的高为0
		return 0;
	else	{	
		int lHeight, rHeight;
		lHeight = Height(LeftChild(r));		// 求r的左子树的高
		rHeight = Height(RightChild(r));	// 求r的右子树的高
		return (lHeight > rHeight ? lHeight + 1: rHeight + 1);
			// 非空二叉树高为左右子树的高的最大值再加1
	}
}

template <class ElemType>
int SqBinaryTree<ElemType>::Height() const
// 操作结果：返回二叉树的高
{
	return Height(0);
}

template <class ElemType>
int SqBinaryTree<ElemType>::NodeCount(int r) const
// 操作结果：返回以r为根的二叉树的结点个数
{
	if (IsNodeEmpty(r))
       return 0;// 空二叉数结点个数为0
	else
       return 1 + NodeCount(LeftChild(r)) + NodeCount(RightChild(r));
                // 非空二叉树结点个为左右子树的结点个数之和再加1
}

template <class ElemType>
int SqBinaryTree<ElemType>::NodeCount() const
// 操作结果：返回二叉树的结点个数
{
	return NodeCount(0);
}

template <class ElemType>
int SqBinaryTree<ElemType>::LeftChild(const int p) const
// 操作结果：返回二叉树结点p的左孩子
{
	if (2 * p + 1 < maxSize && tag[2 * p + 1] == 1)
      return  2 * p + 1;
    else 
      return  -1 ; 
}

template <class ElemType>
int SqBinaryTree<ElemType>::RightChild(const int p) const
// 操作结果：返回二叉树结点p的右孩子
{
	if (2 * p + 2 < maxSize && tag[2 * p + 2] == 1)
      return  2 * p + 2;
    else 
      return  -1 ; 
}

template <class ElemType>
int SqBinaryTree<ElemType>::LeftSibling(const int p) const
// 操作结果：返回二叉树结点p的左兄弟 
{
	if (p % 2 == 1 || p == 0 || tag[p - 1] == 0)
        return -1;
    else 
        return p - 1; 
}

template <class ElemType>
int SqBinaryTree<ElemType>::RightSibling(const int p) const
// 操作结果：返回二叉树结点p的右兄弟
{
	if (p % 2 == 0 || p + 1 >= maxSize || tag[p + 1] == 0)
        return -1;
    else 
        return p + 1; 
}

template <class ElemType>
int SqBinaryTree<ElemType>::Parent(const int p) const
// 操作结果：返回二叉树结点p的双亲
{
	return p > 0 ? (p - 1) / 2 : -1;
}

template <class ElemType>
int SqBinaryTree<ElemType>::Find(const ElemType &e) const
// 操作结果：查找二叉树中元素e，查找成功返回其在数组的下标，否则返回-1. 
{
	LinkQueue<int> q;					// 定义辅助队列
	int t = 0;							
	
	if (!IsNodeEmpty(t))
        q.EnQueue(t);					// 如果根非空,则入队
	while (!q.IsEmpty())	{			// q非空,说明还有结点未访问
		q.DelQueue(t);     
		if (elems[t] == e)
			return t;
		if (!IsNodeEmpty(LeftChild(t)))				// 左孩子非空
			q.EnQueue(LeftChild(t));				// 左孩子入队
		if (!IsNodeEmpty(RightChild(t)))			// 右孩子非空
			q.EnQueue(RightChild(t));			// 右孩子入队
	}
	return -1;
}


template <class ElemType>
Status SqBinaryTree<ElemType>::InsertLeftChild(int p, const ElemType &e)
// 操作结果：插入e为p的左孩子。如果p为空、或者p的左孩子非空、或者或者p的左孩子位置不在数组有效范围，则操作作失败
{
	if (IsNodeEmpty(p))
		return FAIL;
	else 	{	// 插入左孩子    
		if (2 * p + 1 < maxSize && 2 * p + 1 > 0 && tag[2 * p + 1] == 0)	{	// p左孩子为空,且位置合法
			elems[2 * p + 1] = e;				// 设置左孩子元素值
			tag[2 * p + 1] = 1;		            // 设置左孩子标志
			return SUCCESS;						// 返回SUCCESS
		}
		else
		    return FAIL;
	}
}

template <class ElemType>
Status SqBinaryTree<ElemType>::InsertRightChild(int p, const ElemType &e)
// 操作结果：插入e为p的右孩子。如果p为空、或者p的右孩子非空、或者或者p的右孩子位置不在数组有效范围，则操作作失败
{
	if (IsNodeEmpty(p))
		return FAIL;
	else	{	// 插入右孩子
		if (2 * p + 2 < maxSize && 2 * p + 2 > 0 && tag[2 * p + 2] == 0)	{	// p左孩子为空,且位置合法
			elems[2 * p + 2] = e;				// 设置左孩子元素值
			tag[2 * p + 2] = 1;		            // 设置左孩子标志
			return SUCCESS;						    // 返回SUCCESS
		}
		else
            return FAIL;
	}
}

template <class ElemType>
Status SqBinaryTree<ElemType>::DeleteLeftChild(int p)
// 操作结果：如果p非空，则删除p左子树；否则操作失败。 
{
	if (IsNodeEmpty(p))
		return FAIL;
	else  { 
		Destroy(LeftChild(p));
		return SUCCESS;			
	}
}

template <class ElemType>
Status SqBinaryTree<ElemType>::DeleteRightChild(int p)
// 操作结果：如果p非空，则删除p右子树；否则操作失败。 
{
	if (IsNodeEmpty(p))
		return FAIL;
	else	{
		Destroy(RightChild(p));	
		return SUCCESS;		
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::Destroy(int r)
// 操作结果：删除以r为根的二叉树
{
	if(r >=0 && r < maxSize && !IsNodeEmpty(r))	{ // r非空,实施删除
		Destroy(LeftChild(r));		// 删除左子树
		Destroy(RightChild(r));		// 删除右子树
		tag[r] = 0;			// 将r置空
	}
}

template <class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree(const ElemType &e, int size)
// 操作结果：建立以e为根的最大结点个数为size的二叉树
{
	maxSize = size;					// 最大结点个数
	elems = new ElemType[maxSize];	// 分配数据元素的存储空间
	tag = new int[maxSize];	        // 分配标记数组的存储空间
	for (int i = 1; i <maxSize; i++)// 将所有结点标识为空
		tag[i] = 0;
	tag[0] = 1;	                    // 设置根标志
	elems[0] = e;			        // 设置根的数据元素值
}


template <class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree(const SqBinaryTree<ElemType> &t)
// 操作结果：由已知二叉树构造新二叉树——复制构造函数
{
	maxSize = t.maxSize;			// 最大结点个数
	elems = new ElemType[maxSize];	// 分配数据元素的存储空间
	tag = new int[maxSize];	        // 分配标记数组的存储空间
	for (int i = 0; i <maxSize; i++)	{
		elems[i] = t.elems[i];           // 复制结点元素 
		tag[i] = t.tag[i];             // 复制结点标记
    }
}

template <class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree(ElemType es[], int ta[], int size)
// 操作结果：由元素数组es[]和标记数组ta[]构造最大空间为size的二叉树, 
{
	maxSize = size;					// 设置最大空间
	elems = new ElemType[maxSize];	// 分配数据元素的存储空间
	tag = new int[maxSize];	        // 分配标记数组的存储空间
	for (int i = 0; i <maxSize; i++)	{
		elems[i] = es[i];           // 复制结点元素 
		tag[i] = ta[i];             // 复制结点标记
    }
}

template <class ElemType>
SqBinaryTree<ElemType> &SqBinaryTree<ElemType>::operator=(const SqBinaryTree<ElemType> &t)
// 操作结果：由已知二叉树t复制到当前二叉树--赋值运算符重载
{
	if (&t != this)	{
		delete []elems;					// 释放存储空间
		maxSize = t.maxSize;		    // 设置最大空间
	    elems = new ElemType[maxSize];	// 分配数据元素的存储空间
        tag = new int[maxSize];	        // 分配标记数组的存储空间

		for (int i = 0; i <maxSize; i++){
		    elems[i] = t.elems[i];           // 复制结点元素 
		    tag[i] = t.tag[i];             // 复制结点标记
        }
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShape(SqBinaryTree<ElemType> &bt, int r, int level)
//	操作结果：按树状形式显示二叉树bt中以r为根的子树，level为层次数。
{
	if(!bt.IsNodeEmpty(r))	{	        //空树不显式，只显式非空树
		DisplayBTWithTreeShape<ElemType>(bt, bt.RightChild(r), level + 1);//显示右子树
		cout << endl;					//显示新行	
		for(int i = 0; i < level - 1; i++)
			cout << "  ";				//确保在第level列显示结点
		ElemType e;
		bt.GetElem(r, e);
		cout << e;						//显示结点
		DisplayBTWithTreeShape<ElemType>(bt, bt.LeftChild(r), level + 1);//显示左子树
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(SqBinaryTree<ElemType> &bt)
//	操作结果：树状形式显示二叉树 
{
	DisplayBTWithTreeShape<ElemType>(bt, 0, 1);	
		// 树状显示二叉树bt
	cout << endl;
}

template <class ElemType>
void CreateBinaryTree(ElemType es[], int ta[], int r, ElemType pre[], ElemType in[], 
	int preLeft, int preRight, int inLeft, int inRight)	
// 操作结果：已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造
//	以r为根的二叉树
{
	if (inLeft <= inRight)	{	// 二叉树有结点,非空二叉树
		es[r] = pre[preLeft]; ta[r] = 1; // 生成根结点
		int mid = inLeft;
		while (in[mid] != pre[preLeft]) // 查找pre[preLeft]在in[]中的位置,也就是中序序列中根的位置
			mid++;
		CreateBinaryTree(es, ta, 2 * r + 1, pre, in, preLeft+1, preLeft + mid - inLeft, inLeft, mid - 1);
                                        // 生成左子树
		CreateBinaryTree(es, ta, 2 * r + 2, pre, in, preLeft + mid - inLeft + 1, preRight, mid + 1, 
			inRight);					// 生成右子树
	}
} 

template <class ElemType>
SqBinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n, int size)
// 操作结果：已知先序和中序序列构造二叉树
{
	ElemType *es = new ElemType[size];	// 分配元素数组的临时空间
    int *ta = new int[size];	        // 分配标记数组的临时空间
	int r = 0;							// 二叉树的根
	for (int i = 0; i < size; i++)
	    ta[i] = 0;
	CreateBinaryTree<ElemType>(es, ta, r, pre, in, 0, n - 1, 0, n - 1);
		// 由先序和中序序列构造以r为根的二叉树 
	SqBinaryTree<ElemType> *bt = new SqBinaryTree<ElemType>(es, ta, size);	// 生成二叉树
	delete []es;
    delete []ta;						// 释放临时空间
	return *bt;
}

#endif
