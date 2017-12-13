#ifndef __HUFFMAN_TREE_NODE_H__
#define __HUFFMAN_TREE_NODE_H__

// 哈夫曼树结点类
template <class WeightType>
struct HuffmanTreeNode
{
// 数据成员:
	WeightType weight;							// 权数据域
	unsigned int parent, leftChild, rightChild;	// 双亲,左右孩子域

// 构造函数:
	HuffmanTreeNode();							// 无参数的构造函数
	HuffmanTreeNode(WeightType w, int p = 0, int lChild = 0, int rChild = 0);
		// 已知权,双亲及左右孩子构造结点
};

// 哈夫曼树结点类的实现部分
template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode()
// 操作结果：构造空结点
{
	parent = leftChild = rightChild = -1;
}

template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(WeightType w, int p, int lChild, int rChild)									// 右孩子
// 操作结果：构造一个权为w,双亲为p,左孩子为lChild,右孩子为rChild的结点
{
	weight = w;								// 权
	parent = p;								// 双亲
	leftChild = lChild;						// 左孩子
	rightChild = rChild;					// 右孩子
}

#endif
