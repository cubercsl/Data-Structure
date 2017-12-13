#ifndef __Brute_Force_H__
#define __Brute_Force_H__

#include "String.h"				// 串类

int BF_find(const String &ob, const String &pat, const int p = 0)
// 操作结果: 查找模式串pat在目标串ob中从位置p开始的子串。如果找到则返回第一次出现的位置，否则返回-1。 
{
	int i = p, j = 0;
	while (i < ob.GetLength() && j < pat.GetLength()
        && pat.GetLength() - j <= ob.GetLength() - i)		
		if (ob[i] == pat[j])	{	// 继续比较后续字符
			i++; j++;
		}
		else	{	                // 指针回退,重新开始新的匹配
			i = i - j + 1; j = 0;
		}

	if (j >= pat.GetLength()) return i - j;// 匹配成功
	else return -1;						// 匹配失败
}

#endif

