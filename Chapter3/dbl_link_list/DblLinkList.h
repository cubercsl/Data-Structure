#ifndef __DBL_LK_LIST_H__
#define __DBL_LK_LIST_H__

#include "Assistance.h"				// 辅助软件包
#include "DblNode.h"				// 双向链表结点类

// 双向链表类
template <class ElemType>
class DblLinkList 
{
protected:
//  循环链表的数据成员:
	DblNode<ElemType> *head;			// 头结点指针
	int length;							// 元素个数

public:
	DblLinkList();				        // 无参数的构造函数
	DblLinkList(ElemType v[], int n);	// 有参数的构造函数
 	virtual ~DblLinkList();		        // 析构函数
	int GetLength() const;			    // 求循环链表长度			 
	bool IsEmpty() const;			    // 判断循环链表是否为空
	void Clear();				        // 将循环链表清空
	void Traverse(void (*Visit)(const ElemType &)) const;// 遍历循环链表
	int LocateElem(const ElemType &e);	// 元素定位 
	Status GetElem(int i, ElemType &e) const;	 // 取指定位置的元素	
	Status SetElem(int i, const ElemType &e);	// 设置指定位置的元素值
	Status DeleteElem(int i, ElemType &e);		// 删除元素		
	Status InsertElem(int i, const ElemType &e);// 在任意位置插入元素
	Status InsertElem(const ElemType &e);	    // 在表尾插入元素
	DblLinkList(const DblLinkList<ElemType> &la);// 复制构造函数
	DblLinkList<ElemType> &operator =(const DblLinkList<ElemType> &la); // 重载赋值运算 
};


// 链表类的实现部分
template <class ElemType>
DblLinkList<ElemType>::DblLinkList()
// 操作结果：构造一个空链表
{
	head = new DblNode<ElemType>;	// 构造头指针
	assert(head);                   // 构造头结点失败，终止程序运行 
	head->prior = head->next = head;// 空循环链表头结点的前驱、后继为头结点本身
	length = 0;						// 初始化元素个数
}

template <class ElemType>
DblLinkList<ElemType>::DblLinkList(ElemType v[], int n)
// 操作结果：根据数组v中的元素，构造双向循环链表
{
    DblNode<ElemType> *p;
	p = head =  new DblNode<ElemType>;	// 构造头结点 
	assert(head);                       // 构造头结点失败，终止程序运行 
	for (int i = 0; i < n; i++) {
	    p->next = new DblNode<ElemType>(v[i],p);
	    assert(p->next);                // 构造元素结点失败，终止程序运行 
	    p = p->next;
    }
	length = n;						    // 初始化元素个数
    head->prior = p;                    //头结点的prior指向尾结点 
    p->next = head;	                    //尾结点的next指向头结点 
}

template <class ElemType>
DblLinkList<ElemType>::~DblLinkList()
// 操作结果：销毁循环链表
{
	Clear();			// 清空循环链表
	delete head;		// 释放头结点空间
}

template <class ElemType>
int DblLinkList<ElemType>::GetLength() const
// 操作结果：返回循环链表元素个数
{
	return length;
}

template <class ElemType>
bool DblLinkList<ElemType>::IsEmpty() const
// 操作结果：如循环链表为空，则返回true，否则返回false
{
	return head->next == head;
}

template <class ElemType>
void DblLinkList<ElemType>::Clear()
// 操作结果：清空循环链表
{

	ElemType tmpElem;	// 临时元素值
	while (length > 0)	// 循环链表非空，则删除第1个元素
		DeleteElem(1, tmpElem);
}

template <class ElemType>
void DblLinkList<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：依次对循环链表的每个元素调用函数(*visit)
{
    DblNode<ElemType> *p;
	for (p = head->next; p != head; p = p->next)		// 用p依次访问每个元素
		(*Visit)(p->data);	// 对循环链表的每个元素调用函数(*visit)
}

template <class ElemType>
int DblLinkList<ElemType>::LocateElem(const ElemType &e)
// 操作结果：返回指定元素在循环链表中第一次出现的序号，如果不存在返回0 
{
    DblNode<ElemType> *p = head->next;
    int count=1;
	while (p != head && p->data != e) {
	    count++;
		p = p->next;
	}
	if (p != head)
	    return count;
    else 
        return 0;
}

