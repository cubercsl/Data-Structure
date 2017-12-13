#include "BinaryAvlTree.h"				// 二叉平衡树类

int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		BinaryAVLTree<int> bt;
		int elem[] = {11, 39, 23, 68, 85, 8, 3, 46, 27, 50};
		int n = 10;
		
		cout << "从空树开始依次插入元素{11, 39, 23, 68, 85, 8, 3, 46, 27, 50}，构造二叉平衡树。" << endl;		
		for (int i = 0; i < n; i++) {
			cout << "插入第" << i + 1 << "元素" << elem[i] << endl; 
			bt.Insert(elem[i]);			// 插入结点
            DisplayBTWithTreeShape(bt);
		    cout << endl;
		    system("PAUSE");				// 调用库函数system()
        }

		cout << "构造的二叉平衡树，括号内的数字为结点的平衡因子:" << endl;
		DisplayBTWithTreeShape(bt);
		cout << endl;
		system("PAUSE");				// 调用库函数system()
 
		cout << "结点数:" << bt.NodeCount();
		cout << endl;
		system("PAUSE");				// 调用库函数system()

		cout << "先序遍历:" << endl;
		bt.PreOrder(Write<int>);
		cout<<endl;
		system("PAUSE");				// 调用库函数system()

		cout << "中序遍历:" << endl;
		bt.InOrder(Write<int>);
		cout<<endl;
		system("PAUSE");				// 调用库函数system()

		cout << "后序遍历:" << endl;
		bt.PostOrder(Write<int>);
		cout<<endl;
		system("PAUSE");				// 调用库函数system()

		cout << "层次遍历:" << endl;
		bt.LevelOrder(Write<int>);
		cout<<endl;
		system("PAUSE");				// 调用库函数system()

		bt.Insert(25);					
		cout << "插入数据元素25后:" << endl;
		DisplayBTWithTreeShape(bt);
		cout << endl;
		system("PAUSE");				// 调用库函数system()

		bt.Delete(23);					
		cout << "删除数据元素23后:" << endl;
		DisplayBTWithTreeShape(bt);
		cout << endl;
		system("PAUSE");				// 调用库函数system()

		bt.Delete(8);					
		cout << "删除数据元素8后:" << endl;
		DisplayBTWithTreeShape(bt);
		cout << endl;
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

