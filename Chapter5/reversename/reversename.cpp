#include <cstring>					// 标准串操作
#include <iostream>					// 标准流操作
#include <cassert>					// 支持断言
using namespace std;				// 标准库包含在命名空间std中


void reversename(char *name , char *newname)
{
    char *p;
    p = strchr(name , ' ');       //p指在空格' '位置
    *p = '\0';                    //把空格换为串结束符，因此name的长度只包括名
    strcpy(newname , p+1);        //p+1是name姓，因此newname等于name的姓
    strcat(newname , ",");        //newname等于姓加逗号
    strcat(newname , name);       //newname等于姓加逗号加名
    *p = ' ';                     //恢复name为开始时的状态
    return;
}

int main()
{
    char name[30], newname[30];
    cout << "输入一个人姓名：名在前，姓在后，中间有一个空格分隔。" << endl; 
    cin.getline(name,30,'\n');    //读入长度不超过30的字符串name
    reversename(name , newname);
    cout << "reversename:" << newname << endl;

	system("PAUSE");             
	return 0;               
}
