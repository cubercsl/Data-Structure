#include "Brute-Force.h"

int main(void)
{	// 测式简单字符串模式匹配算法
	String ob("this is a string");
	String pat("is");
	cout << "主串为：" ;
	Write(ob);
	cout << "子串为：" ;
	Write(pat);
	
	cout << endl << "从主串开始位置（第0个字符）查找模式串：" ;
	cout << BF_find(ob, pat) << endl;

	cout << endl << "从主串第3个字符开始查找模式串：" ;
	cout << BF_find(ob, pat, 3) << endl;

	pat="string";
	cout << endl << "改模式串为string，从主串开始位置查找模式串：" ;
	cout << BF_find(ob, pat) << endl;
	
	pat="this";
	cout << endl << "改模式串为this，从主串开始位置查找模式串：" ;
	cout << BF_find(ob, pat) << endl;

	cout << endl << "改模式串为this，从主串第3个字符开始查找模式串：" ;
	cout << BF_find(ob, pat, 3) << endl;

	pat="that";
	cout << endl << "改模式串为that，从主串开始位置查找模式串：" ;
	cout << BF_find(ob, pat) << endl;

	pat="this is a string!";
	cout << endl << "改模式串为this is a string!，从主串开始位置查找模式串：" ;
	cout << BF_find(ob, pat) << endl;

	pat=ob;
	cout << endl << "改模式串为this is a string，从主串开始位置查找模式串：" ;
	cout << BF_find(ob, pat) << endl;

	system("PAUSE");        // 调用库函数system()
	return 0;               // 返回值0, 返回操作系统
}

