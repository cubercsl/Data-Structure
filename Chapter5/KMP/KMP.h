#ifndef __KMP_H__
#define __KMP_H__

#include "String.h"				// 串类

// KMP匹配算法
void GetFailure(const String &pat, int f[])
// 操作结果: 求模式串pat的失效函数值
{
	f[0]=-1;				             // 初始f[0]的值为-1
	int j = 0, k = -1;		
	while (j < pat.GetLength() - 1)
		if (k == -1 || pat[k] == pat[j])	
			f[++j]=++k;
		else		                     // pat[k]与pat[j]不匹配
			k = f[k];		             // 寻求新的匹配字符
}


int KMP_find(const String &ob, const String &pat, int p = 0)
// 操作结果: 查找模式串pat第一次在目标串ob中从第p个字符开始出现的位置
{
	int *f = new int[pat.GetLength()];      // 为失效函数值数组f分配空间
	GetFailure(pat, f);				     // 求模式串pat的f数组的元素值
	int i = p, j = 0;			
	while (i < ob.GetLength() && j < pat.GetLength() && pat.GetLength() - j <= ob.GetLength() - i)
    if (j == -1 || pat[j] == ob[i])		{
		i++; j++;			             // 模式串pat与目标串ob的当前位置向后移
    }
	else	                             // pat[j]与ob[i]不匹配
		j = f[j];		                 // 寻找新的模式串pat的匹配字符位置
    delete []f;				             // 释f所占用的存储空间
	if (j < pat.GetLength())
        return -1;		                 // 匹配失败
	else
        return i - j;			         // 匹配成功
}
#endif

