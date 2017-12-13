#ifndef __BINNARY_TREE_H__
#define __BINNARY_TREE_H__
#include "Assistance.h"				// 辅助软件包
#include "LinkQueue.h"				// 链队列
#include "LinkStack.h"				// 链栈
#include "BinAvlTreeNode.h"			// 平衡二叉树结点类

// 平衡二叉树类
template <class ElemType>
class BinaryAVLTree
{
protected:
//  平衡二叉树的数据成员:
	BinAVLTreeNode<ElemType> *root;

//	辅助函数:
	BinAVLTreeNode<ElemType> *CopyTreeHelp(BinAVLTreeNode<ElemType> *copy);	// 复制平衡二叉树
	void DestroyHelp(BinAVLTreeNode<ElemType> * &r);						// 销毁以r为根的平衡二叉树
	void PreOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// 先序遍历以r为根的平衡二叉树
	void InOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// 中序遍历以r为根的平衡二叉树
	void PostOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// 后序遍历以r为根的平衡二叉树
    int HeightHelp(const BinAVLTreeNode<ElemType> *r) const;				// 求以r为根的平衡二叉树的高
	int NodeCountHelp(const BinAVLTreeNode<ElemType> *r) const;				// 求以r为根的平衡二叉树的结点个数
	BinAVLTreeNode<ElemType> *ParentHelp(BinAVLTreeNode<ElemType> *r, 
		const BinAVLTreeNode<ElemType> *p) const;							// 在以r为根的平衡二叉树中求p的双亲
	BinAVLTreeNode<ElemType> *Find(const ElemType &key, BinAVLTreeNode<ElemType> *&f) const;	
		// 查找关键字为key的数据元素,返回指向关键字为key的元素的指针,用f返回其双亲. 

	BinAVLTreeNode<ElemType> *Find(const ElemType &key, BinAVLTreeNode<ElemType> *&f,
		LinkStack<BinAVLTreeNode<ElemType> *> &s);
		 // 查找关键字为key的数据元素,返回指向关键字为key的元素的指针,并用f返回其双亲,栈s存储查找路径.
		 
	BinAVLTreeNode<ElemType> *Find(const ElemType &key, BinAVLTreeNode<ElemType> *&f,
		BinAVLTreeNode<ElemType> *&a, BinAVLTreeNode<ElemType> *&af);
		 // 查找关键字为key的数据元素,返回指向关键字为key的元素的指针,并用f返回其双亲,a为离插入结点最近的平衡因子不等于0的结点,af是a的双亲. 
		 
	void LeftRotate(BinAVLTreeNode<ElemType> *&subRoot);
		// 对以subRoot为根的二叉树作左旋处理,处理之后subRoot指向新的树根结点,也就是旋转处理前的右子树的根结点
	void RightRotate(BinAVLTreeNode<ElemType> *&subRoot);
		// 对以subRoot为根的二叉树作右旋处理,处理之后subRoot指向新的树根结点,也就是旋转处理前的左子树的根结点
	void DeleteLeftBalance(BinAVLTreeNode<ElemType> *&subRoot, bool &isShorter);
		// 对以subRoot为根的二叉树删除时作左平衡处理,处理后subRoot指向新的树根结点
	void DeleteRightBalance(BinAVLTreeNode<ElemType> *&subRoot, bool &isShorter);
		// 对以subRoot为根的二叉树删除时作右平衡处理,处理后subRoot指向新的树根结点
	void DeleteBalance(const ElemType &key, LinkStack<BinAVLTreeNode<ElemType> *> &s);
		// 从删除结点根据查找路径进行回溯,并作平衡处理
	void DeleteHelp(const ElemType &key, BinAVLTreeNode<ElemType> *&p,
		LinkStack< BinAVLTreeNode<ElemType> *> &s);		// 删除p指向的结点

public:
//  平衡二叉树方法声明及重载编译系统默认方法声明:
	BinaryAVLTree();											// 无参数的构造函数
	virtual ~BinaryAVLTree();									// 析构函数
	BinAVLTreeNode<ElemType> *GetRoot() const;					// 返回平衡二叉树的根
	bool IsEmpty() const;										// 判断平衡二叉树是否为空
	Status GetElem(BinAVLTreeNode<ElemType> *p, ElemType &e) const;
		// 用e返回结点数据元素值
	Status SetElem(BinAVLTreeNode<ElemType> *p, const ElemType &e);
		// 将结p的值置为e
	void InOrder(void (*Visit)(const ElemType &)) const;		// 平衡二叉树的中序遍历	
	void PreOrder(void (*Visit)(const ElemType &)) const;		// 平衡二叉树的先序遍历
	void PostOrder(void (*Visit)(const ElemType &)) const;		// 平衡二叉树的后序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;		// 平衡二叉树的层次遍历
	int NodeCount() const;										// 求平衡二叉树的结点个数
	BinAVLTreeNode<ElemType> *Find(const ElemType &key) const;	// 查找关键字为key的数据元素
	bool Insert(const ElemType &e);								// 插入数据元素e
	bool Delete(const ElemType &key);							// 删除关键字为key的数据元素
	BinAVLTreeNode<ElemType> *LeftChild(const BinAVLTreeNode<ElemType> *p) const;
		// 返回平衡二叉树结点p的左孩子
	BinAVLTreeNode<ElemType> *RightChild(const BinAVLTreeNode<ElemType> *p) const;
		// 返回平衡二叉树结点p的右孩子
	BinAVLTreeNode<ElemType> *Parent(const BinAVLTreeNode<ElemType> *p) const;
		// 返回平衡二叉树结点p的双亲
	int	Height() const;											// 求平衡二叉树的高
	BinaryAVLTree(const ElemType &e);							// 建立以e为根的平衡二叉树
	BinaryAVLTree(const BinaryAVLTree<ElemType> &copy);			// 复制构造函数
	BinaryAVLTree(BinAVLTreeNode<ElemType> *r);					// 建立以r为根的平衡二叉树
	BinaryAVLTree<ElemType> &operator=(const BinaryAVLTree<ElemType>& copy);	// 赋值语句重载
};

