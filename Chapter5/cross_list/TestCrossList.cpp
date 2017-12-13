#include "CrossList.h"		// 稀疏矩阵的三元组顺序表

int main(void)
{
    try								// 用try封装可能出现异常的代码
	{
		const int rs = 6, cs=7;
		CrossList<int> a(rs, cs),d(rs,cs);	// 定义一个rs行cs列稀疏矩阵
		int m[rs][cs] = {
			 0,	 0,	11,	 0,	 0, 13,  0, 
			12,	 0,	 0,	 0,	 0,  0, 14, 
			 0,	-4,	 0,	 0,	 0, -8,  0, 
			 0,	 0,	 0,	 0,	 0,  0,  0,
			 0,	 0,	 0,	 0,	 0,  0,  0,
			 0, -8,  0,  0,  0,  0,  0
		};
		int i, j, v;

		// 设置稀疏矩阵a的元素值
		for (i = 0; i < rs; i++)
			for (j = 0; j < cs; j++)
				a.SetElem(i, j, m[i][j]);	// 设置元素值

		// 显示稀疏矩阵a
		cout << "显示矩阵a:" << endl; 
		for (i = 0; i < a.GetRows(); i++)  { 
			for (j = 0; j < a.GetCols(); j++)	{	// 列
				a.GetElem(i, j, v);		// 取元素值
				cout << v << "\t";		// 显示元素值
			}
			cout << endl;
		}
		cout << endl;

		cout << "显示矩阵a+a:" << endl; 
		CrossList<int> c(a);	
		c = a + c;
		for (i = 0; i < c.GetRows(); i++)  { 
		  for (j = 0; j < c.GetCols(); j++)	{	// 列
			c.GetElem(i, j, v);		// 取元素值
			cout << v << "\t";		// 显示元素值
		  }
	      cout << endl;
		}
	}
	catch (Error err)		// 捕捉并处理异常
	{
		err.Show();			// 显示异常信息
	}

  	system("PAUSE");        // 调用库函数system()
	return 0;               // 返回值0, 返回操作系统
}

