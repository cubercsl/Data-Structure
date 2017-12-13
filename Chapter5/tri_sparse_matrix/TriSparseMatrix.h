#ifndef __TRI_SPARSE_MATRIX_H__
#define __TRI_SPARSE_MATRIX_H__

#include "Assistance.h"				// 辅助软件包
#include "triple.h"					// 三元组类

// 稀疏矩阵三元组顺序表类
template<class ElemType>
class TriSparseMatrix
{
protected:
// 稀疏矩阵三元组顺序表的数据成员:
	Triple<ElemType> *triElems;		// 存储稀疏矩阵的三元组表
	int maxSize;					// 非零元素最大个数
	int rows, cols, num;			// 稀疏矩阵的行数,列数及非零元个数

public:
// 稀疏矩阵三元组顺序表的函数成员： 
	TriSparseMatrix(int rs = DEFAULT_SIZE, int cs = DEFAULT_SIZE, int size = DEFAULT_SIZE);
		// 构造一个rs行cs列非零元素最大个数为size的空稀疏矩阵
	~TriSparseMatrix();				// 析构函数
    int GetRows() const;			// 返回稀疏矩阵行数
    int GetCols() const;			// 返回稀疏矩阵列数
    int GetNum() const;				// 返回稀疏矩阵非零元个数
	Status SetElem(int r, int c, const ElemType &v);	// 设置指定位置的元素值
	Status GetElem(int r, int c, ElemType &v);			// 求指定位置的元素值
	TriSparseMatrix(const TriSparseMatrix<ElemType> &copy);	// 复制构造函数
	TriSparseMatrix<ElemType> &operator =(const TriSparseMatrix<ElemType> &copy); 
		// 赋值运算符重载
	void SimpleTranspose(TriSparseMatrix<ElemType> &b);// 稀疏矩阵的简单转置算法
	void FastTranspose(TriSparseMatrix<ElemType> &b);// 稀疏矩阵的快速转置算法
};

// 稀疏矩阵三元组顺序表类的实现部分
template <class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(int r, int c, int size)
// 操作结果： 构造一个r行c列非零元素最大个数为size的空稀疏矩阵
{
	if (r < 1 || c < 1)							
		throw Error("行数或列数无效!");	// 抛出异常
	maxSize = size;						// 非零元素最大个数
	rows = r;							// 行数
	cols = c;							// 列数
	num = 0;							// 非零元素个数
	triElems = new Triple<ElemType>[maxSize];	// 分配存储空间
} 

template <class ElemType>
TriSparseMatrix<ElemType>::~TriSparseMatrix()
// 操作结果：稀疏矩阵所占用空间
{
	if (triElems != NULL) delete []triElems; // 释放存储空间
}

template <class ElemType>
int TriSparseMatrix<ElemType>::GetRows() const
// 操作结果：返回稀疏矩阵行数
{
	return rows;					// 返回行数
}

template <class ElemType>
int TriSparseMatrix<ElemType>::GetCols() const
// 操作结果：返回稀疏矩阵列数
{
	return cols;					// 返回列数
}

template <class ElemType>
int TriSparseMatrix<ElemType>::GetNum() const
// 操作结果：返回稀疏矩阵非零元个数
{
	return num;						// 返回非零元个数
}

template <class ElemType>
Status TriSparseMatrix<ElemType>::SetElem(int r, int c, const ElemType &v)
// 操作结果：如果下标范围错,则返回RANGE_ERROR,如果溢出,则返回OVER_FLOW,否则返
//	回SUCCESS
{
	if (r >= rows || c >= cols || r < 0 || c < 0)
		return RANGE_ERROR;					// 下标范围错
	
	int i, j;								// 工作变量
	for (j = num - 1; j >= 0 && 
		(r < triElems[j].row || r == triElems[j].row && c < triElems[j].col); j--);// 查找三元组位置

	if (j >= 0 && triElems[j].row == r && triElems[j].col == c)	{	// 找到三元组
		if (v == 0)	{	// 删除三元组
			for (i = j + 1; i < num; i++)
				triElems[i - 1] = triElems[i];	// 前移从j+1开始的三元组
			num--;								// 删除三元组后,非零元个数自减1
		}
		else	// 修改元素值
			triElems[j].value = v;
		return SUCCESS;						// 成功
	}
	else if (v != 0)	{	
		if (num < maxSize)		{	// 将三元组(r, c, v)插入到三元组表中
			for (i = num - 1; i > j; i--)	// 后移元素	
				triElems[i + 1] = triElems[i];
			// j + 1为空出的插入位置
			triElems[j + 1].row = r;		// 行
			triElems[j + 1].col = c;		// 列
			triElems[j + 1].value = v;		// 非零元素值
			num++;							// 插入三元组后,非零元个数自加1
			return SUCCESS;					// 成功
		}
		else	// 溢出
			return OVER_FLOW;				// 溢出时返回OVER_FLOW
	}
	return SUCCESS;							// 成功
}

