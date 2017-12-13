#include "Kruskal.h"					// Kruskal算法

int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		int infity = DEFAULT_INFINITY;
		char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F'};
		int m[6][6] = {
			{infity, 34, 46, infity, infity, 19},
			{34, infity, infity, infity, 12, infity},
			{46, infity, infity, 17, infity, 25},
			{infity, infity, 17, infity, 38, 25},
			{infity, 12, infity, 38, infity, 26},
			{19, infity, 25, 25, 26, infity}
		};
		int n = 6;

		AdjMatrixUndirNetwork<char, int> net(vexs, n);

		for (int u = 0; u < n; u++)	// 生成邻接矩阵的行
			for (int v = u + 1; v < n; v++)	// 生成邻接矩阵元素的值
				if (m[u][v] != infity) net.InsertArc(u, v, m[u][v]);

		cout << "原网:" << endl;
		net.Display();					// 显示网net
		cout << endl;
		system("PAUSE");

		cout << "Kruskal算法产生最小生成树的边:" << endl;
		MiniSpanTreeKruskal(net);		// Kruskal算法
		cout << endl;
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