template <class ElemType>
void DisplayBTWithTreeShapeHelp(const BinAVLTreeNode<ElemType> *r, int level);
	//	按树状形式显示以r为根的平衡二叉树，level为层次数，可设根结点的层次数为1
template <class ElemType>
void DisplayBTWithTreeShape(const BinaryAVLTree<ElemType> &bt);
	//	树状形式显示二叉平衡树bt 

// 平衡二叉树类的实现部分
template <class ElemType>
BinaryAVLTree<ElemType>::BinaryAVLTree()
// 操作结果：构造一个空平衡二叉树
{
	root = NULL;
}

template <class ElemType>
BinaryAVLTree<ElemType>::~BinaryAVLTree()
// 操作结果：销毁平衡二叉树--析造函数
{
	DestroyHelp(root);
}

template <class ElemType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType>::GetRoot() const
// 操作结果：返回平衡二叉树的根
{
	return root;
}

template <class ElemType>
bool BinaryAVLTree<ElemType>::IsEmpty() const
// 操作结果：判断平衡二叉树是否为空
{
	return root == NULL;
}

template <class ElemType>
Status BinaryAVLTree<ElemType>::GetElem(BinAVLTreeNode<ElemType> *p, ElemType &e) const
// 操作结果：用e返回结点p数据元素值,如果不存在结点p,函数返回NOT_PRESENT,否则返回ENTRY_FOUND
{
	if (p == NULL)	// 不存在结点p
		return NOT_PRESENT;			// 返回NOT_PRESENT
	else	{	    // 存在结点p
		e = p->data;				// 用e返回数据元素值
		return ENTRY_FOUND;			// 返回ENTRY_FOUND
	}
}

template <class ElemType>
Status BinaryAVLTree<ElemType>::SetElem(BinAVLTreeNode<ElemType> *p, const ElemType &e)
// 操作结果：如果不存在结点p,则返回FAIL,否则返回SUCCESS,并将结点p的值设置为e
{
	if (p == NULL)		   // 不存在结点p
		return FAIL;	   // 返回FAIL
	else	{	           // 存在结点p
		p->data = e;	   // 将结点p的值设置为e
		return SUCCESS;	   // 返回SUCCESS
	}
}

template <class ElemType>
void BinaryAVLTree<ElemType>::PreOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历以r为根的平衡二叉树
{
	if (r != NULL) 	{
		(*Visit)(r->data);					// 访问根结点
		PreOrderHelp(r->leftChild, Visit);	// 先序遍历r的左子树
		PreOrderHelp(r->rightChild, Visit);	// 先序遍历r的右子树
	}
}