template <class ElemType>
Status DblLinkList<ElemType>::GetElem(int i, ElemType &e) const
// 操作结果：当循环链表存在第i个元素时，用e返回其值，函数返回ENTRY_FOUND,
//	否则函数返回NOT_PRESENT
{
    DblNode<ElemType> *p = head->next;
    int count;
	if (i < 1 || i > length)		// i范围错
		return NOT_PRESENT;				
	else	{	// i合法
		for (count = 1; count < i; count++)
		  p = p->next;	            // p指向第i个结点	
		e = p->data;				// 用e返回第i个元素的值
		return ENTRY_FOUND;
	}
}

template <class ElemType>
Status DblLinkList<ElemType>::SetElem(int i, const ElemType &e)
// 操作结果：将循环链表的第i个位置的元素赋值为e,
//	i的取值范围为1≤i≤length,
//	i合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
{
    DblNode<ElemType> *p = head->next;
    int count;
	if (i < 1 || i > length)
		return RANGE_ERROR;
	else	{	// i合法
		for (count = 1; count < i; count++)
		  p = p->next;	// p指向第i个结点	
		p->data = e;	// 设置第i个元素的值
		return SUCCESS;
	}
}

template <class ElemType>
Status DblLinkList<ElemType>::DeleteElem(int i, ElemType &e)
// 操作结果：删除循环链表的第i个位置的元素, 并用e返回其值,
//	i的取值范围为1≤i≤length,
//	i合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
{
    DblNode<ElemType> *p = head->next;
    int count;
	if (i < 1 || i > length)
		return RANGE_ERROR;
	else	{	// i合法
		for (count = 1; count < i; count++)
		  p = p->next;	// p指向第i个结点	
		p->prior->next = p->next;	// p的前驱结点的next指向p结点的后继结点 
		p->next->prior = p->prior;	// p的后继结点的prior指向p结点的前驱结点
		e = p->data;				// 用e返回被删结点元素值	
		length--;					// 删除成功后元素个数减1 
		delete p;				    // 释放被删结点
		return SUCCESS;
	}
}

template <class ElemType>
Status DblLinkList<ElemType>::InsertElem(int i, const ElemType &e)
// 操作结果：在循环链表的第i个位置前插入元素e
//	i的取值范围为1≤i≤length+1
//	i合法时返回SUCCESS, 否则函数返回RANGE_ERROR
{
    DblNode<ElemType> *p = head->next,*q;
    int count;
	if (i < 1 || i > length + 1)	// i范围错,位置不合法
		return RANGE_ERROR; 
	else	{	// i合法
		for (count = 1; count < i; count++)
		  p = p->next;	// p指向第i个结点	
		q = new DblNode<ElemType>(e, p->prior, p);// 生成新结点q
		p->prior->next = q;			// p的前驱结点的next指向q结点
		p->prior = q;				// p的prior指向q结点
		length++;					// 插入成功后元素个数加1 
		return SUCCESS;
	}
}

template <class ElemType>
Status DblLinkList<ElemType>::InsertElem(const ElemType &e)
// 操作结果：在循环链表的表尾插入元素e
{
    DblNode<ElemType> *p;
	p = new DblNode<ElemType>(e, head->prior,head);// 生成新结点
	assert(p);                   	// 构造元素结点失败，终止程序运行 
	head->prior->next = p;			// 原尾结点的next指向p结点
	head->prior = p;				// 头结点prior指向q结点
	length++;						// 插入成功后元素个数加1 
	return SUCCESS;
}

template <class ElemType>
DblLinkList<ElemType>::DblLinkList(const DblLinkList<ElemType> &la)
// 操作结果：复制构造函数，由单链表la构造新单链表
{
	int laLength = la.GetLength();	// 取被复制单链表的长度
	ElemType e;
	head = new DblNode<ElemType>;	// 构造头指针
	assert(head);                   // 构造头指针失败，终止程序运行 
	length = 0;						// 初始化元素个数

	for (int i = 1; i <= laLength; i++)	{	// 复制数据元素
		la.GetElem(i, e);	// 取出第i个元素的值放在e中 
		InsertElem(e);		// 将e插入到当前单链表的表尾 
	}
}

template <class ElemType>
DblLinkList<ElemType> &DblLinkList<ElemType>::operator =(const DblLinkList<ElemType> &la)
// 操作结果：重载赋值运算符，将单链表la赋值给当前单链表
{
	if (&la != this)	{
		int laLength = la.GetLength();// 取被赋值单链表的长度
		ElemType e;
		Clear();							// 清空当前单链表
		for (int i = 1; i <= laLength; i++)		{
			la.GetElem(i, e);		    // 取出第i个元素的值放在e中
			InsertElem(e);		            // 将e插入到当前单链表的表尾
		}
	}
	return *this;
}

#endif
