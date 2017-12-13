#include "InThreadBinaryTree.h"		  // 中序线索二叉树类

int main(void)
{
	char pre[]={'A','B','D','E','G','C','F'};		// 先序序列
	char in[]={'D','B','G','E','A','C','F'};		// 中序序列
	int n = 7;						  // 结点个数
	BinaryTree<char> bt;
	char c = 'x', e;
	ThreadBinTreeNode<char> *p;


	bt = CreateBinaryTree(pre, in, n);// 构造二叉树
	cout << "由先序：A,B,D,E,G,C,F和中序：D,B,G,E,A,C,F构造的二叉树:" << endl;
	DisplayBTWithTreeShape<char>(bt);
	cout << endl;
	system("PAUSE");	

	cout << "中序索化后的线索二叉树:" << endl;
	InThreadBinTree<char> thrBt(bt);
	DisplayBTWithTreeShape<char>(thrBt);
	system("PAUSE");	
	
   	while (c != '0'){
        cout << endl << "1. 插入右孩子.";
        cout << endl << "2. 删除左子树.";
        cout << endl << "3. 中序遍历.";
        cout << endl << "4. 显示二叉树.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~4):";
		cin >> c;
		switch (c) 	{
		    case '1':
            	cout << endl << "输入被插入元素的值:";
			    cin >> e;
			    p = thrBt.Find(e);
			    if (p == NULL)
			    	cout << "该结点不存在！" << endl;
			    else {
            		cout << endl << "输入插入元素的值:";
			    	cin >> e;
					thrBt.InsertRightChild(p, e);	// 插入左孩子
			    }
			    break;
           	case '2':
            	cout << endl << "输入删除子树双亲元素的值:";
			    cin >> e;
			    p = thrBt.Find(e);
			    if (p == NULL)
			    	cout << "该结点不存在！" << endl;
			    else 
					thrBt.DeleteLeftChild(p);					
			    break;
	         case '3':
				cout << endl;
				thrBt.InOrder(Write<char>);
				break;
	         case '4':
				cout << endl;
				DisplayBTWithTreeShape(thrBt);
				break;
		}
	}
	
	system("PAUSE");	
	return 0;				
}