template <class ElemType>
void BinaryAVLTree<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历平衡二叉树
{
	PreOrderHelp(root, Visit);	
}	

template <class ElemType>
void BinaryAVLTree<ElemType>::InOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历以r为根的平衡二叉树
{
	if (r != NULL) 	{
		InOrderHelp(r->leftChild, Visit);	// 中序遍历r的左子树
		(*Visit)(r->data);					// 访问根结点
		InOrderHelp(r->rightChild, Visit);	// 中序遍历r的右子树
	}
}

template <class ElemType>
void BinaryAVLTree<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历平衡二叉树
{
	InOrderHelp(root, Visit);	
}	

template <class ElemType>
void BinaryAVLTree<ElemType>::PostOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历以r为根的平衡二叉树
{
	if (r != NULL) 	{
		PostOrderHelp(r->leftChild, Visit);	// 后序遍历r的左子树
		PostOrderHelp(r->rightChild, Visit);// 后序遍历r的右子树
		(*Visit)(r->data);					// 访问根结点
	}
}

template <class ElemType>
void BinaryAVLTree<ElemType>::PostOrder(void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历平衡二叉树
{
	PostOrderHelp(root, Visit);	
}	

template <class ElemType>
void BinaryAVLTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历平衡二叉树
{
	LinkQueue<BinAVLTreeNode<ElemType> *> q;// 队列
	BinAVLTreeNode<ElemType> *t = root;		// 从根结点开始进行层次遍历
	
	if (t != NULL) q.EnQueue(t);			// 如果根非空,则入队
	while (!q.IsEmpty())	{	            // q非空,说明还有结点未访问
		q.DelQueue(t);     
		(*Visit)(t->data);
		if (t->leftChild != NULL)			// 左孩子非空
			q.EnQueue(t->leftChild);		// 左孩子入队
		if (t->rightChild != NULL)			// 右孩子非空
			q.EnQueue(t->rightChild);		// 右孩子入队
	}
}

template <class ElemType>
int BinaryAVLTree<ElemType>::HeightHelp(const BinAVLTreeNode<ElemType> *r) const
// 操作结果：求以r为根的平衡二叉树的高
{
	if(r == NULL)	// 空平衡二叉树高为0
		return 0;
	else	{	    // 非空平衡二叉树高为左右子树的高的最大值再加1
		int lHeight, rHeight;
		lHeight = HeightHelp(r->leftChild);		// 左子树的高
		rHeight = HeightHelp(r->rightChild);	// 右子树的高
		return 1 + (lHeight > rHeight ? lHeight : rHeight);
			// 非空平衡二叉树高为左右子树的高的最大值再加1
	}
}

template <class ElemType>
int BinaryAVLTree<ElemType>::Height() const
// 操作结果：求平衡二叉树的高
{
	return HeightHelp(root);
}

template <class ElemType>
BinaryAVLTree<ElemType>::BinaryAVLTree(const ElemType &e)
// 操作结果：建立以e为根的平衡二叉树
{
	root = new BinAVLTreeNode<ElemType>(e);
}

template <class ElemType>
int BinaryAVLTree<ElemType>::NodeCountHelp(const BinAVLTreeNode<ElemType> *r) const
// 操作结果：求以r为根的平衡二叉树的结点个数
{
	if (r ==NULL) 
       return 0;	// 空平衡二叉树结点个数为0
	else 
       return 1 + NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild);
		// 非空平衡二叉树结点个为左右子树的结点个数之和再加1
}

template <class ElemType>
int BinaryAVLTree<ElemType>::NodeCount() const
// 操作结果：求平衡二叉树的结点个数
{
	return NodeCountHelp(root);
}

template <class ElemType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType>::LeftChild(const BinAVLTreeNode<ElemType> *p) const
// 操作结果：返回平衡二叉树结点p的左孩子
{
	return p->leftChild;
}

template <class ElemType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType>::RightChild(const BinAVLTreeNode<ElemType> *p) const
// 操作结果：返回平衡二叉树结点p的右孩子
{
	return p->rightChild;
}

