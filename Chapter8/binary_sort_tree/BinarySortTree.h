#ifndef __BINNARY_TREE_H__
#define __BINNARY_TREE_H__

#include "LinkQueue.h"				// 链队列
#include "BinTreeNode.h"			// 二叉树结点类

// 二叉排序树类
template <class ElemType>
class BinarySortTree
{
protected:
//  二叉排序树的数据成员:
	BinTreeNode<ElemType> *root;

//	辅助函数:
	BinTreeNode<ElemType> *CopyTree(BinTreeNode<ElemType> *r);	// 复制以r为根的二叉排序树
	void Destroy(BinTreeNode<ElemType> * &r);					// 销毁以r为根的二叉排序树
	void PreOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// 先序遍历以r为根的二叉排序树
	void InOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// 中序遍历以r为根的二叉排序树
	void PostOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;// 后序遍历以r为根的二叉排序树
    int Height(const BinTreeNode<ElemType> *r) const;	// 求以r为根的二叉排序树的高
	int NodeCount(const BinTreeNode<ElemType> *r) const;// 求以r为根的二叉排序树的结点数
	BinTreeNode<ElemType> *Parent(BinTreeNode<ElemType> *r, 
		const BinTreeNode<ElemType> *p) const;			// 在以r为根的二叉排序树中求p的双亲
	BinTreeNode<ElemType> *Find(const ElemType &key, BinTreeNode<ElemType> *&f) const;	
		// 查找关键字为key的数据元素
	void Delete(BinTreeNode<ElemType> *&p);				// 删除p指向的结点

public:
//  二叉排序树方法声明及重载编译系统默认方法声明:
	BinarySortTree();									// 无参数的构造函数
	virtual ~BinarySortTree();							// 析构函数
	BinTreeNode<ElemType> *GetRoot() const;				// 求二叉排序树的根
	bool IsEmpty() const;								// 判断二叉排序树是否为空
	Status GetElem(BinTreeNode<ElemType> *p, ElemType &e) const;
		// 用e返回结点数据元素值
	Status SetElem(BinTreeNode<ElemType> *p, const ElemType &e);
		// 将结p的值置为e
	void InOrder(void (*Visit)(const ElemType &)) const;	// 二叉排序树的中序遍历	
	void PreOrder(void (*Visit)(const ElemType &)) const;	// 二叉排序树的先序遍历
	void PostOrder(void (*Visit)(const ElemType &)) const;	// 二叉排序树的后序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;	// 二叉排序树的层次遍历
	int NodeCount() const;									// 求二叉排序树的结点个数
	BinTreeNode<ElemType> *Find(const ElemType &key) const;  // 查找关键字为key的数据元素
	bool Insert(const ElemType &e);							// 插入数据元素e
	bool Delete(const ElemType &key);						// 删除关键字为key的数据元素
	BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> *p) const;
		// 求二叉排序树结点p的左孩子
	BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> *p) const;
		// 求二叉排序树结点p的右孩子
	BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> *p) const;
		// 求二叉排序树结点p的双亲
	int	Height() const;										// 求二叉排序树的高
	BinarySortTree(const ElemType &e);						// 建立以e为根的二叉排序树
	BinarySortTree(const BinarySortTree<ElemType> &copy);	// 复制构造函数
	BinarySortTree(BinTreeNode<ElemType> *r);				// 建立以r为根的二叉排序树
	BinarySortTree<ElemType> &operator=
		(const BinarySortTree<ElemType>& copy);	// 赋值语句重载
};

template <class ElemType>
void DisplayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level);
	//	按树状形式显示以r为根的二叉排序树，level为层次数，可设根结点的层次数为1
template <class ElemType>
void DisplayBTWithTreeShape(const BinarySortTree<ElemType> &bt);
	//	树状形式显示二叉排序树bt 

// 二叉排序树类的实现部分
template <class ElemType>
BinarySortTree<ElemType>::BinarySortTree()
// 操作结果：构造一个空二叉排序树
{
	root = NULL;
}

