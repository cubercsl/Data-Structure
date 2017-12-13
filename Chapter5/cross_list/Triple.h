#ifndef __TRIPLE_H__
#define __TRIPLE_H__

// 三元组类
template<class ElemType>
struct Triple
{
// 数据成员:
	int row, col;						// 非零元素的行下标与列下标
	ElemType value;						// 非零元素的值

// 构造函数:
	Triple(){};							// 无参数的构造函数
	Triple(int r, int c, ElemType v);	// 有参数的构造函数
};

// 三元组类的实现部分

template<class ElemType>
Triple<ElemType>::Triple(int r, int c, ElemType v)
// 操作结果：由已知数数据域构造三元组
{
	row = r;							// 行号
	col = c;							// 列号
	value = v;							// 非零元素值
}

#endif

