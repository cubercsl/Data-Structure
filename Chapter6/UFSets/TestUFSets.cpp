#include "UFSets.h"		            // 并查类

int main(void)
{
    try								// 用try封装可能出现异常的代码
	{
		const int n = 10;
		char c[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
		int a[] = {'a', 'g', 'i', 'c', 'a', 'h', 'f', 'f'};
		int b[] = {'b', 'd', 'j', 'b', 'c', 'i', 'e', 'd'};
		UFSets<char> e(c,n);
		int i;
		for (i = 0; i < 8; i++)
			e.Union(a[i], b[i]);	// 合并等价类
	
		bool out[n];				// 已输出的结点值为true，否则值为false

		for (i = 0; i < n; i++)
			out[i] = false;
		int p = 0;				// 当前结点
		while (p < n)		{	// 对没有输出的当前结点，输出其等价类
			cout << "{" << e.GetElem(p);
			out[p] = true;
			for (i = p + 1; i < n; i++)	{	// 输出等价类
				if (!e.Differ(e.GetElem(p), e.GetElem(i)))	{	// p与i在同一个等价类中
					cout << "," << e.GetElem(i);
					out[i] = true;
				}
			}
			cout << "}" << endl;
			while (p < n && out[p]) p++;
		}

	}
	catch (Error err)		// 捕捉并处理异常
	{
		err.Show();			// 显示异常信息
	}

	system("PAUSE");        // 调用库函数system()
	return 0;               // 返回值0, 返回操作系统
}