template <class ElemType>
BinarySortTree<ElemType>::~BinarySortTree()
// 操作结果：销毁二叉排序树--析造函数
{
	Destroy(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinarySortTree<ElemType>::GetRoot() const
// 操作结果：返回二叉排序树的根
{
	return root;
}

template <class ElemType>
bool BinarySortTree<ElemType>::IsEmpty() const
// 操作结果：判断二叉排序树是否为空
{
	return root == NULL;
}

template <class ElemType>
Status BinarySortTree<ElemType>::GetElem(BinTreeNode<ElemType> *p, ElemType &e) const
// 操作结果：用e返回结点p的数据元素值,如果不存在结点p,函数返回NOT_PRESENT,否则返回ENTRY_FOUND
{
	if (p == NULL)		
		return NOT_PRESENT;	// 不存在结点p，返回NOT_PRESENT
	else  { 
		e = p->data;		// 存在结点p，用e返回数据元素值
		return ENTRY_FOUND;	// 返回ENTRY_FOUND
	}
}

template <class ElemType>
Status BinarySortTree<ElemType>::SetElem(BinTreeNode<ElemType> *p, const ElemType &e)
// 操作结果：如果不存在结点p,则返回FAIL,否则返回SUCCESS,并将结点p的值设置为e
{
	if (p == NULL)
		return FAIL;		// 不存在结点p，返回FAIL
	else	{
		p->data = e;				// 存在结点p将结点p的值设置为e
		return SUCCESS;				// 返回SUCCESS
	}
}

template <class ElemType>
void BinarySortTree<ElemType>::PreOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历以r为根的二叉排序树
{
	if (r != NULL) 	{
		(*Visit)(r->data);				// 访问根结点
		PreOrder(r->leftChild, Visit);	// 先序遍历r的左子树
		PreOrder(r->rightChild, Visit);	// 先序遍历r的右子树
	}
}

template <class ElemType>
void BinarySortTree<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历二叉排序树
{
	PreOrder(root, Visit);	
}	

template <class ElemType>
void BinarySortTree<ElemType>::InOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历以r为根的二叉排序树
{
	if (r != NULL) 	{
		InOrder(r->leftChild, Visit);	// 中序遍历r的左子树
		(*Visit)(r->data);				// 访问根结点
		InOrder(r->rightChild, Visit);	// 中序遍历r的右子树
	}
}

template <class ElemType>
void BinarySortTree<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历二叉排序树
{
	InOrder(root, Visit);	
}	

template <class ElemType>
void BinarySortTree<ElemType>::PostOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历以r为根的二叉排序树
{
	if (r != NULL) 	{
		PostOrder(r->leftChild, Visit);	// 后序遍历r的左子树
		PostOrder(r->rightChild, Visit);// 后序遍历r的右子树
		(*Visit)(r->data);				// 访问根结点
	}
}

template <class ElemType>
void BinarySortTree<ElemType>::PostOrder(void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历二叉排序树
{
	PostOrder(root, Visit);	
}	

template <class ElemType>
void BinarySortTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历二叉排序树
{
	LinkQueue<BinTreeNode<ElemType> *> q;	// 队列
	BinTreeNode<ElemType> *t = root;
	
	if (t != NULL) 
        q.EnQueue(t);			// 如果根非空,则入队
	while (!q.IsEmpty())	{	// q非空,说明还有结点未访问
		q.DelQueue(t);     
		(*Visit)(t->data);
		if (t->leftChild != NULL)			// 左孩子非空
			q.EnQueue(t->leftChild);		// 左孩子入队
		if (t->rightChild != NULL)			// 右孩子非空
			q.EnQueue(t->rightChild);		// 右孩子入队
	}
}

template <class ElemType>
int BinarySortTree<ElemType>::Height(const BinTreeNode<ElemType> *r) const
// 操作结果：求以r为根的二叉排序树的高
{
	if(r == NULL)	// 空二叉排序树高为0
		return 0;
	else	{	    // 非空二叉排序树高为左右子树的高的最大值再加1
		int lHeight, rHeight;
		lHeight = Height(r->leftChild);		// 左子树的高
		rHeight = Height(r->rightChild);	// 右子树的高
		return 1 + (lHeight > rHeight ? lHeight : rHeight);
			// 非空二叉排序树高为左右子树的高的最大值再加1
	}
}

template <class ElemType>
int BinarySortTree<ElemType>::Height() const
// 操作结果：求二叉排序树的高
{
	return Height(root);
}

template <class ElemType>
BinarySortTree<ElemType>::BinarySortTree(const ElemType &e)
// 操作结果：建立以e为根的二叉排序树
{
	root = new BinTreeNode<ElemType>(e);
}

template <class ElemType>
int BinarySortTree<ElemType>::NodeCount(const BinTreeNode<ElemType> *r) const
// 操作结果：求以r为根的二叉排序树的结点个数
{
	if (r ==NULL) 
        return 0;			// 空二叉排序树结点个数为0
	else 
        return 1 + NodeCount(r->leftChild) + NodeCount(r->rightChild);
		// 非空二叉排序树结点个为左右子树的结点个数之和再加1
}

template <class ElemType>
int BinarySortTree<ElemType>::NodeCount() const
// 操作结果：求二叉排序树的结点个数
{
	return NodeCount(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinarySortTree<ElemType>::LeftChild(const BinTreeNode<ElemType> *p) const
// 操作结果：求二叉排序树结点p的左孩子
{
	return p->leftChild;
}

template <class ElemType>
BinTreeNode<ElemType> *BinarySortTree<ElemType>::RightChild(const BinTreeNode<ElemType> *p) const
// 操作结果：求二叉排序树结点p的右孩子
{
	return p->rightChild;
}

template <class ElemType>
BinTreeNode<ElemType> * BinarySortTree<ElemType>::Parent(BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *p) const
// 操作结果： 在以r为根的二叉排序树中求结点p的双亲
{
	if (r == NULL) 
        return NULL;		// 空二叉排序树
	else if (r->leftChild == p || r->rightChild == p) 
        return r; // r为p的双亲
	else	{	// 在子树上求双亲
		BinTreeNode<ElemType> *tmp;
		
		tmp = Parent(r->leftChild, p); // 在左子树上求p的双亲	
		if (tmp != NULL)
           return tmp;	               // 双亲在左子树上

		tmp = Parent(r->rightChild, p);// 在右子树上求p的双亲	
		if (tmp != NULL) 
           return tmp;	               // 双亲在右子树上
		else 
           return NULL;				   // 表示p无双亲
	}
}

template <class ElemType>
BinTreeNode<ElemType> *BinarySortTree<ElemType>::Parent(const BinTreeNode<ElemType> *p) const
// 操作结果：求二叉排序树结点p的双亲
{
	return Parent(root, p);
}

template <class ElemType>
BinTreeNode<ElemType> *BinarySortTree<ElemType>::Find(const ElemType &key, 
	BinTreeNode<ElemType> *&f) const
// 操作结果: 求指向关键字为key的数据元素的指针,用f返回其双亲
{
	BinTreeNode< ElemType> *p = GetRoot();	// 指向当前结点
	f = NULL;								// 指向p的双亲
	
	while (p != NULL && p->data != key)	{	// 查找关键字为key的结点
		if (key < p->data)	{	// key更小,在左子树上进行查找
	        cout << "比" << p->data << "小" << endl;
			f = p;
			p = p->leftChild;
		}
		else		{	// key更大,在右子树上进行查找
	        cout << "比" << p->data << "大" << endl;
			f = p;
			p = p->rightChild;
		}
	}
	return p;
}

template <class ElemType>
BinTreeNode<ElemType> *BinarySortTree<ElemType>::Find(const ElemType &key)	const 
// 操作结果: 返回指向关键字为key的数据元素的指针
{
	BinTreeNode<ElemType> *f;			// 指向被查找结点的双亲
	return Find(key, f);
}

template <class ElemType>
bool BinarySortTree<ElemType>::Insert(const ElemType &e)
// 操作结果: 插入数据元素e
{
	BinTreeNode<ElemType> *f;		// 指向被查找结点的双亲

	cout << "插入数据元素" << e <<"的搜索过程：" << endl;
	if (Find(e, f) == NULL)	{	    // 查找失败, 插入成功
		BinTreeNode<ElemType> *p;	// 插入的新结点
		p = new BinTreeNode<ElemType>(e);
		if (IsEmpty())	            // 空二叉树,新结点为根结点
			root = p;
		else if (e < f->data)	    // e小于其双亲,插入结点为f的左孩子
			f->leftChild = p;
		else	                    // e大于其双亲,插入结点为f的右孩子
			f->rightChild = p;
		return true;		
	}
	else	// 查找成功, 插入失败
		return false;
}

template <class ElemType>
void BinarySortTree<ElemType>::Delete(BinTreeNode<ElemType> *&p)
// 操作结果: 删除p指向的结点
{
	BinTreeNode<ElemType> *tmpPtr, *tmpF;  
	if (p->leftChild == NULL && p->rightChild == NULL)	{	// p为叶结点
		delete p;
		p = NULL;
	}
	else if (p->leftChild == NULL)	{	// p只有左子树为空
		tmpPtr = p;
		p = p->rightChild;
		delete tmpPtr;
	}
	else if (p->rightChild == NULL)	{	// p只有右子树非空
		tmpPtr = p;
		p = p->leftChild;
		delete tmpPtr;
	}
	else	{	// p左右子非空
		tmpF = p;
		tmpPtr = p->leftChild;
		while (tmpPtr->rightChild != NULL)	{	// 查找p在中序序列中直接前驱tmpPtr及其双亲tmpF,直到tmpPtr右子树为空
			tmpF = tmpPtr;
			tmpPtr = tmpPtr->rightChild;
		}
		p->data = tmpPtr->data;
			// 将tmpPtr指向结点的数据元素值赋值给tmpF指向结点的数据元素值

		// 删除tmpPtr指向的结点
		if (tmpF->rightChild == tmpPtr)	// 删除tmpF的右孩子
			Delete(tmpF->rightChild);
		else    // 删除tmpF的左孩子
			Delete(tmpF->leftChild);
	}
}

template <class ElemType>
bool BinarySortTree<ElemType>::Delete(const ElemType &key)
// 操作结果: 删除关键字为key的数据元素
{
	BinTreeNode<ElemType> *p, *f;
	p = Find(key, f);
	if ( p == NULL)	// 查找失败, 删除失败
		return false;
	else	// 查找成功, 插入失败
		if (f == NULL)	// 被删除结点为根结点
			Delete(p);
		else if (key < f->data)	// elem.key更小,删除f的左孩子
			Delete(f->leftChild);
		else	// elem.key更大, 删除f的右孩子
			Delete(f->rightChild);
		return true;		
}

template <class ElemType>
void BinarySortTree<ElemType>::Destroy(BinTreeNode<ElemType> *&r)
// 操作结果：销毁以r的二叉排序树
{
	if(r != NULL)	{	// r非空,实施销毁
		Destroy(r->leftChild);		// 销毁左子树
		Destroy(r->rightChild);		// 销毁右子树
		delete r;						// 销毁根结点
		r = NULL;
	}
}

template <class ElemType>
BinTreeNode<ElemType> *BinarySortTree<ElemType>::CopyTree(BinTreeNode<ElemType> *copy)
// 操作结果：将以copy为根的二叉排序树复制成新的二叉排序树,返回新二叉排序树的根
{
	if (copy == NULL)	// 复制空二叉排序树
		return NULL;					// 空二叉排序树根为空	
	else	{	// 复制非空二叉排序树
		BinTreeNode<ElemType> *lChild = CopyTree(copy->leftChild);	// 复制左子树
		BinTreeNode<ElemType> *rChild = CopyTree(copy->rightChild);	// 复制右子树
		BinTreeNode<ElemType> *r = new BinTreeNode<ElemType>(copy->data, lChild, rChild);
			// 复制根结点
		return r;
	}
}

template <class ElemType>
BinarySortTree<ElemType>::BinarySortTree(const BinarySortTree<ElemType> &copy)
// 操作结果：由已知二叉排序树构造新二叉排序树——复制构造函数
{
	root = CopyTree(copy.root);	// 复制二叉排序树
}

template <class ElemType>
BinarySortTree<ElemType>::BinarySortTree(BinTreeNode<ElemType> *r)
// 操作结果：建立以r为根的二叉排序树
{	
	root = r;	// 复制二叉排序树
}

template <class ElemType>
BinarySortTree<ElemType> &BinarySortTree<ElemType>::operator=(const BinarySortTree<ElemType> &copy)
// 操作结果：由已知二叉排序树copy复制到当前二叉排序树--赋值语句重载
{
	if (&copy != this)	{
		Destroy(root);				// 释放原二叉排序树所占用空间
		root = CopyTree(copy.root);	// 复制二叉排序树
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level)
//	操作结果：按树状形式显示以r为根的二叉排序树，level为层次数，可设根结点的层次数为1
{
	if(r != NULL)	{	//空树不显式，只显式非空树
		DisplayBTWithTreeShapeHelp<ElemType>(r->rightChild, level + 1);//显示右子树
		cout << endl << endl;					//显示新行	
		for(int i = 0; i < level - 1; i++)
			cout << "   ";				//确保在第level列显示结点
		cout << r->data;				//显示结点
		DisplayBTWithTreeShapeHelp<ElemType>(r->leftChild, level + 1);//显示左子树
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(const BinarySortTree<ElemType> &bt)
//	操作结果：树状形式显示二叉排序树 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);	
		// 树状显示以bt.GetRoot()为根的二叉排序树
	cout << endl;
}

#endif