template <class ElemType>
BinAVLTreeNode<ElemType> * BinaryAVLTree<ElemType>::ParentHelp(BinAVLTreeNode<ElemType> *r, const BinAVLTreeNode<ElemType> *p) const
// 操作结果：在以r为根的平衡二叉树中求结点p的双亲
{
	if (r == NULL) 
       return NULL;		// 空平衡二叉树
	else if (r->leftChild == p || r->rightChild == p) 
       return r;        // r为p的双亲
	else	{	        // 在子树上求双亲
		BinAVLTreeNode<ElemType> *tmp;
		
		tmp = ParentHelp(r->leftChild, p);	// 在左子树上求p的双亲	
		if (tmp != NULL) 
           return tmp;		                // 双亲在左子树上

		tmp = ParentHelp(r->rightChild, p);	// 在右子树上求p的双亲	
		if (tmp != NULL) 
           return tmp;			            // 双亲在右子树上
		else 
           return NULL;						// 表示p无双亲
	}
}

template <class ElemType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType>::Parent(const BinAVLTreeNode<ElemType> *p) const
// 操作结果：返回平衡二叉树结点p的双亲
{
	return ParentHelp(root, p);
}

template <class ElemType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType>::Find(const ElemType &key, BinAVLTreeNode<ElemType> *&f) const
// 操作结果: 返回指向关键字为key的数据元素的指针,并用f返回其双亲
{
	BinAVLTreeNode< ElemType> *p = GetRoot(); // 指向当前结点
	f = NULL;								  // 指向p的双亲
	
	while (p != NULL && p->data != key)	{	  // 查找关键字为key的结点
		if (key < p->data)		{	          // key更小,在左子树上进行查找
			f = p;
			p = p->leftChild;
		}
		else		{	                      // key更大,在右子树上进行查找
			f = p;
			p = p->rightChild;
		}
	}
	
	return p;
}

template <class ElemType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType>::Find(const ElemType &key)	const 
// 操作结果: 返回指向关键字为key的数据元素的指针
{
	BinAVLTreeNode<ElemType> *f;			// 指向被查找结点的双亲
	return Find(key, f);
}

template <class ElemType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType>::Find(
	const ElemType &key,	BinAVLTreeNode<ElemType> *&f,
	LinkStack<BinAVLTreeNode<ElemType> *> &s) 
// 查找关键字为key的数据元素,返回指向关键字为key的元素的指针,并用f返回其双亲,栈s存储查找路径.
{
	BinAVLTreeNode<ElemType> *p = GetRoot();// 指向当前结点
	f = NULL;		                        // 指向p的双亲
	s.Clear();
	while (p != NULL && p->data != key)	{	// 查寻关键字为key的结点
		if (key < p->data)	{	            // key更小,在左子树上进行查找
			f = p;
			s.Push(p);
			p = p->leftChild;
		}
		else	{	// key更大,在右子树上进行查找
			f = p;
			s.Push(p);
			p = p->rightChild;
		}
	}
	return p;
}

template <class ElemType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType>::Find(
	const ElemType &key,	BinAVLTreeNode<ElemType> *&f,
	BinAVLTreeNode<ElemType> *&a, BinAVLTreeNode<ElemType> *&af) 
// 查找关键字为key的数据元素,返回指向关键字为key的元素的指针,并用f返回其双亲,a为离插入结点最近的平衡因子不等于0的结点,af是a的双亲. 
{
	BinAVLTreeNode<ElemType> *p = GetRoot();// 指向当前结点
	a = af = f = NULL;		                        // 指向p的双亲
	while (p != NULL && p->data != key)	{	// 查寻关键字为key的结点
		if (p->bf != EH) {
            af = f;
		    a = p;
        }    
		if (key < p->data)	{	            // key更小,在左子树上进行查找
			f = p;
			p = p->leftChild;
		}
		else	{	// key更大,在右子树上进行查找
			f = p;
			p = p->rightChild;
		}
	}
	if (a == NULL)
	   a = GetRoot();
	return p;
}

template <class ElemType>
void BinaryAVLTree<ElemType>::LeftRotate(BinAVLTreeNode<ElemType> *&subRoot)
// 操作结果: 对以subRoot为根的二叉树作左旋处理,处理之后subRoot指向新的树根结点,
//	也就是旋转处理前的右子树的根结点
{
	BinAVLTreeNode<ElemType> *ptrRChild;
	ptrRChild = subRoot->rightChild;			// ptrRChild指向subRoot右孩子
	subRoot->rightChild = ptrRChild->leftChild;	// ptrRChild的左子树链接为subRoot的右子树
	ptrRChild->leftChild = subRoot;				// subRoot链接为ptrRChild的左孩子
	subRoot = ptrRChild;						// subRoot指向新的根结点
}

