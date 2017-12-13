#ifndef __GEN_LIST_H__
#define __GEN_LIST_H__

#include "Assistance.h"				// 辅助软件包
#include "GenNode.h"					// 广义表结点类

// 广义表类
template<class ElemType>
class GenList
{
protected:
// 广义表类的数据成员:
	GenListNode<ElemType> *head;		// 广义表头指针
	
// 辅助函数
	void ShowHelp(GenListNode<ElemType> *hd) const;	
		// 显示以hd为头结点的广义表
	int DepthHelp(const GenListNode<ElemType> *hd);	
		// 计算以hd为表头的广义表的深度
	void ClearHelp(GenListNode<ElemType> *hd);		
		// 释放以hd为表头的广义表结构
	void CopyHelp(const GenListNode<ElemType> *sourceHead, 
		 GenListNode<ElemType> *&destHead);	
		// 将以destHead为头结点的广义表复制成以sourceHead为头结点的
		// 广义表
	static void CreateHelp(GenListNode<ElemType> *&first);
		// 创建以first为头结点的广义表

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	GenList();							// 无参数的构造函数
	GenList(GenListNode<ElemType> *hd);	// 由头结点指针构造广义表
	~GenList();							// 析构函数
	GenListNode<ElemType> *First() const;// 返回广义表的第一个元素
	GenListNode<ElemType> *Next(GenListNode<ElemType> *p) const;	                                                                               
		// 返回p指向的广义表元素的后继
	bool IsEmpty() const;				// 判断广义表是否为空
	void Insert(const ElemType &e);		// 将原子元素e作为表头加入到广义表最前面
	void Insert(GenList<ElemType> &subList);	
		// 将子表subList作为表头加入到广义表最前面
	Status Delete(int i);           // 删除广义表中第i个元素		
	int GetDepth();						// 计算广义表深度
    int GetLength();	                // 求广义表的长度
	GenList(const GenList<ElemType> &g);// 复制构造函数
	GenList<ElemType> &operator =(const GenList<ElemType> &g);// 赋值语句重载
	void Input(void);					// 输入广义表	
	void Show(void);					// 显示广义表	
};

// 广义表类的实现部分
template <class ElemType>
GenList<ElemType>::GenList()
// 操作结果：构造一个空广义表
{
	head = new GenListNode<ElemType>(HEAD);
	head->ref = 1;							// 引用数
}

template <class ElemType>
GenList<ElemType>::GenList(GenListNode<ElemType> *hd)
// 操作结果：由头结点指针构造广义表
{
	head = hd;								// 头结点
}

template <class ElemType>
GenListNode<ElemType> *GenList<ElemType>::First() const
// 操作结果：返回广义表的第一个元素
{
	return head->tLink;
}

template <class ElemType>
GenListNode<ElemType> *GenList<ElemType>::Next(GenListNode<ElemType> *p) const
// 操作结果：返回p指向的广义表元素的后继
{
	return p->tLink;
}

template <class ElemType>
bool GenList<ElemType>::IsEmpty() const
// 操作结果：如广义表为空，则返回true，否则返回false
{
	return head->tLink == NULL;
}

template <class ElemType>
void GenList<ElemType>::Insert(const ElemType &e)
// 操作结果：将原子元素e作为表头加入到广义表最前面
{
	GenListNode<ElemType> *p = new GenListNode<ElemType>(ATOM, head->tLink);
	p->atom = e;				// 数据域
	head->tLink = p;			// 将p插入在head与head->tLink之间 
}

template <class ElemType>
void GenList<ElemType>::Insert(GenList<ElemType> &subList)
// 操作结果：将子表subList作为表头加入到广义表最前面
{
	GenListNode<ElemType> *p = new GenListNode<ElemType>(LIST, head->tLink);
	p->hLink = subList.head;	// 子表
	subList.head->ref++;		// subList引用数自加1
	head->tLink = p;			// 将p插入在head与head->tLink之间 
}

template <class ElemType>
Status GenList<ElemType>::Delete(int i)
// 操作结果：删除广义表中第i个元素 
{
	if (i < 1 || i > GetLength())		
		return RANGE_ERROR;      // 返回位置错
	else	{
	    GenListNode<ElemType> *pre = head, *p = head->tLink;
		for (int k = 1; k < i; k++)  {//  使p和pre分别指向被删除结点和其前驱结点 
			pre = p;
            p = p->tLink; 
        }
        pre->tLink = p->tLink;
        if (p->tag == LIST)
       	    ClearHelp(p->hLink); 
        delete p;
		return SUCCESS;	        // 返回删除成功
	}
}


template <class ElemType>
void GenList<ElemType>::ShowHelp(GenListNode<ElemType> *hd) const
// 操作结果：显示以hd为头结点的广义表
{
	bool frist = true;
	cout << "(";						// 广义表以(开始
	for (GenListNode<ElemType> *p = hd->tLink; p != NULL; p = p->tLink)
	{	// 依次处理广义表各元素 
		if (frist) frist = false;		// 第一个元素
		else cout << ",";				// 不同元素这间用逗号隔开
		if (p->tag == ATOM)         	// 原子结点
			cout << p->atom;
		else	                     	// 表结点
			ShowHelp(p->hLink);
	}
	cout << ")";						// 广义表以)结束
}

template <class ElemType>
void GenList<ElemType>::Show(void)
// 操作结果：显示广义表	
{
	ShowHelp(head);					// 调用辅助函数显示广义表
}


