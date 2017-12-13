#include "DFS.h"						// 图的深度优先遍历

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
		{	// 生成邻接矩阵的行
			for (int v = u; v < n; v++)
			{	// 生成邻接矩阵元素的值
				if (m[u][v] == 1) g.InsertArc(u, v);
			}
		}

		cout << "原有图:" << endl;
		g.Display();						// 显示图g
		cout << endl;
		system("PAUSE");				// 调用库函数system()

		cout << "深度优先遍历:";
		DFSTraverse<char>(g, Write<char>);// <char>用于确定函数模板参数
		cout << endl;
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

