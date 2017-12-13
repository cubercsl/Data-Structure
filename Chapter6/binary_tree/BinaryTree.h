#ifndef __BINNARY_TREE_H__
#define __BINNARY_TREE_H__

#include "LinkQueue.h"				// 链队列
#include "BinTreeNode.h"			// 二叉树结点类

// 二叉树类
template <class ElemType>
class BinaryTree
{
protected:
//  二叉树的数据成员:
	BinTreeNode<ElemType> *root;

//	辅助函数:
	BinTreeNode<ElemType> *CopyTree(BinTreeNode<ElemType> *t);
// 复制二叉树
	void Destroy(BinTreeNode<ElemType> * &r);	// 删除以r为根二叉树
	void PreOrder(BinTreeNode<ElemType>*r,void(*Visit)(const ElemType&)) const;
		// 先序遍历以r为根的二叉树
	void InOrder(BinTreeNode<ElemType>*r,void (*Visit)(const ElemType &)) const;
		// 中序遍历以r为根的二叉树
	void PostOrder(BinTreeNode<ElemType>*r,
void (*Visit)(const ElemType &)) const;	// 后序遍历以r为根的二叉树
    int Height(const BinTreeNode<ElemType> *r) const;	
// 求以r为根的二叉树的高
	int NodeCount(const BinTreeNode<ElemType> *r) const;
// 求以r为根的二叉树的结点个数
	BinTreeNode<ElemType> *Parent(BinTreeNode<ElemType> *r, 
		const BinTreeNode<ElemType>*p) const;//在以r为根的二叉树中求p的双亲

public:
//  二叉树方法声明及重载编译系统默认方法声明:
	BinaryTree();						// 无参数的构造函数
	BinaryTree(const ElemType &e);		// 构造以e为根的二叉树
	virtual ~BinaryTree();				// 析构函数
	BinTreeNode<ElemType> *GetRoot() const;	// 返回二叉树的根
	bool IsEmpty() const;				// 判断二叉树是否为空
	Status GetElem(BinTreeNode<ElemType> *p, ElemType &e) const;
		// 用e返回结点p元素值
	Status SetElem(BinTreeNode<ElemType> *p, const ElemType &e);
		// 将结点p的值置为e
	void InOrder(void (*Visit)(const ElemType &)) const;// 二叉树的中序遍历	
	void PreOrder(void (*Visit)(const ElemType &)) const;// 二叉树的先序遍历
	void PostOrder(void (*Visit)(const ElemType &)) const;// 二叉树的后序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;	// 二叉树的层次遍历
	int NodeCount() const;				// 求二叉树的结点个数
	BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> *p) const;
		//  求结点p的左孩子
	BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> *p) const;
		// 求结点p的右孩子
	BinTreeNode<ElemType> *LeftSibling(const BinTreeNode<ElemType> *p) const;
		// 求结点p的左兄弟 
	BinTreeNode<ElemType>*RightSibling(const BinTreeNode<ElemType>*p) const;
		// 求结点p的右兄弟
	BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> *p) const;
		// 求结点p的双亲
	BinTreeNode<ElemType> *Find(const ElemType &e) const;
		// 查找元素e，查找成功返回结点指针，否则返回NULL 
	void InsertLeftChild(BinTreeNode<ElemType> *p, const ElemType &e);
        // 插入一个结点e作为p的左孩子
	void InsertRightChild(BinTreeNode<ElemType> *p, const ElemType &e);
        // 插入一个结点e作为p的右孩子
	void DeleteLeftChild(BinTreeNode<ElemType> *p);	// 删除p的左子树
	void DeleteRightChild(BinTreeNode<ElemType> *p);// 删除p的右子树
	int	Height() const;							    // 求二叉树的高
	BinaryTree(const BinaryTree<ElemType> &t);	// 复制构造函数
	BinaryTree(BinTreeNode<ElemType> *r);			// 建立以r为根的二叉树
	BinaryTree<ElemType> &operator=(const BinaryTree<ElemType>& t);
		// 赋值运算符重载
};


template <class ElemType>
void DisplayBTWithTreeShape(BinTreeNode<ElemType> *r, int level);
	//	按树状形式显示以r为根的二叉树，level为层次数，可设根结点的层次数为1
template <class ElemType>
void DisplayBTWithTreeShape(BinaryTree<ElemType> &bt);
	//	树状形式显示二叉树 
template <class ElemType>
void CreateBinaryTree(BinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], 
	int preLeft, int preRight, int inLeft, int inRight);	
	// 已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造以r为根的
	// 二叉树
template <class ElemType>
BinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n);
	// 已知先序和中序序列构造二叉树