template <class ElemType>
int GenList<ElemType>::DepthHelp(const GenListNode<ElemType> *hd)
// 操作结果：返回以hd为表头的广义表的深度
{
	if (hd->tLink == NULL) return 1;// 空广义表的深度为1
	
	int subMaxDepth = 0;			// 子表最大深度
	for (GenListNode<ElemType> *p = hd->tLink; p != NULL; p = p->tLink)
	{	// 求子表的最大深度
		if (p->tag == LIST)
		{	// 子表
			int curSubDepth = DepthHelp(p->hLink);	// 子表深度
			if (subMaxDepth < curSubDepth) subMaxDepth = curSubDepth;
		}
	}
	return subMaxDepth + 1;				// 广义表深度为子表最大深度加1
}

template <class ElemType>
int GenList<ElemType>::GetDepth()
// 操作结果：返回广义表深度
{
	return DepthHelp(head);
}

template <class ElemType>
int GenList<ElemType>::GetLength()
// 操作结果：返回广义表长度
{
	GenListNode<ElemType> *p = head->tLink;	// 临时变量 
	int length = 0;
	while (p) {
          p = p->tLink;
          length++;
    }
	return length;
}

template <class ElemType>
void GenList<ElemType>::ClearHelp(GenListNode<ElemType> *hd)
// 操作结果：释放以hd为表头的广义表结构
{
	hd->ref--;						// 引用数自减1
	
	if (hd->ref == 0)
	{	// 引用数为0,释放结点所占用空间
		GenListNode<ElemType> *pre = hd, *p;	// 临时变量 
		for (p = hd->tLink; p != NULL; p = p->tLink)
		{	// 扫描广义表hd的顶层
			delete pre;					// 释放pre
            pre = p;
			if (p->tag == LIST)			// p为子表
				ClearHelp(p->hLink);	// 释放子表
		}
		delete pre;						// 释放尾结点pre
	}
}

template <class ElemType>
GenList<ElemType>::~GenList()
// 操作结果：释放广义表结构——析构函数
{
	ClearHelp(head);
}

template <class ElemType>
void GenList<ElemType>::CopyHelp(const GenListNode<ElemType> *sourceHead, 
	GenListNode<ElemType> *&destHead)	
// 初始条件: 以sourceHead为头结点的广义表为非递归广义表
// 操作结果: 将以sourceHead为头结点的广义表复制成以destHead为头结点的广义表
{
	destHead = new GenListNode<ElemType>(HEAD);		// 复制头结点
	GenListNode<ElemType> *destPtr = destHead;		// destHead的当前结点
	destHead->ref = 1;								// 引用数为1
	for (GenListNode<ElemType> *p = sourceHead->tLink; p != NULL; 
		p = p->tLink)
	{	// 扫描广义表sourceHead的顶层
		destPtr = destPtr->tLink = new GenListNode<ElemType>(p->tag);	
			// 生成新结点
		if (p->tag == LIST)
		{	// 子表
			CopyHelp(p->hLink, destPtr->hLink);// 复制子表
		}
		else
		{	// 原子结点
			destPtr->atom = p->atom;				// 复制原子结点
		}
	}
}

template <class ElemType>
GenList<ElemType>::GenList(const GenList<ElemType> &g)
// 操作结果：由广义表g构造新广义表--复制构造函数
{
	CopyHelp(g.head, head);
}

template<class ElemType>
GenList<ElemType> &GenList<ElemType>::operator =(const GenList<ElemType> &g)
// 操作结果：将广义表g赋值给当前广义表--赋值语句重载
{
	if (&g != this)	{
		ClearHelp(head);			// 清空当前广义表
		CopyHelp(g.head, head);		// 复制广义表
	}
	return *this;
}

template<class ElemType>
void GenList<ElemType>::CreateHelp(GenListNode<ElemType> *&first)
// 操作结果：创建以first为头结点的广义表
{
	char ch = GetChar();			// 读入字符
	switch (ch)
	{
	case ')':						// 广义表建立完毕
		return;				
	case '(':						// 子表
		// 表头为子表
		first = new GenListNode<ElemType>(LIST);// 生成表结点
		
		GenListNode<ElemType> *subHead;	// 子表指针
		subHead = new GenListNode<ElemType>(HEAD);// 生成子表的头结点
		subHead->ref = 1;				// 引用数为1	
		first->hLink = subHead;			// subHead为子表
		CreateHelp(subHead->tLink);		// 递归建立子表
		
		ch = GetChar();					// 跳过','
		if (ch != ',') cin.putback(ch);	// 如不是','，则将ch回退到输入流
		CreateHelp(first->tLink);		// 建立广义表下一结点
		break;
	default:							// 原子
		// 表头为原子
		cin.putback(ch);				// 将ch回退到输入流
		ElemType amData;				// 原子结点数据
		cin >> amData;					// 输入原子结点数据
		first = new GenListNode<ElemType>(ATOM);// 生成原表结点
		first->atom = amData;			// 原子结点数据
		
		ch = GetChar();					// 跳过','
		if (ch != ',') cin.putback(ch);	// 如不是','，则将ch回退到输入流
		CreateHelp(first->tLink);		// 建立广义表下一结点
		break;
	}
}

template<class ElemType>
void GenList<ElemType>::Input(void)
// 操作结果：输入广义表
{
	ClearHelp(head);
	head = new GenListNode<ElemType>(HEAD);	// 生成广义表头结点
	head->ref = 1;							// 引用数为1
	
	GetChar();								// 读入第一个'('
//	cout <<"ss"<<endl;
	GenList<ElemType>::CreateHelp(head->tLink);
		// 创建以head->tLink为表头的广义表
}

#endif