template <class ElemType>
void BinaryAVLTree<ElemType>::RightRotate(BinAVLTreeNode<ElemType> *&subRoot)
// 操作结果: 对以subRoot为根的二叉树作右旋处理,处理之后subRoot指向新的树根结点,
//	也就是旋转处理前的左子树的根结点
{
	BinAVLTreeNode<ElemType> *pLChild;
	pLChild = subRoot->leftChild;				// pLChild指向subRoot左孩子
	subRoot->leftChild = pLChild->rightChild;	// pLChild的右子树链接为subRoot的左子树
	pLChild->rightChild = subRoot;				// subRoot链接为pLChild的右孩子
	subRoot = pLChild;							// subRoot指向新的根结点
}

template <class ElemType>
bool BinaryAVLTree<ElemType>::Insert(const ElemType &e)
// 操作结果: 插入数据元素e
{
	BinAVLTreeNode<ElemType> *f, *af, *a, *b, *c;
	if (Find(e, f, a, af) == NULL)	{	    // 查找失败, 则插入成功
		BinAVLTreeNode<ElemType> *p;	    // 插入的新结点
		p = new BinAVLTreeNode<ElemType>(e);// 生成插入结点
		p->bf = 0;
		if (IsEmpty()){	                    // 空二叉树,新结点为根结点
			root = p;
		    return true;
        }		
		if (e < f->data)        // e比其双亲小,插入结点为f的左孩子
			f->leftChild = p;
		else	                // e比其双亲大,插入结点为f的右孩子
			f->rightChild = p;
			
		switch (a->bf)	{
			case LH:
		        if (a->data > e) { // LL旋转 
                   b = a->leftChild;
                   if (b->data > e) {
		              a->bf = b->bf = EH;// 修改平衡因子 
		              a->leftChild = b->rightChild;
		              b->rightChild = a; // 完成旋转，子树的根为b 
                   }
                   else {          // LR旋转
                      c = b->rightChild;
 		              if (c == p) {     // 修改平衡因子 
                         a->bf = b->bf = EH;
                      }
                      else if (e < c->data)
                         a->bf = RH;
                      else {
                         a->bf = EH;
                         b->bf = LH;
                      }
                      // 进行LR旋转   
                      b->rightChild = c->leftChild;
                      a->leftChild = c->rightChild;
                      c->leftChild = b;
                      c->rightChild = a;
                      b = c;        // 完成旋转，子树的根为b
                   }
                   // 把完成旋转的子树插入到原树中    
                   if (af == NULL)
                      root = b;    // 失去平衡的最小子树的根为整棵树的根 
                   else if (e < af->data)
                      af->leftChild = b; // 失去平衡的最小子树为其双亲的左子树 
                   else
                      af->rightChild = b;// 失去平衡的最小子树为其双亲的右子树   
                }   
                else {
                   a->bf = EH;     // 不旋转，仅需要修改平衡因子 
                   a = a->rightChild;
                   while (a != p) 
                      if (a->data > e){
		                 a->bf = LH;
		                 a = a->leftChild;
                      }
                      else {
                         a->bf = RH;
                         a = a->rightChild;
                      }
                }
                break;
			case EH:				// 不旋转，仅需要修改平衡因子
                while (a != p) 
                   if (a->data > e){
		              	a->bf = LH;
		              	a = a->leftChild;
                   }
                	else {
                   		a->bf = RH;
                   		a = a->rightChild;
                }
				break;
			case RH:				
		        if (a->data < e) {          // RR旋转
                   b = a->rightChild;    
                   if (b->data < e) {
		              a->bf = b->bf = EH;   // 修改平衡因子
		              a->rightChild = b->leftChild;
		              b->leftChild = a;     // 完成旋转，子树的根为b
                   }
                   else {
                      c = b->leftChild;    // RL旋转 
 		              if (c == p) {        // 修改平衡因子
                         a->bf = b->bf = EH;
                      }
                      else if (e > c->data)
                         a->bf = LH;
                      else {
                         a->bf = EH;
                         b->bf = RH;
                      } 
                      // 进行RL旋转  
                      b->leftChild = c->rightChild;
                      a->rightChild = c->leftChild;
                      c->rightChild = b;
                      c->leftChild = a;
                      b = c;           // 完成旋转，子树的根为b
                   }    
                   // 把完成旋转的子树插入到原树中    
                   if (af == NULL)
                      root = b;    // 失去平衡的最小子树的根为整棵树的根 
                   else if (e < af->data)
                      af->leftChild = b; // 失去平衡的最小子树为其双亲的左子树 
                   else
                      af->rightChild = b;// 失去平衡的最小子树为其双亲的右子树   
               }   
                else {               // 不旋转，仅需要修改平衡因子
                   a->bf = EH;
                   a = a->leftChild;
                   while (a != p) 
                      if (a->data > e){
		                 a->bf = LH;
		                 a = a->leftChild;
                      }
                      else {
                         a->bf = RH;
                         a = a->rightChild;
                      }
                }
				break;
        }
		return true;		
	}
	else	// 查找成功, 则插入失败
		return false;
}