// 二叉树类的实现部分
template <class ElemType>
BinaryTree<ElemType>::BinaryTree()
// 操作结果：构造一个空二叉树
{
	root = NULL;
}

template <class ElemType>
BinaryTree<ElemType>::~BinaryTree()
// 操作结果：删除二叉树--析造函数
{
	Destroy(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::GetRoot() const
// 操作结果：返回二叉树的根
{
	return root;
}

template <class ElemType>
bool BinaryTree<ElemType>::IsEmpty() const
// 操作结果：判断二叉树是否为空
{
	return root == NULL;
}

template <class ElemType>
Status BinaryTree<ElemType>::GetElem(BinTreeNode<ElemType> *p, ElemType &e) const
// 操作结果：用e返回结点p元素值,如果不存在结点p,函数返回NOT_PRESENT,否则返回ENTRY_FOUND
{
	if (p == NULL)		// 不存在结点p
		return NOT_PRESENT;			// 返回NOT_PRESENT
	else	{	// 存在结点p
		e = p->data;				// 用e返回元素值
		return ENTRY_FOUND;			// 返回ENTRY_FOUND
	}
}

template <class ElemType>
Status BinaryTree<ElemType>::SetElem(BinTreeNode<ElemType> *p, const ElemType &e)
// 操作结果：如果不存在结点p,则返回FAIL,否则返回SUCCESS,并将结点p的值设置为e
{
	if (p == NULL)		// 不存在结点p
		return FAIL;				// 返回FAIL
	else	{	// 存在结点p
		p->data = e;				// 将结点p的值设置为e
		return SUCCESS;				// 返回SUCCESS
	}
}

template <class ElemType>
void BinaryTree<ElemType>::PreOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历以r为根的二叉树
{
	if (r != NULL)	{
		(*Visit)(r->data);				// 首先访问根结点r
		PreOrder(r->leftChild, Visit);	// 再遍历r的左子树
		PreOrder(r->rightChild, Visit);	// 最后遍历r的右子树
	}
}

template <class ElemType>
void BinaryTree<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历二叉树
{
	PreOrder(root, Visit);	
}	

template <class ElemType>
void BinaryTree<ElemType>::InOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历以r为根的二叉树
{
	if (r != NULL) 	{
		InOrder(r->leftChild, Visit);	// 首先遍历r的左子树
		(*Visit)(r->data);				// 再访问根结点r
		InOrder(r->rightChild, Visit);	// 最后遍历r的右子树
	}
}

template <class ElemType>
void BinaryTree<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历二叉树
{
	InOrder(root, Visit);	
}	

template <class ElemType>
void BinaryTree<ElemType>::PostOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历以r为根的二叉树
{
	if (r != NULL) 	{
		PostOrder(r->leftChild, Visit);	// 首先遍历r的左子树
		PostOrder(r->rightChild, Visit);// 再遍历r的右子树
		(*Visit)(r->data);				// 最后访问根结点r
	}
}

template <class ElemType>
void BinaryTree<ElemType>::PostOrder(void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历二叉树
{
	PostOrder(root, Visit);	
}	

template <class ElemType>
void BinaryTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历二叉树
{
	LinkQueue<BinTreeNode<ElemType> *> q;	// 定义队列q
	BinTreeNode<ElemType> *p;
	
	if (root != NULL) q.EnQueue(root);		// 如果根非空,则入队
	while (!q.IsEmpty())	{	            // q非空,说明还有结点未访问
		q.DelQueue(p);                      // 队头元素出队，并访问之 
		(*Visit)(p->data);
		if (p->leftChild != NULL)			// 队头元素左孩子非空
			q.EnQueue(p->leftChild);		// 左孩子入队
		if (p->rightChild != NULL)			// 队头元素右孩子非空
			q.EnQueue(p->rightChild);		// 右孩子入队
	}
}

template <class ElemType>
int BinaryTree<ElemType>::Height(const BinTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉树的高
{
	if(r == NULL)	// 空二叉树高为0
		return 0;
	else	{	// 非空二叉树高为左右子树的高的最大值再加1
		int lHeight, rHeight;
		lHeight = Height(r->leftChild);		// 左子树的高
		rHeight = Height(r->rightChild);	// 右子树的高
		return (lHeight > rHeight ? lHeight : rHeight) + 1;
			// 非空二叉树高为左右子树的高的最大值再加1
	}
}

template <class ElemType>
int BinaryTree<ElemType>::Height() const
// 操作结果：返回二叉树的高
{
	return Height(root);
}

template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const ElemType &e)
// 操作结果：建立以e为根的二叉树
{
	root = new BinTreeNode<ElemType>(e);
}

template <class ElemType>
int BinaryTree<ElemType>::NodeCount(const BinTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉树的结点个数
{
	if (r ==NULL)
       return 0;			// 空二叉树结点个数为0
	else
       return NodeCount(r->leftChild) + NodeCount(r->rightChild) + 1;
		// 非空二叉树结点个为左右子树的结点个数之和再加1
}

template <class ElemType>
int BinaryTree<ElemType>::NodeCount() const
// 操作结果：返回二叉树的结点个数
{
	return NodeCount(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::LeftChild(const BinTreeNode<ElemType> *p) const
// 操作结果：返回二叉树结点p的左孩子
{
	return p->leftChild;
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::RightChild(const BinTreeNode<ElemType> *p) const
// 操作结果：返回二叉树结点p的右孩子
{
	return p->rightChild;
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::LeftSibling(const BinTreeNode<ElemType> *p) const
// 操作结果：返回二叉树结点p的左兄弟 
{
    BinTreeNode<ElemType> *r = Parent(root, p);
    if (r == NULL)
       return NULL;
    else if (r->rightChild == p)
	   return r->leftChild;
    else 
       return NULL;
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::RightSibling(const BinTreeNode<ElemType> *p) const
// 操作结果：返回二叉树结点p的左兄弟
{
    BinTreeNode<ElemType> *r = Parent(root, p);
    if (r == NULL)
       return NULL;
    else if (r->leftChild == p)
	   return r->rightChild;
    else 
       return NULL;
}


template <class ElemType>
BinTreeNode<ElemType> * BinaryTree<ElemType>::Parent(BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *p) const
// 操作结果：返回以r为根的二叉树, 结点p的双亲
{
	if (r == NULL)
       return NULL;		// 空二叉树
	else if (r->leftChild == p || r->rightChild == p)
       return r; // r为p的双亲
	else	{	// 在子树上求双亲
		BinTreeNode<ElemType> *tmp;
		tmp = Parent(r->leftChild, p);	// 在左子树上求p的双亲	
		if (tmp != NULL)
           return tmp;			        // 双亲在左子树上
  
		tmp = Parent(r->rightChild, p);	// 在右子树上求p的双亲	
		if (tmp != NULL)
           return tmp;			        // 双亲在右子树上
		else
           return NULL;				    // 表示p无双亲
	}
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::Parent(const BinTreeNode<ElemType> *p) const
// 操作结果：返回二叉树结点p的双亲
{
	return Parent(root, p);
}

template <class ElemType>
void BinaryTree<ElemType>::InsertLeftChild(BinTreeNode<ElemType> *p, const ElemType &e)
// 初始条件：p非空，
// 操作结果：插入元素值为e的结点为p的左孩子，如果p的左孩子非空，则p原有左子树成为e的左子树
{
	if (p == NULL)	// p空，返回
		return;
	else 	{	// 插入左孩子
		BinTreeNode<ElemType> *child =  new BinTreeNode<ElemType>(e);// 元素值为e结点
		if (p->leftChild != NULL)	// p的左孩子非空
			child->leftChild = p->leftChild;	// p原有左子树成为e的左子树
		p->leftChild = child;					// e成为p的左孩子
		return;
	}
}

template <class ElemType>
void BinaryTree<ElemType>::InsertRightChild(BinTreeNode<ElemType> *p, const ElemType &e)
// 初始条件：p非空
// 操作结果：插入元素值为e的结点为p的右孩子，如果p的右孩子非空，则p原有右子树成为e的右子树
{
	if (p == NULL)	// p为空，返回
		return;
	else	{	// 插入右孩子
		BinTreeNode<ElemType> *child =  new BinTreeNode<ElemType>(e);// 元素值为e结点
		if (p->rightChild != NULL)	// p的右孩子非空
			child->rightChild = p->rightChild;	// p原有右子树成为e的右子树
		p->rightChild = child;					// e成为p的右孩子
		return;
	}
}

template <class ElemType>
void BinaryTree<ElemType>::DeleteLeftChild(BinTreeNode<ElemType> *p)
// 初始条件：p非空
// 操作结果：删除p左子树
{
	if (p == NULL)	// p为空
		return;
	else	// p非空
		Destroy(p->leftChild);	// 删除p左子树
}

template <class ElemType>
void BinaryTree<ElemType>::DeleteRightChild(BinTreeNode<ElemType> *p)
// 初始条件：p非空
// 操作结果：删除p右子树
{
	if (p == NULL)	// p为空
		return;
	else	// p非空
		Destroy(p->rightChild);	// 删除p右子树
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::Find(const ElemType &e) const
// 操作结果：返回二叉树结点p的双亲
{
	LinkQueue<BinTreeNode<ElemType> *> q;	// 定义队列q
	BinTreeNode<ElemType> *p;
	
	if (root != NULL) q.EnQueue(root);		// 如果根非空,则入队
	while (!q.IsEmpty())	{	            // q非空,说明还有结点未访问
		q.DelQueue(p);                      // 队头元素出队，并访问之 
		if (p->data == e)
			return p;
		if (p->leftChild != NULL)			// 队头元素左孩子非空
			q.EnQueue(p->leftChild);		// 左孩子入队
		if (p->rightChild != NULL)			// 队头元素右孩子非空
			q.EnQueue(p->rightChild);		// 右孩子入队
	}
	return NULL;
}


template <class ElemType>
void BinaryTree<ElemType>::Destroy(BinTreeNode<ElemType> *&r)
// 操作结果：删除以r的二叉树
{
	if(r != NULL)	{	// r非空,实施删除
		Destroy(r->leftChild);		// 删除左子树
		Destroy(r->rightChild);		// 删除右子树
		delete r;					// 删除根结点
		r = NULL;
	}
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::CopyTree(BinTreeNode<ElemType> *t)
// 操作结果：将以t为根的二叉树复制成新的二叉树,返回新二叉树的根
{
	if (t == NULL)	// 复制空二叉树
		return NULL;					// 空二叉树根为空	
	else	{	// 复制非空二叉树
		BinTreeNode<ElemType> *lChild = CopyTree(t->leftChild);	// 复制左子树
		BinTreeNode<ElemType> *rChild = CopyTree(t->rightChild);	// 复制右子树
		BinTreeNode<ElemType> *r = new BinTreeNode<ElemType>(t->data, lChild, rChild);
			// 复制根结点
		return r;
	}
}

template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const BinaryTree<ElemType> &t)
// 操作结果：由已知二叉树构造新二叉树——复制构造函数
{
	root = CopyTree(t.root);	// 复制二叉树
}

template <class ElemType>
BinaryTree<ElemType>::BinaryTree(BinTreeNode<ElemType> *r)
// 操作结果：建立以r为根的二叉树
{	
	root = r;	// 复制二叉树
}

template <class ElemType>
BinaryTree<ElemType> &BinaryTree<ElemType>::operator=(const BinaryTree<ElemType> &t)
// 操作结果：由已知二叉树t复制到当前二叉树--赋值运算符重载
{
	if (&t != this)	{
		Destroy(root);				// 释放原二叉树所占用空间
		root = CopyTree(t.root);	// 复制二叉树
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShape(BinTreeNode<ElemType> *r, int level)
// 操作结果：按树状形式显示以r为根的二叉树，level为层次数，可设根结点的层次数为1
{
	if(r != NULL)	{	// 空树不显式，只显式非空树
		DisplayBTWithTreeShape<ElemType>(r->rightChild, level + 1);//显示右子树
		cout << endl;					//显示新行	
		for(int i = 0; i < level - 1; i++)
			cout << "  ";				//确保在第level列显示结点
		cout << r->data;				//显示结点
		DisplayBTWithTreeShape<ElemType>(r->leftChild, level + 1);//显示左子树
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(BinaryTree<ElemType> &bt)
// 操作结果：树状形式显示二叉树 
{
	DisplayBTWithTreeShape<ElemType>(bt.GetRoot(), 1);	
		// 树状显示以bt.GetRoot()为根的二叉树
	cout << endl;
}

template <class ElemType>
void CreateBinaryTree(BinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], 
							int preLeft, int preRight, int inLeft, int inRight)	
// 操作结果：已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造
//	以r为根的二叉树
{
	if (inLeft > inRight)	// 二叉树无结点,空二叉树
		r = NULL;			// 空二叉树根为空
	else	{	// 二叉树有结点,非空二叉树
		r = new BinTreeNode<ElemType>(pre[preLeft]);// 生成根结点
		int mid = inLeft;
		while (in[mid] != pre[preLeft]) 	// 查找pre[preLeft]在in[]中的位置,也就是中序序列中根的位置
			mid++;
		CreateBinaryTree(r->leftChild, pre, in, preLeft+1, preLeft + mid - inLeft, inLeft, mid - 1);
			// 生成左子树
		CreateBinaryTree(r->rightChild, pre, in, preLeft + mid - inLeft + 1, preRight, mid + 1, 
			inRight);								// 生成右子树
	}
} 

template <class ElemType>
BinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n)
// 操作结果：已知先序和中序序列构造二叉树
{
	BinTreeNode<ElemType> *r;						// 二叉树的根
	CreateBinaryTree<ElemType>(r, pre, in, 0, n - 1, 0, n - 1);
		// 由先序和中序序列构造以r为根的二叉树 
	BinaryTree<ElemType> *bt = new BinaryTree<ElemType>(r);	// 生成二叉树
	return *bt;
}

#endif
