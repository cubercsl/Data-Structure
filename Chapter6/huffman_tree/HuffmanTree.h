#ifndef __HUFFMAN_TREE_H__
#define __HUFFMAN_TREE_H__

#include "String.h"								// 串类
#include "HuffmanTreeNode.h"					// 哈夫曼树结点类

// 哈夫曼树类
template <class CharType, class WeightType>
class HuffmanTree
{
protected:
//  哈夫曼树的数据成员:
	HuffmanTreeNode<WeightType> *nodes;			// 存储结点信息
	CharType *LeafChars;						// 叶结点字符信息
	String *LeafCharCodes;						// 叶结点字符编码信息
	int num;									// 叶结点个数

//	辅助函数:
	void Select(int n, int &r1, int &r2);		// 在nodes[0 ~ n-1]中选择双亲为0,权值最小的两个结点r1,r2
	void CreatHuffmanTree(CharType ch[], WeightType w[], int n);
		// 由n个字符和权值创建一棵哈夫曼树

public:
//  哈夫曼树方法声明及重载编译系统默认方法声明:
	HuffmanTree(CharType ch[], WeightType w[], int n);	// 由n个字符和权值构造哈夫曼树
	virtual ~HuffmanTree();						// 析构函数
	String Encode(CharType ch);					// 编码
	LinkList<CharType> Decode(String strCode);	// 译码
	HuffmanTree(const HuffmanTree<CharType, WeightType> &copy);	// 复制构造函数
	HuffmanTree<CharType, WeightType> &operator=(const HuffmanTree<CharType, 
		WeightType>& copy);						// 赋值运算符重载
};

// 孩子兄弟表示哈夫曼树类的实现部分
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::Select(int n, int &r1, int &r2)
// 操作结果：在nodes[0 ~ n-1]中选择双亲为0,权值最小的两个结点r1,r2
{
	r1 = r2 = -1;
	for (int i = 0; i < n; i++)	    // 查找树值最小的两个结点
		if (nodes[i].parent == -1) 	// 只处理双亲不为-1的结点
		   if (r1 == -1)	
			  r1 = i;
		   else if	(nodes[i].weight < nodes[r1].weight)	{
              r2 = r1;
              r1 = i;
           }
		   else if (r2 == -1 || nodes[i].weight < nodes[r2].weight)
	          r2 = i;
}

template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::CreatHuffmanTree(CharType ch[], WeightType w[], int n)
// 操作结果：由n个字符和权值创建一棵哈夫曼树
{
	num = n;					// 叶结点个数
	int m = 2 * n - 1;			// 结点个数

	nodes = new HuffmanTreeNode<WeightType>[m];
	LeafChars = new CharType[n];
	LeafCharCodes = new String[n];

	int i, p, q;					
	for (i = 0; i < n; i++)	{	// 存储叶结点信息
		nodes[i].weight = w[i];	
		nodes[i].leftChild = -1;
		nodes[i].rightChild = -1;
		nodes[i].parent = -1;
		LeafChars[i] = ch[i];	
	}

	for (i = n; i < m; i++){    // 构造哈夫曼树
		int r1, r2;
		Select(i, r1, r2);
		// 合并以r1,r2为根的树
		nodes[r1].parent = nodes[r2].parent = i;// r1,r2的双亲为i
		nodes[i].leftChild = r1;				// r1为i的左孩子
		nodes[i].rightChild = r2;				// r2为i的右孩子
		nodes[i].parent = -1;					// i为新的根结点 
		nodes[i].weight = nodes[r1].weight + nodes[r2].weight;//i的权为r1,r2的权值之和
	}

	for (i = 0; i < n; i++)	{	    // 求n个叶结点字符的编码
		LinkList<char> charCode;	// 暂存叶结点字符编码信息
		q = i; 
        p = nodes[q].parent;
		while (p != -1)     {	    // 从叶结点到根结点逆向求编码
			if (nodes[p].leftChild == q)
                charCode.InsertElem(1, '0');// 左分支编码为'0'
			else
                charCode.InsertElem(1, '1');// 右分支编码为'1'
			q = p;
            p = nodes[q].parent;
		}
		LeafCharCodes[i] = charCode;		// 复制字符编码
	}
}