template <class ElemType>
void BinaryAVLTree<ElemType>::DeleteLeftBalance(BinAVLTreeNode<ElemType> *&
subRoot, bool &isShorter)
// 操作结果: 对以subRoot为根的二叉树删除时作左平衡处理, 删除subRoot的左子树上的结点，处
//	理后subRoot指向新的树根结点
{
	BinAVLTreeNode<ElemType> *ptrRChild, *ptrRLChild;	
	ptrRChild  = subRoot->rightChild;	// ptrRChild指向subRoot右孩子
	switch (ptrRChild->bf)	{	// 根据subRoot的右子树的平衡因子作相应的平衡处理
	case RH:							// 右高，作单左旋转
		subRoot->bf = ptrRChild->bf = EH;// 平衡因子都为0
		LeftRotate(subRoot);			// 左旋
		isShorter = true;
		break;
	case EH:							// 等高，作单左旋转
		subRoot->bf = RH;
		ptrRChild->bf = LH;		
		LeftRotate(subRoot);			// 左旋
		isShorter = false;
		break;
	case LH:							// 左高,先右旋后左旋
		ptrRLChild = ptrRChild->leftChild;	// ptrRLChild指向subRoot的右孩子的左子树的根
		switch (ptrRLChild->bf)		{	// 修改subRoot及右孩子的平衡因子
		case LH:
			subRoot->bf = EH;
			ptrRChild->bf = RH;
			isShorter = true;
			break;
		case EH:
			subRoot->bf = ptrRChild->bf = EH;
			isShorter = false;
			break;
		case RH:
			subRoot->bf = LH;
			ptrRChild->bf = EH;
			isShorter = true;
			break;
		}
		ptrRLChild->bf = 0;
		RightRotate(subRoot->rightChild);	// 对subRoot右子树作右旋处理
		LeftRotate(subRoot);				// 对subRoot作左旋处理
	}
}

template <class ElemType>
void BinaryAVLTree<ElemType>::DeleteRightBalance(BinAVLTreeNode<ElemType> *
&subRoot, bool &isShorter)
// 操作结果: 对以subRoot为根的二叉树删除时作右平衡处理, 删除subRoot的右子树上的结点，处
//	理后subRoot指向新的树根结点
{
	BinAVLTreeNode<ElemType> *ptrLChild, *ptrLRChild;	
	ptrLChild  = subRoot->leftChild;// ptrLChild指向subRoot左孩子
	switch (ptrLChild->bf)	{	    // 根据subRoot的左子树的平衡因子作相应的平衡处理
	case LH:						// 右高，作单右旋转
		subRoot->bf = ptrLChild->bf = EH;// 平衡因子都为0
		RightRotate(subRoot);		// 右旋
		isShorter = true;
		break;
	case EH:						// 等高，作单右旋转
		subRoot->bf = LH;
		ptrLChild->bf = RH;			// 平衡因子都为0
		RightRotate(subRoot);		// 右旋
		isShorter = false;
		break;
	case RH:						// 左高,先左旋后右旋
		ptrLRChild = ptrLChild->rightChild;// ptrLRChild指向subRoot的左孩子的右子树的根
		switch (ptrLRChild->bf)
		{	// 修改subRoot及左孩子的平衡因子
		case LH:
			subRoot->bf = RH;
			ptrLChild->bf = EH;
			isShorter = true;
			break;
		case EH:
			subRoot->bf = ptrLChild->bf = EH;
			isShorter = false;
			break;
		case RH:
			subRoot->bf = EH;
			ptrLChild->bf = LH;
			isShorter = true;
			break;
		}
		ptrLRChild->bf = 0;
		LeftRotate(subRoot->leftChild);	// 对subRoot左子树作左旋处理
		RightRotate(subRoot);			// 对subRoot作右旋处理
	}
}

