#ifndef __BIN_TREE_NODE_H__
#define __BIN_TREE_NODE_H__

#define LH -1								// 左高
#define EH 0								// 等高
#define RH 1								// 右高

// 二叉平衡树结点类
template <class ElemType>
struct BinAVLTreeNode
{
// 数据成员:
	ElemType data;							// 数据域
	int bf;									// 结点的平衡因子
	BinAVLTreeNode<ElemType> *leftChild;	// 左孩子指针域
	BinAVLTreeNode<ElemType> *rightChild;	// 右孩子指针域

//	构造函数:
	BinAVLTreeNode();						// 无参数的构造函数 
	BinAVLTreeNode(const ElemType &e,		// 有参数的构造函数
		int bFactor = 0,
		BinAVLTreeNode<ElemType> *lChild = NULL, 
		BinAVLTreeNode<ElemType> *rChild = NULL);
};

// 二叉平衡树结点类的实现部分
template <class ElemType>
BinAVLTreeNode<ElemType>::BinAVLTreeNode()
// 操作结果：构造一个叶结点
{
	bf = 0;							// 平衡因子
	leftChild = rightChild = NULL;	// 叶结点左右孩子为空
}

template <class ElemType>
BinAVLTreeNode<ElemType>::BinAVLTreeNode(const ElemType &e, int bFactor, 
								   BinAVLTreeNode<ElemType> *lChild, 
								   BinAVLTreeNode<ElemType> *rChild)

// 操作结果：构造一个数据域为e,平衡因子为bFactor,左孩子为lChild,右孩子为rChild的结点
{	
	data = e;						// 数据元素值
	bf = bFactor;					// 平衡因子
	leftChild = lChild;				// 左孩子
	rightChild = rChild;			// 右孩子
}

#endif

