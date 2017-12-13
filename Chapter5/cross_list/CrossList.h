#ifndef __CROSS_LIST_H__
#define __CROSS_LIST_H__

#include "Assistance.h"				// 辅助软件包
#include "crossnode.h"				// 十字链表三元组结点类
#include "triple.h"					// 三元组类

// 稀疏矩阵十字链表类
template<class ElemType>
class CrossList
{
protected:
//  稀疏矩阵十字链的数据成员:
	CrossNode<ElemType> **rowHead, **colHead;// 行列链表表头数组
	int rows, cols, num;			// 稀疏矩阵的行数,列数及非零元个数

public:
// 稀疏矩阵十字链的方法声明:
	CrossList(int rs = DEFAULT_SIZE, int cs = DEFAULT_SIZE);
		// 构造一个rs行cs列的空稀疏矩阵
	~CrossList();				// 析构函数
	void Clear();					// 清空稀疏矩阵
	int GetRows() const { return rows; };			// 返回稀疏矩阵行数
    int GetCols() const { return cols; };			// 返回稀疏矩阵列数
    int GetNum() const { return num; };			// 返回稀疏矩阵非零元个数
	Status SetElem(int r, int c, const ElemType &v);	// 设置指定位置的元素值
	Status GetElem(int r, int c, ElemType &v);			// 取指定位置的元素值
	CrossList(const CrossList<ElemType> &b);	// 复制构造函数
	CrossList<ElemType> &operator =(const CrossList<ElemType> &b); 
		// 重载赋值运算符 
	CrossList<ElemType> operator +(const CrossList<ElemType> &b); 
		// 重载加法运算符 
};

// 稀疏矩阵十字链表类的实现部分
template <class ElemType>
CrossList<ElemType>::CrossList(int rs, int cs)
// 操作结果：构造一个rs行cs列的空稀疏矩阵
{
	if (rs < 1 || cs < 1)							
		throw Error("行数或列数无效!");	// 抛出异常
	rows = rs;							// 行数
	cols = cs;							// 列数
	num = 0;							// 非零元个数
	rowHead = new CrossNode<ElemType> *[rows];	// 分配行链表表头数组存储空间
	colHead = new CrossNode<ElemType> *[cols];	// 分配行链表表头数组存储空间
	for (int row = 0; row < rows; row++) 
		rowHead[row] = NULL;			// 初始化行链表表头数组
	for (int col = 0; col < cols; col++) 
		colHead[col] = NULL;			// 初始化行链表表头数组
}

template <class ElemType>
CrossList<ElemType>::~CrossList()
// 操作结果：稀疏矩阵所占用空间
{
	Clear();
	delete []rowHead;					// 释放行链表表头数组
	delete []colHead;					// 释放列链表表头数组
}

template <class ElemType>
void CrossList<ElemType>::Clear()
// 操作结果：清空稀疏矩阵
{
    CrossNode<ElemType> *p;
	for (int i = 0; i < rows; i++)	
		while (rowHead[i] != NULL)	{   // 释放第row行的结点所点用空间
			p =  rowHead[i];		
			rowHead[i] = p->right;	
			delete p;
		}
	for (int j = 0; j < cols; j++) 
		colHead[j] = NULL;			// 初始化行链表表头数组
    num = 0;
}

template <class ElemType>
Status CrossList<ElemType>::SetElem(int r, int c, const ElemType &v)
// 操作结果：如果下标范围错,则返回RANGE_ERROR,否则返回SUCCESS
{
	if (r >= rows || c >= cols || r < 0 || c < 0)
		return RANGE_ERROR;				// 下标范围错
	
	CrossNode<ElemType> *pre, *p;
	if (v == 0) {  // 把第r行、第c列的值修改为零 
	    pre = NULL; p=rowHead[r];	// p指向相应结点，pre为p的前驱结点 
		while (p != NULL && p->triElem.col < c)	{
			pre = p;
            p = p->right;
		}
  
	    if (p != NULL && p->triElem.col == c)  {// 原元素为非零元素，则删除p结点
            //  修改相应行中结点的指针    
			if (rowHead[r] == p)
                rowHead[r] = p->right;
            else
                pre->right = p->right;

            //  修改相应列中结点的指针    
			if (colHead[c] == p)  
			   colHead[c] = p->down;
            else {
                pre = colHead[c];
                while (pre->down != p) 
                    pre = pre->down;
                pre->down = p->down;
            }
            delete p;            
		    num--;				// 删除结点,非零元素个数减1
        }
    }        		
	else	{  // 把第r行、第c列的值修改为非零元素 
	    pre = NULL; p=rowHead[r];	// p指向相应结点，pre为p的前驱结点 
		while (p != NULL && p->triElem.col < c)	{
			pre = p;	p = p->right;
		}
  
	    if (p != NULL && p->triElem.col == c)  	// 原结点为非零元素，则直接修改其值 
            p->triElem.value == v;
        else { 	// 原结点为0元素，则需要插入结点
            Triple<ElemType> e(r, c, v);		// 三元组
	        CrossNode<ElemType> *ePtr = new CrossNode<ElemType>(e);//生成结点
            // 把结点插入到相应行中    	    
	        if (rowHead[r] == p)
                rowHead[r] = ePtr;
 	        else
			    pre->right = ePtr;
   	        ePtr->right = p;	
            // 把结点插入到相应列中    	    
		    pre = NULL; p=colHead[c];
		    while (p != NULL && p->triElem.row < r)	{
			    pre = p;
   	            p = p->down;
		    }
	        if (colHead[c] == p)
                colHead[c] = ePtr;
 	        else
			    pre->down = ePtr;
   	        ePtr->down = p;	
		    num++;							// 完成插入结点后非零元素个数加一 
	   }
	}	   
	return SUCCESS;							// 返回修改成功
}