template <class ElemType>
void BinaryAVLTree<ElemType>::DeleteBalance(const ElemType &key, 
LinkStack<BinAVLTreeNode<ElemType> *> &s)
// 操作结果: 根据查找路径，从删除结点进行回溯,并作平衡处理
{
	bool isShorter = true;
	while (!s.IsEmpty() && isShorter)	{
		BinAVLTreeNode<ElemType> *ptrCurNode, *ptrParent;
		s.Pop(ptrCurNode);		// 取出待平衡的结点
		if (s.IsEmpty())	    // ptrCurNode已为根结点,ptrParent为空
			ptrParent = NULL;
		else	                // ptrCurNode不为根结点,取出双亲ptrParent
			s.Top(ptrParent);

		if (key < ptrCurNode->data)		{	// 删除ptrCurNode的左子树上的结点
			switch (ptrCurNode->bf)		{	// 检查ptrCurNode的平衡度
			case LH:						// 左高
				ptrCurNode->bf = EH;
				break;
			case EH:						// 等高
				ptrCurNode->bf = RH;
				isShorter = false;
				break;
			case RH:						// 右高
				if (ptrParent == NULL)	{	// 已回溯到根结点
					DeleteLeftBalance(ptrCurNode, isShorter);
					root = ptrCurNode;		// 转换后ptrCurNode为新根
				}
				else if (ptrParent->leftChild == ptrCurNode)// ptrParent左子树作平衡处理
					DeleteLeftBalance(ptrParent->leftChild, isShorter);
				else	// ptrParent右子树作平衡处理
					DeleteLeftBalance(ptrParent->rightChild, isShorter);
				break;
			}
		}
		else
		{	// 删除ptrCurNode的右子树上的结点
			switch (ptrCurNode->bf)	   {	// 检查ptrCurNode的平衡度
			case RH: 						// 右高
				ptrCurNode->bf = EH;
				break;
			case EH: 						// 等高
				ptrCurNode->bf = LH;
				isShorter = false;
				break;
			case LH: 						// 左高
				if (ptrParent == NULL)	{	// 已回溯到根结点
					DeleteLeftBalance(ptrCurNode, isShorter);
					root = ptrCurNode;		// 转换后ptrCurNode为新根
				}
				else if (ptrParent->leftChild == ptrCurNode)	// ptrParent左子树作平衡处理
					DeleteLeftBalance(ptrParent->leftChild, isShorter);
				else	// ptrParent右子树作平衡处理
					DeleteLeftBalance(ptrParent->rightChild, isShorter);
				break;
			}
		}
	}
}

template <class ElemType>
void BinaryAVLTree<ElemType>::DeleteHelp(const ElemType &key, 
BinAVLTreeNode<ElemType> *&p, LinkStack< BinAVLTreeNode<ElemType> *> &s)
// 操作结果: 删除p指向的结点
{
	BinAVLTreeNode<ElemType> *tmpPtr, *tmpF;  
	if (p->leftChild == NULL && p->rightChild == NULL)	{// p为叶结点
		delete p;
		p = NULL;
		DeleteBalance(key, s);
	}
	else if (p->leftChild == NULL)	{	// p只有左子树为空
		tmpPtr = p;
		p = p->rightChild;
		delete tmpPtr;
		DeleteBalance(key, s);
	}
	else if (p->rightChild == NULL)	{	// p只有右子树非空
		tmpPtr = p;
		p = p->leftChild;
		delete tmpPtr;
		DeleteBalance(key, s);
	}
	else	{	// p左右子树都有 
		tmpF = p;
		s.Push(tmpF);
		tmpPtr = p->leftChild;
		while (tmpPtr->rightChild != NULL)	{// 查找p在中序序列中直接前驱tmpPtr及其双亲tmpF
			tmpF = tmpPtr;
			s.Push(tmpF);
			tmpPtr = tmpPtr->rightChild;
		}
		p->data = tmpPtr->data;// 将tmpPtr指向结点的元素值赋值给被删除结点

		if (tmpF->rightChild == tmpPtr)	//  删除tmpPtr指向的结点
			DeleteHelp(key, tmpF->rightChild, s);
		else
			DeleteHelp(key, tmpF->leftChild, s);
	}
}

