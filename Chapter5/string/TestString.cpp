#include "String.h"			// 串类

int main(void)
{
	String s1("It is a car.");
	String s2;
	char c = '1';
	int p,l;
	
	while (c != '0'){
        cout << endl << "1. 测试Insert()";
        cout << endl << "2. 测试Delete()";
        cout << endl << "3. 测试Copy()";
        cout << endl << "4. 测试关系运算符==";
        cout << endl << "5. 测试SubString()";
        cout << endl << "6. 测试下标运算符";
        cout << endl << "7. 测试连接运算符+";
        cout << endl << "8. 输入字符串1";
        cout << endl << "9. 输入字符串2";        
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~9):";
		cin >> c;
		switch (c) 	{
			case '1':
				cout << "字符串s1为：";
				Write(s1);
				cout << "字符串s2为：";
				Write(s2);
				cout << endl << "输入插入位置：";
				cin >> p;
				Insert(s1, s2, p);
				cout << endl << "插入结果为：";
				Write(s1);
				cout << endl;
				break;
	       case '2':
				cout << "字符串s1为：";
				Write(s1);
				cout << endl << "输入删除的起点位置和长度：";
				cin >> p >> l;
				Delete(s1, p, l);
				cout << endl << "删除结果为：";
				Write(s1);
				cout << endl;
				break;
		   case '3':
				cout << "字符串s1为：";
				Write(s1);
				cout << "字符串s2为：";
				Write(s2);
				Copy(s2 ,s1);
				cout << endl << "复制结果为：";
				Write(s2);
				cout << endl;
			    break;
           case '4':
				cout << "字符串s1为：";
				Write(s1);
				cout << "字符串s2为：";
				Write(s2);
				if (s1 == s2) 
       				cout << "s1和s2相等。"<< endl;
    			else 
       				cout << "s1和s2不相等。"<< endl;
			    break;
           case '5':
				cout << "字符串s1为：";
				Write(s1);
				cout << endl << "输入子串的起点位置和长度：";
				cin >> p >> l;
				s2 = SubString(s1, p, l);
				cout << endl << "取子串结果为：";
				Write(s2);
				cout << endl;
			    break;
          case '6':
				cout << "字符串s1为：";
				Write(s1);
				cout << endl << "输入字符下标：";
				cin >> p;
				cout << endl << "测试下标运算符结果为：" << endl;
				cout << s1[p] << endl;
			    break;
           case '7':
				cout << "字符串s1为：";
				Write(s1);
				cout << "字符串s2为：";
				Write(s2);
				s1 = s1 + s2;
				cout << endl << "字符串连接结果为：";
				Write(s1);
				cout << endl;
				break;
          case '8':
				cout << endl << "输入字符串1：";
				Read(s1);
			    break;
           case '9':
				cout << endl << "输入字符串2：";
				Read(s2);
				break;
		}
	}
	system("PAUSE");        // 调用库函数system()
	return 0;               // 返回值0, 返回操作系统
}