template <class ElemType>
Status TriSparseMatrix<ElemType>::GetElem(int r, int c, ElemType &v)
// 操作结果：如果下标范围错,则返回RANGE_ERROR,否则返回SUCCESS,并用v返回指定位置元素值
{
	if (r >= rows || c >= cols || r < 0 || c < 0)
		return RANGE_ERROR;			// 下标范围错

	int j;							// 工作变量

	
	for (j = num - 1; j >= 0 && 
		(r < triElems[j].row || r == triElems[j].row && c < triElems[j].col); j--);// 查找指定位置的三元组
	
	if (j >= 0 && triElems[j].row == r && triElems[j].col == c)	// 找到三元组
		v = triElems[j].value;		// 用v返回指定位置元素值
	else	// 未找到三元组
		v = 0;						// 未找到三元组,表示0元素值
	return SUCCESS;					// 成功
}

template <class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(const TriSparseMatrix<ElemType> &copy)
// 操作结果：由稀疏矩阵copy构造新稀疏矩阵——复制构造函数
{
	maxSize = copy.maxSize;							// 最大非零元素个数
	triElems = new Triple<ElemType>[maxSize];		// 分配存储空间
	rows = copy.rows;								// 复制行数
	cols = copy.cols;								// 复制列数
	num = copy.num;									// 复制非零元素个数
	triElems = new Triple<ElemType>[maxSize];		// 为三元组分配存储空间
	for (int i = 0; i < num; i++)	// 复制三元组
		triElems[i] = copy.triElems[i];
}

template <class ElemType>
TriSparseMatrix<ElemType> &TriSparseMatrix<ElemType>::operator =(const TriSparseMatrix<ElemType> &copy)
// 操作结果：将稀疏矩阵copy赋值给当前稀疏矩阵——赋值运算符重载
{
	if (&copy != this)	{
		maxSize = copy.maxSize;						// 最大非零元素个数
		if (triElems != NULL) delete []triElems;	// 释放存储空间
		triElems = new Triple<ElemType>[maxSize];	// 分配存储空间
		rows = copy.rows;							// 复制行数
		cols = copy.cols;							// 复制列数
		num = copy.num;								// 复制非零元素个数

		for (int i = 0; i < num; i++)	// 复制三元组
			triElems[i] = copy.triElems[i];
	}
	return *this;
}

template<class ElemType>
void TriSparseMatrix<ElemType>::SimpleTranspose(TriSparseMatrix<ElemType> &b)
// 操作结果：稀疏矩阵的简单转置算法，结果放在三元组顺序表b中 
{
	b.rows = cols;
	b.cols = rows;
	b.num = num;
	b.maxSize = maxSize;
	delete []b.triElems;
	b.triElems = new Triple<ElemType>[b.maxSize];

	if (b.num > 0)	{
		int i = 0;						// 稀疏矩阵b的下一个三元组的存放位置
		for (int col = 0; col < cols; col++)	
			for (int j = 0; j < num; j++)	// 查找a矩阵中第col列的三元组
				if (triElems[j].col == col)	{
					b.triElems[i].row = triElems[j].col;
					b.triElems[i].col = triElems[j].row;
					b.triElems[i].value = triElems[j].value;
					i++;							
				}
	}
}

template<class ElemType>
void TriSparseMatrix<ElemType>::FastTranspose(TriSparseMatrix<ElemType> &b)
// 操作结果：稀疏矩阵的快速转置算法，结果放在三元组顺序表b中 
{
	b.rows = cols;
	b.cols = rows;
	b.num = num;
	b.maxSize = maxSize;
	delete []b.triElems;
	b.triElems = new Triple<ElemType>[b.maxSize];

	int *cNum = new int[cols + 1];	// 存放原矩阵中每一列的非零元个数
	int *cPos = new int[cols + 1];	// 存放原矩阵中每一列的第一个非零元在b中的存储位置
	int col;
	int i;			        

	if (b.num > 0)	{
		for (col = 0; col < cols; col++) cNum[col] = 0;	// 初始化cNum
		for (i = 0; i < num; i++)
			++cNum[triElems[i].col];		// 统计原矩阵中每一列的非零元个数
		cPos[0] = 0;						// 第一列的第一个非零元在b存储的起始位置
		for (col = 1; col < cols; col++)	// 循环求每一列的第一个非零元在b存储的起始位置
			cPos[col] = cPos[col - 1] + cNum[col - 1];	

		for (i = 0; i < num; i++){	// 循环遍历原矩阵的三元组
			int j = cPos[triElems[i].col];	
				// 用于表示b当前列的下一个非零元三元组的存储位置
			b.triElems[j].row = triElems[i].col;
			b.triElems[j].col = triElems[i].row;
			b.triElems[j].value = triElems[i].value;
			++cPos[triElems[i].col];				
				// b当前列的下一个非零元三元组的存储新位置
		}
	}

	delete []cNum;	
	delete []cPos;	
}


#endif