template <class ElemType>
bool BinaryAVLTree<ElemType>::Delete(const ElemType &key)
// 操作结果: 删除关键字为key的结点
{
	BinAVLTreeNode<ElemType> *p, *f;
	LinkStack< BinAVLTreeNode<ElemType> *> s;
	p = Find(key, f, s);
	if ( p == NULL)	    // 查找失败, 则删除失败
		return false;
	else	{	        // 查找成功, 插入失败
		if (f == NULL)	// 被删除结点为根结点
			DeleteHelp(key, p, s);
		else if (key < f->data)		// key比双亲小,删除f的左孩子
			DeleteHelp(key, f->leftChild, s);
		else	                    // key比双亲大,删除f的右孩子
			DeleteHelp(key, f->rightChild, s);
		return true;		
	}
}

template <class ElemType>
void BinaryAVLTree<ElemType>::DestroyHelp(BinAVLTreeNode<ElemType> *&r)
// 操作结果：销毁以r的平衡二叉树
{
	if(r != NULL)	{	// r非空,实施销毁
		DestroyHelp(r->leftChild);		// 销毁左子树
		DestroyHelp(r->rightChild);		// 销毁右子树
		delete r;						// 销毁根结点
		r = NULL;
	}
}

template <class ElemType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType>::CopyTreeHelp(BinAVLTreeNode<ElemType> *copy)
// 操作结果：将以copy为根的平衡二叉树复制成新的平衡二叉树,返回新平衡二叉树的根
{
	if (copy == NULL)	// 复制空平衡二叉树
		return NULL;					// 空平衡二叉树根为空	
	else	{	// 复制非空平衡二叉树
		BinAVLTreeNode<ElemType> *lChild = CopyTreeHelp(copy->leftChild);	// 复制左子树
		BinAVLTreeNode<ElemType> *rChild = CopyTreeHelp(copy->rightChild);	// 复制右子树
		BinAVLTreeNode<ElemType> *r = new BinAVLTreeNode<ElemType>(copy->data, copy->bf, lChild, rChild);
			// 复制根结点
		return r;
	}
}

template <class ElemType>
BinaryAVLTree<ElemType>::BinaryAVLTree(const BinaryAVLTree<ElemType> &copy)
// 操作结果：由已知平衡二叉树构造新平衡二叉树——复制构造函数
{
	root = CopyTreeHelp(copy.root);	// 复制平衡二叉树
}

template <class ElemType>
BinaryAVLTree<ElemType>::BinaryAVLTree(BinAVLTreeNode<ElemType> *r)
// 操作结果：建立以r为根的平衡二叉树
{	
	root = r;	// 复制平衡二叉树
}

template <class ElemType>
BinaryAVLTree<ElemType> &BinaryAVLTree<ElemType>::operator=(const BinaryAVLTree<ElemType> &copy)
// 操作结果：由已知二叉平衡树copy复制到当前平衡二叉树--赋值语句重载
{
	if (&copy != this)	{
		DestroyHelp(root);				// 释放原平衡二叉树所占用空间
		root = CopyTreeHelp(copy.root);	// 复制平衡二叉树
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(const BinAVLTreeNode<ElemType> *r, int level)
//	操作结果：按树状形式显示以r为根的平衡二叉树，level为层次数，可设根结点的层次数为1
{
	if(r != NULL)	{	//空树不显式，只显式非空树
		DisplayBTWithTreeShapeHelp<ElemType>(r->rightChild, level + 1);//显示右子树
		cout << endl << endl;					//显示新行	
		for(int i = 0; i < level - 1; i++)
			cout << "       ";				//确保在第level列显示结点
		cout << r->data << "(" << r->bf << ")";				//显示结点
		DisplayBTWithTreeShapeHelp<ElemType>(r->leftChild, level + 1);//显示左子树
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(const BinaryAVLTree<ElemType> &bt)
//	操作结果：树状形式显示平衡二叉树 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);	
		// 树状显示以bt.GetRoot()为根的平衡二叉树
	cout << endl;
}

#endif
