#ifndef __ASSISTANCE_H__				// 如果没有定义__ASSISTANCE_H__
#define __ASSISTANCE_H__				// 那么定义__ASSISTANCE_H__

// 辅助软件包

#ifdef _MSC_VER						// 表示是VC 
#if _MSC_VER == 1200				// 表示VC6.0

// 标准库头文件
#include <string.h>					// 标准串和操作
#include <iostream.h>				// 标准流操作
#include <limits.h>					// 极限
#include <math.h>					// 数学函数
#include <fstream.h>				// 文件输入输出
#include <ctype.h>				 	// 字符处理
#include <time.h>				 	// 日期和时间函数
#include <stdlib.h>					// 标准库
#include <stdio.h>					// 标准输入输出
#include <iomanip.h>				// 输入输出流格式设置	
#include <stdarg.h> 				// 支持变长函数参数	
#include <assert.h>					// 支持断言

#else								// 其它版本的VC++

// ANSI C++标准库头文件
#include <string>					// 标准串和操作
#include <iostream>					// 标准流操作
#include <limits>					// 极限
#include <cmath>					// 数学函数
#include <fstream>					// 文件输入输出
#include <cctype>					// 字符处理
#include <ctime>       				// 日期和时间函数
#include <cstdlib>					// 标准库
#include <cstdio>       			// 标准输入输出
#include <iomanip>					// 输入输出流格式设置	
#include <cstdarg> 					// 支持变长函数参数	
#include <cassert>					// 支持断言
using namespace std;				// 标准库包含在命名空间std中

#endif	// _MSC_VER == 1200
#else								// 非VC 

// ANSI C++标准库头文件
#include <string>					// 标准串操作
#include <iostream>					// 标准流操作
#include <limits>					// 极限
#include <cmath>					// 数据函数
#include <fstream>					// 文件输入输出
#include <cctype>					// 字符处理
#include <ctime>       				// 日期和时间函数
#include <cstdlib>					// 标准库
#include <cstdio>       			// 标准输入输出
#include <iomanip>					// 输入输出流格式设置	
#include <cstdarg> 					// 支持变长函数参数	
#include <cassert>					// 支持断言
using namespace std;				// 标准库包含在命名空间std中

#endif	// _MSC_VER



// 自定义类型
enum Status {SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW,RANGE_ERROR, DUPLICATE_ERROR,
	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED};

// 宏定义
#define DEFAULT_SIZE 1000			// 缺省元素个数
#define DEFAULT_INFINITY 1000000	// 缺省无穷大


// 辅助函数的声明
template <class ElemType >
void Swap(ElemType &e1, ElemType &e2);	// 交换e1, e2之值
template<class ElemType>
void Display(ElemType elem[], int n);	// 显示数组elem的各数据元素值
template <class ElemType>
void Write(const ElemType &e);			// 显示数据元素


// 辅助函数的实现 
template <class ElemType >
void Swap(ElemType &e1, ElemType &e2)
// 操作结果: 交换e1, e2之值
{
	ElemType temp;		// 临时变量
	// 循环赋值实现交换e1, e2
	temp = e1;	e1 = e2;  e2 = temp;
}

template<class ElemType>
void Display(ElemType elem[], int n)
// 操作结果: 显示数组elem的各数据元素值
{
	for (int i = 0; i < n; i++)	// 显示数组elem
		cout << elem[i] << "  ";
	cout << endl; 
}

template <class ElemType>
void Write(const ElemType &e)
// 操作结果: 显示数据元素
{
    cout << e << "  ";
}

#endif