template <class ElemType>
Status CrossList<ElemType>::GetElem(int r, int c, ElemType &v)
// 操作结果：如果下标范围错,则返回RANGE_ERROR,否则返回SUCCESS,并用v返回指定位置元素值
{
	if (r >= rows || c >= cols || r < 0 || c < 0)
		return RANGE_ERROR;			// 下标范围错
	
	CrossNode<ElemType> *p;
	for (p=rowHead[r]; p != NULL && p->triElem.col < c; p = p->right);
		// 寻找在第r行链表中的三元组位置
	if (p != NULL && p->triElem.col == c)	// 找到三元组
		v = p->triElem.value;
	else	// 未找到三元组
		v = 0;						// 不存在指定位置(r, c)的三元组,表示0元素

	return SUCCESS;					// 成功
}

template <class ElemType>
CrossList<ElemType>::CrossList(const CrossList<ElemType> &b)
// 操作结果：由稀疏矩阵b构造新稀疏矩阵——复制构造函数
{
    CrossNode<ElemType> *p;
	rows = b.rows;					// 复制行数
	cols = b.cols;					// 复制列数
	num = 0;						// 初始化非零元个数
	rowHead = new CrossNode<ElemType> *[rows];	// 分配行链表表头数组存储空间
	colHead = new CrossNode<ElemType> *[cols];	// 分配行链表表头数组存储空间
	for (int i = 0; i < rows; i++) 
		rowHead[i] = NULL;			// 初始化行链表表头数组
	for (int i = 0; i < cols; i++) 
		colHead[i] = NULL;			// 初始化行链表表头数组
	
	for (int i = 0; i < rows; i++)
		for (p = b.rowHead[i]; p != NULL; p = p->right)
			SetElem(p->triElem.row, p->triElem.col, p->triElem.value);
}

template <class ElemType>
CrossList<ElemType> &CrossList<ElemType>::operator =(const CrossList<ElemType> &b)
// 操作结果：将稀疏矩阵b赋值给当前稀疏矩阵——赋值语句重载
{
    if (rows != b.rows || cols != b.cols)
        throw Error("行数或列数不相等!");	// 抛出异常

	if (&b != this) {
	    CrossNode<ElemType> *p;
		Clear();						// 清空稀疏矩阵
		num = b.num;					// 初始化非零元个数
		for (int i = 0; i < rows; i++)
			for (p = b.rowHead[i]; p != NULL; p = p->right)
			   SetElem(p->triElem.row, p->triElem.col, p->triElem.value);
	}
	return *this;

}

template <class ElemType>
CrossList<ElemType> CrossList<ElemType>::operator +(const CrossList<ElemType> &b)
// 操作结果：将稀疏矩阵b赋值加到当前稀疏矩阵中——加法运算符重载
{
    if (rows != b.rows || cols != b.cols)
        throw Error("行数或列数不相等!");	// 抛出异常

    CrossList<ElemType> temp(b.rows,b.cols);
    ElemType v;
    CrossNode<ElemType> *p, *q;

	for (int i = 0; i < rows; i++) {
		p = rowHead[i]; q = b.rowHead[i];
        while (p != NULL && q != NULL)  
           if (p->triElem.col < q->triElem.col) {
		       temp.SetElem(p->triElem.row, p->triElem.col, p->triElem.value);
		       p = p->right;
           }
           else  if (p->triElem.col > q->triElem.col) {
		       temp.SetElem(q->triElem.row, q->triElem.col, q->triElem.value);
		       q = q->right;
           }
           else  {
               v = p->triElem.value + q->triElem.value;
               if (v != 0)
		          temp.SetElem(q->triElem.row, q->triElem.col, v);
		       p = p->right;
		       q = q->right;
           }
        while (p != NULL)  {
 		   temp.SetElem(p->triElem.row, p->triElem.col, p->triElem.value);
		   p = p->right;
        }
        while (q != NULL)  {
           temp.SetElem(q->triElem.row, q->triElem.col, q->triElem.value);
		   q = q->right;
        }
	}			   
	return temp;

}
#endif
