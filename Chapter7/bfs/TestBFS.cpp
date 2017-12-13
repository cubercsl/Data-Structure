#include "BFS.h"						// 图的广度优先遍历

int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F' ,'G', 'H', 'I'};
		int m[9][9] = {
			{0, 1, 0, 1, 1, 0, 0, 0, 0},
			{1, 0, 1, 0, 1, 0, 0, 0, 0},
			{0, 1, 0, 0, 1, 0, 0, 0, 0},
			{1, 0, 0, 0, 0, 0, 1, 0, 0},
			{1, 1, 1, 0, 0, 1, 1, 0, 0},
			{0, 0, 0, 0, 1, 0, 0, 0, 1},
			{0, 0, 0, 1, 1, 0, 0, 1, 0},
			{0, 0, 0, 0, 0, 0, 1, 0, 0},
			{0, 0, 0, 0, 0, 1, 0, 0, 0}
		};
		int n = 9;

		AdjMatrixUndirGraph<char> g(vexs, n);

		for (int u = 0; u < n; u++)
			for (int v = u; v < n; v++)
				if (m[u][v] == 1) g.InsertArc(u, v);

		cout << "原有图:" << endl;
		g.Display();
		cout << endl;
		system("PAUSE");

		cout << "广度优先遍历:";
		BFSTraverse(g, Write<char>);    // 对图g进行广度优先遍历 
		cout << endl;
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