template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(CharType ch[], WeightType w[], int n)
// 操作结果：由字符,权值和字符个数构造哈夫曼树
{
	CreatHuffmanTree(ch, w, n);				// 由字符,权值和字符个数构造哈夫曼树
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree()
// 操作结果：销毁哈夫曼树
{	
	if (nodes != NULL) delete []nodes;					// 释放结点信息
	if (LeafChars != NULL) delete []LeafChars;			// 释放叶结点字符信息
	if (LeafCharCodes != NULL) delete []LeafCharCodes;	// 释放叶结点字符编码信息
}

template <class CharType, class WeightType>
String HuffmanTree<CharType, WeightType>::Encode(CharType ch)
// 操作结果：返回字符编码
{
	for (int i = 0; i < num; i++)	    // 找到字符,得到编码
		if (LeafChars[i] == ch)
           return LeafCharCodes[i];
	throw Error("非法字符,无法编码!");	// 抛出异常
}

template <class CharType, class WeightType>
LinkList<CharType> HuffmanTree<CharType, WeightType>::Decode(String strCode)
// 操作结果：对编码串strCode进行译码,返回编码前的字符序列
{
	LinkList<CharType> charList;		// 编码前的字符序列
	int p = 2 * num - 2;
	for (int i = 0; i < strCode.GetLength(); i++)	{	// 处理每位编码
		if (strCode[i] == '0')
            p = nodes[p].leftChild;	    // '0'表示左分支	
		else
            p = nodes[p].rightChild;	// '1'表示左分支	

		if (nodes[p].leftChild == -1 && nodes[p].rightChild == -1)	{
            // 译码时从根结点开始搜索到一个叶结点
			charList.InsertElem(charList.GetLength() + 1, LeafChars[p]);
			p = 2 * num - 2;           // 从根开始重新搜索 
		}
	}
	
	if (p != 2 * num - 2)                   //最后一段代码没有对应字符 
	   throw Error("编码不对,无法译码!");	// 抛出异常

	return charList;					    // 返回编码前的字符序列
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(const HuffmanTree<CharType, WeightType> &copy)
// 操作结果：由哈夫曼树copy构造新哈夫曼树——复制构造函数
{
	num = copy.num;								// 叶结点个数
	int m = 2 * num - 1;						// 结点总数 
	nodes = new HuffmanTreeNode<WeightType>[m];
	LeafChars = new CharType[num];	
	LeafCharCodes = new String[num];

	int i;			
	for (i = 0; i < m; i++)	                    // 复制结点信息
		nodes[i] = copy.nodes[i];		
	
	for (i = 0; i < num; i++)	{	
		LeafChars[i] = copy.LeafChars[i];		// 复制叶结点字符信息
		LeafCharCodes[i] = copy.LeafCharCodes[i];// 复制叶结点字符编码信息
	}
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType> &HuffmanTree<CharType, WeightType>::operator=(const HuffmanTree<CharType, WeightType>& copy)	
// 操作结果：将哈夫曼树copy赋值给当前哈夫曼树——赋值运算符重载
{
	if (&copy != this)	{
		if (nodes != NULL) delete []nodes;					// 释放结点信息
		if (LeafChars != NULL) delete []LeafChars;			// 释放叶结点字符信息
		if (LeafCharCodes != NULL) delete []LeafCharCodes;	// 释放叶结点字符编码信息

		num = copy.num;						// 叶结点个数
		int m = 2 * num - 1;				// 结点总数 
		nodes = new HuffmanTreeNode<WeightType>[m];
		LeafChars = new CharType[num];	
		LeafCharCodes = new String[num];

		int i;						
		for (i = 0; i < m; i++)	            // 复制结点信息
			nodes[i] = copy.nodes[i];	
		
		for (i = 0; i < num; i++)	{	
            LeafChars[i] = copy.LeafChars[i];		// 复制叶结点字符信息
			LeafCharCodes[i] = copy.LeafCharCodes[i];// 复制叶结点字符编码信息
		}	
	}
	return *this;
}

#endif
