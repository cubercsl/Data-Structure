#include "ShortestPathBellmanFord.h"	// 最短路径BellmanFord算法

int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		int infity = DEFAULT_INFINITY;
		char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', };
		int m[7][7] = {
			{infity,     60,     50,     50,  infity, infity,  infity},
			{infity, infity, infity, infity,     -10, infity,  infity},
			{infity,    -20, infity, infity,      10, infity,      70}, 
			{infity, infity,    -20, infity,  infity,    -10,  infity},
			{infity, infity, infity, infity,  infity, infity,      30},
			{infity, infity, infity, infity,  infity, infity,      30},
			{infity, infity, infity, infity,  infity, infity,  infity}
		};  
		int n = 7;

		AdjListDirNetwork<char, int> net(vexs, n);

		for (int u = 0; u < n; u++) {
			for (int v = n-1; v >=0; v--){
				if (m[u][v] != infity)
					net.InsertArc(u, v, m[u][v]);
			}
		}

		cout << "原网:" << endl;
		net.Display();					// 显示网net
		cout << endl;
		system("PAUSE");				// 调用库函数system()

		int dist[n], path[n], v0 = 0;
		ShortestPathBellmanFord(net, v0, path, dist);	//用BellmanFord算法求最短路径
		DisplayPathAndDist(net, v0, path, dist);		//显示最短路径 
		cout << endl;
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

