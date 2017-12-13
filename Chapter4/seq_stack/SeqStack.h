#ifndef __SQ_STACK_H__
#define __SQ_STACK_H__
#include "Assistance.h"	// 辅助软件包


// 顺序栈模板类
template<class ElemType>
class SeqStack 
{
protected:
// 顺序栈的数据成员:
	int top;										// 栈顶指针 
	int maxSize;									// 栈的最大容量 
	ElemType *elems;								// 元素存储空间

public:
//  顺序栈的方法声明及重载编译系统默认方法声明:
	SeqStack(int size = DEFAULT_SIZE);				// 构造函数
	virtual ~SeqStack();							// 析构函数
	int GetLength() const;							// 求栈的长度			 
	bool IsEmpty() const;							// 判断栈是否为空
	void Clear();									// 将栈清空
	void Traverse(void (*Visit)(const ElemType &)) const;	// 遍历栈
	Status Push(const ElemType e);				    // 入栈
	Status Top(ElemType &e) const;				    // 取顶元素
	Status Pop(ElemType &e);					    // 出栈
	SeqStack(const SeqStack<ElemType> &s);		// 复制构造函数
	SeqStack<ElemType> &operator =(const SeqStack<ElemType> &s); // 赋值语句重载
};


// 顺序栈类的实现部分

template<class ElemType>
SeqStack<ElemType>::SeqStack(int size)
// 操作结果：构造一个最大容量为size的空栈
{
	maxSize = size;						// 栈的最大容量
	if (elems != NULL) delete []elems;	// 释放已有存储空间
	elems = new ElemType[maxSize];		// 分配新的存储空间
	top = -1;	
}

template<class ElemType>
SeqStack<ElemType>::~SeqStack()
// 操作结果：销毁栈
{
	delete []elems;					// 释放栈的存储空间
}

template <class ElemType>
int SeqStack<ElemType>::GetLength() const
// 操作结果：返回栈中元素个数
{
	return top + 1;
}

template<class ElemType>
bool SeqStack<ElemType>::IsEmpty() const
// 操作结果：如栈为空，则返回true，否则返回false
{
	return top == -1;
}

template<class ElemType>
void SeqStack<ElemType>::Clear()
// 操作结果：清空栈
{
	top = -1;
}

template <class ElemType>
void SeqStack<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：从栈顶到栈底依次对栈的每个元素调用函数(*visit)访问 
{
	for (int i = top; i >=0 ; i--) 
		(*Visit)(elems[i]);
}

template<class ElemType>
Status SeqStack<ElemType>::Push(const ElemType e)
// 操作结果：将元素e追加到栈顶,如成功则返加SUCCESS,如栈已满将返回OVER_FLOW
{
	if (top == maxSize - 1) // 栈已满
		return OVER_FLOW;
	else  {	// 操作成功
		elems[++top] = e;	// 将元素e追加到栈顶 
		return SUCCESS;
	}
}

template<class ElemType>
Status SeqStack<ElemType>::Top(ElemType &e) const
// 操作结果：如栈非空,用e返回栈顶元素,函数返回SUCCESS,否则函数返回UNDER_FLOW
{
	if(IsEmpty())	 // 栈空
		return UNDER_FLOW;
	else	{ // 栈非空,操作成功
		e = elems[top];	// 用e返回栈顶元素
		return SUCCESS;
	}
}

template<class ElemType>
Status SeqStack<ElemType>::Pop(ElemType &e)
// 操作结果：如栈非空,删除栈顶元素,并用e返回栈顶元素,函数返回SUCCESS,否则
// 函数返回UNDER_FLOW
{
	if (IsEmpty())	 // 栈空
		return UNDER_FLOW;
	else	{ // 操作成功
		e = elems[top--]; // 用e返回栈顶元素
		return SUCCESS;
	}
}

template<class ElemType>
SeqStack<ElemType>::SeqStack(const SeqStack<ElemType> &s) 
// 操作结果：由栈s构造新栈--复制构造函数
{
    maxSize = s.maxSize;			    // 栈的最大容量 
    if (elems != NULL) delete []elems;	// 释放已有存储空间
    elems = new ElemType[maxSize];		// 分配存储空间
	top = s.top;					    // 复制栈顶指针 
	for (int i = 0; i <= top; i++)      // 从栈底到栈顶对栈s的每个元素进行复制
		elems[i] = s.elems[i];
}

template<class ElemType>
SeqStack<ElemType> &SeqStack<ElemType>::operator = (const SeqStack<ElemType> &s)
// 操作结果：将栈s赋值给当前栈--赋值语句重载
{
	if (&s != this)	{
	    maxSize = s.maxSize;			    // 栈的最大容量 
	    if (elems != NULL) delete []elems;	// 释放已有存储空间
	    elems = new ElemType[maxSize];		// 分配存储空间
		top = s.top;					    // 复制栈顶指针 
		for (int i = 0; i <= top; i++)		// 从栈底到栈顶对栈s的每个元素进行复制
			elems[i] = s.elems[i];
	}
	return *this;
}

#endif
