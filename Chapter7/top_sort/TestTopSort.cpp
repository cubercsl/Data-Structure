#include "TopSort.h"					// 拓扑排序算法

int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F'};
		int m[6][6] = {
			{0, 0, 0, 0, 0, 0},
			{1, 0, 0, 1, 0, 0},
			{1, 0, 0, 1, 0, 0},
			{1, 0, 0, 0, 0, 1},
			{0, 0, 1, 1, 0, 1},
			{0, 0, 0, 0, 0, 0}
		};
		int n = 6;

		AdjListDirGraph<char> g(vexs, n);

		for (int u = 0; u < n; u++)
		{	// 生成邻接矩阵的行
			for (int v = 0; v < n; v++)
			{	// 生成邻接矩阵元素的值
				if (m[u][v] == 1) g.InsertArc(u, v);
			}
		}

		cout << "原图:" << endl;
		g.Display();						// 显示图g
		cout << endl;
		system("PAUSE");				// 调用库函数system()

		cout << "拓扑排序:";
		if (TopSort(g) == SUCCESS)
		{	// 拓扑排序成功
			cout << endl << "原图无环!" << endl;
		}
		else
		{	// 拓扑排序失败
			cout << endl << "原图存在环!" << endl;
		}
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

