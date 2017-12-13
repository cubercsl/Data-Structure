#include "ShortestPathDij.h"			// 最短路径迪杰斯特拉算法

int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		int infity = DEFAULT_INFINITY;
		char vexs[] = {'A', 'B', 'C', 'D', 'E'};
		int m[5][5] = {
			{infity,     10, infity,     30,     100},
			{infity, infity,     50, infity,  infity},
			{infity, infity, infity, infity,      10}, 
			{infity, infity,     20, infity,      60},
			{infity, infity, infity, infity,  infity}
		};  
		int n = 5;

		AdjListDirNetwork<char, int> net(vexs, n);

		for (int u = 0; u < n; u++)
		{	// 生成邻接矩阵的行
			for (int v = n-1; v >=0; v--)
			{	// 生成邻接矩阵元素的值
				if (m[u][v] != infity) net.InsertArc(u, v, m[u][v]);
			}
		}

		cout << "原网:" << endl;
		net.Display();					// 显示网net
		cout << endl;
		system("PAUSE");				// 调用库函数system()

		int dist[n], path[n], v0 = 0;
		ShortestPathDij(net, v0, path, dist);		//用Dijskstra算法求最短路径
		DisplayPathAndDist(net, v0, path, dist);	//显示最短路径 
		cout << endl;
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

