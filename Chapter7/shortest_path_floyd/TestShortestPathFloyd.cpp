#include "ShortestPathFloyd.h"		// 弗洛伊德算法

int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		int infity = DEFAULT_INFINITY;
		char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F'};
		int m[6][6] = {
			{infity,	  12,		  3,      infity,	   9,		 10},
			{    12,  infity,	 infity,          2,       6,    infity},
			{     3,  infity,    infity,          2,  infity,         6},
			{infity,       2,         2,     infity,       4,         7},
			{     9,       6,	 infity,          4,  infity,         4},
			{    10,  infity,         6,          7,       4,    infity}
		};
		int n = 6;

		AdjListDirNetwork<char, int> net(vexs, n);

		for (int u = 0; u < n; u++)
			for (int v = n-1; v >=0; v--)
				if (m[u][v] != infity) net.InsertArc(u, v, m[u][v]);

		cout << "原网:" << endl;
		net.Display();					// 显示网net
		cout << endl;
		system("PAUSE");				// 调用库函数system()

		int **dist, **path;
		// 分配存储空间
		dist = new int *[net.GetVexNum()], path = new int *[net.GetVexNum()];
		for (int i = 0; i < net.GetVexNum(); i++)	{	
			dist[i] = new int[net.GetVexNum()]; 
            path[i] = new int[net.GetVexNum()]; 
		}

		ShortestPathFloyd(net, path, dist);	// 用Floyd算法求最短路径
		DisplayPathAndDist(net, path, dist);// 显示最短路径 
		cout << endl << endl;

		// 释放存储空间
		for (int j = 0; j < net.GetVexNum(); j++)    {	
			delete []dist[j];
            delete []path[j]; 
		}
		delete []dist; delete []path;
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

