#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include "Assistance.h"			// 辅助软件包
#include "LinkList.h"			// 链表类
#include "PolyItem.h"			// 多项式项类


// 多项式类
class Polynomial
{
protected:
// 多项式实现的数据成员:
	LinkList<PolyItem> polyList;// 多项式组成的线性表

public:
	//  抽象数据类型方法声明及重载编译系统默认方法声明:
	Polynomial(){};				// 无参构造函数
	~Polynomial(){};			// 析构函数
	int Length() const;			// 求多项式的项数			 
	bool IsZero() const;		// 判断多项式是否为0
	void SetZero();				// 将多项式置为0
	void Display();				// 显示多项式
	void InsItem( const PolyItem &item);		// 插入一项
	Polynomial operator +(const Polynomial &p) const; // 加法运算符重载
	Polynomial(const Polynomial &copy);			// 复制构造函数
	Polynomial(const LinkList<PolyItem> &copyLinkList);				
		// 由多项式组成的线性表构造多项式
	Polynomial &operator =(const Polynomial &copy);	// 赋值语句重载
	Polynomial &operator =(const LinkList<PolyItem> &copyLinkList);	// 赋值语句重载
};


// 多项式类的实现部分

int Polynomial::Length() const
// 操作结果：返回多项式的项数
{
	return polyList.GetLength();
}

bool Polynomial::IsZero() const
// 操作结果：如多项式为0，则返回true，否则返回false
{
	return polyList.IsEmpty();
}

void Polynomial::SetZero()
// 操作结果：将多项式置为0
{
	polyList.Clear(); 
}

void Polynomial::Display()
// 操作结果：显示多项式
{
	int pos = 1;
	PolyItem it;
	Status status = polyList.GetElem(pos, it);
	while ( status == ENTRY_FOUND)	{// 依次显示多项式的每一项
	    if (pos > 1 && it.coef>0)
          cout<<"+";
        if ( it.coef != 1)
            if (it.coef !=-1)
               cout << it.coef;
            else 
               cout << "-";
        if (it.expn > 1)
           cout << "x^" << it.expn ; 
        else
           if (it.expn == 1)
               cout << "x"  ;
		status = polyList.GetElem(++pos, it);	// 取出下一项
	}
}

void Polynomial::InsItem( const PolyItem &item)
// 操作结果：向多项式插入一项
{
	int pos = 1;
	PolyItem it;
	Status status = polyList.GetElem(pos, it);
	while ( status == ENTRY_FOUND && it.expn > item.expn) 	// 查找插入位置
			status = polyList.GetElem(++pos, it);
	polyList.InsertElem(pos, item);					            // 向多项式插入一项
}

Polynomial Polynomial::operator +(const Polynomial &p) const
// 操作结果：返回当前多项式与p之和——加法运算符重载
{
	LinkList<PolyItem> la = polyList;			// 当前多项式对应的线性表
	LinkList<PolyItem> lb = p.polyList;			// 多项式p对应的线性表
	LinkList<PolyItem> lc;						// 和多项式对应的线性表
	int aPos = 1, bPos = 1;
	PolyItem aItem, bItem;
	Status aStatus, bStatus;
	
	aStatus = la.GetElem(aPos++, aItem);			// 取出la的第1项 
	bStatus = lb.GetElem(bPos++, bItem);			// 取出lb的第1项

	while (aStatus == ENTRY_FOUND && bStatus == ENTRY_FOUND )	{
		if (aItem.expn > bItem.expn) {		// la中的项aItem指数较小
			lc.InsertElem(aItem);	// 将aItem追加到lc的表尾 
			aStatus = la.GetElem(aPos++, aItem);// 取出la的第下一项
		}
		else if (aItem.expn < bItem.expn) {	// lb中的项bItem指数较小
			lc.InsertElem(bItem);	// 将bItem追加到lc的表尾
			bStatus = lb.GetElem(bPos++, bItem);// 取出lb的第下一项
		}
		else {	// la中的项aItem和lb中的项bItem指数相等
			PolyItem sumItem(aItem.coef + bItem.coef, aItem.expn);
			if (sumItem.coef != 0)
				lc.InsertElem(sumItem);	// 将两项的和追加到lc的表尾
			aStatus = la.GetElem(aPos++, aItem);// 取出la的第下一项
			bStatus = lb.GetElem(bPos++, bItem);// 取出lb的第下一项
		}
	}

	while (aStatus == ENTRY_FOUND) {	// 将la的剩余项追加到lc的后面
		lc.InsertElem(aItem);	// 将aItem追加到lc的后面
		aStatus = la.GetElem(aPos++, aItem);// 取出la的第下一项
	}

	while (bStatus == ENTRY_FOUND) {	// 将lb的剩余项追加到lc的后面
		lc.InsertElem(bItem);	// 将bItem追加到lc的后面
		bStatus = lb.GetElem(bPos++, bItem);// 取出lb的第下一项
	}

	Polynomial fc;							// 和多项式
	fc.polyList = lc;

	return fc;
}

Polynomial::Polynomial(const Polynomial &copy)
// 操作结果：由多项式copy构造新多项式——复制构造函数
{
	polyList = copy.polyList;
}

Polynomial::Polynomial(const LinkList<PolyItem> &copyLinkList)	
// 操作结果：由多项式组成的线性表构造多项式——转换构造函数
{
	polyList = copyLinkList;
}

Polynomial &Polynomial::operator =(const Polynomial &copy)	
// 操作结果：将多项式copy赋值给当前多项式——赋值语句重载
{
	if ( &copy != this)	{
		polyList = copy.polyList;
	}
	return *this;
}

Polynomial &Polynomial::operator =(const LinkList<PolyItem> &copyLinkList)
// 操作结果：将多项式组成的线性表copyLinkList赋值给当前多项式
//	——赋值语句重载
{
	polyList = copyLinkList;
	return *this;
}

#endif
