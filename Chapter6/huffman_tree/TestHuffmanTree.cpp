#include "HuffmanTree.h"	// 哈夫曼树类

int main(void)
{
    try	{					// 用try封装可能出现异常的代码
		char ch[] = {'A', 'B', 'C', 'D'}; 
		int w[] = {12, 3, 5, 9};
		int n = 4, i;

		HuffmanTree<char, int> hmTree1(ch, w, n);
		HuffmanTree<char, int> hmTree(hmTree1);
		hmTree = hmTree1;			
		String strText = "ABCDADCBD";	// 文本串
		String strCode = "100111010011";		// 编码串

		cout << "各字符的编码为:" << endl;
		for (i = 0; i < n; i++)  {
			String strTmp = hmTree.Encode(ch[i]);
			cout << ch[i] << " : " << strTmp.CStr() << endl;
		}
		
		cout << "文本串" << strText.CStr() << "编码为:";
		for (i = 0; i < strText.GetLength(); i++)		{
			String strTmp = hmTree.Encode(strText[i]);
			cout << strTmp.CStr();
		}
		cout << endl;
		system("PAUSE");	
		cout << "编码串" << strCode.CStr() << "译码为:";
		LinkList<char> lkText = hmTree.Decode(strCode);
		strText = lkText;
		cout << strText.CStr() << endl;
	}
	catch (Error err)	{	// 捕捉并处理异常
		err.Show();			// 显示异常信息
	}

	system("PAUSE");  
	return 0;        
}
