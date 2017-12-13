#include "LinkStack.h"	// 链栈类

struct Datatypes
{
     short int retAddr;    //模仿返回地址
     int nDisk;            //参数n
     char SourcePeg;       //参数A
     char AuxPeg;          //参数B
     char DestPeg;         //参数C
};

void SimuTowers(int n, char A, char B, char C)
{
     Datatypes  currArea;  //当前工作区
     LinkStack<Datatypes> s;//模拟系统运行时的堆栈
     char temp;
     short int i;

     //当前工作区初始化
     currArea.retAddr =1;
     currArea.nDisk =n;
     currArea.SourcePeg =A;
     currArea.AuxPeg =B;
     currArea.DestPeg =C;
     s.Push(currArea);      //当前工作区入栈
     //以下为模拟出口
start:
     if (currArea.nDisk==1){
        cout << "Move Disk 1 from Peg " << currArea.SourcePeg
             << " to Peg " << currArea.DestPeg << endl;
        i=currArea.retAddr;
        s.Pop(currArea);                //出栈恢复当前工作区
        switch(i)  {
           case 1: goto L1;
           case 2: goto L2;
           case 3: goto L3;
        }
     }

     //以下模拟递归自调用过程
     s.Push(currArea);                  //当前工作区入栈
     currArea.nDisk--;
     temp = currArea.AuxPeg;
     currArea. AuxPeg =currArea.DestPeg;
     currArea.DestPeg =temp;
     currArea.retAddr =2;
     goto start;

     //以下模拟返回第一次递归调用
L2:
     cout << "Move Disk " << currArea.nDisk << " from Peg "
          << currArea.SourcePeg << " to Peg "
          << currArea.DestPeg << endl;
     s.Push(currArea);                            //当前工作区入栈
     currArea.nDisk--;
     temp = currArea.SourcePeg;
     currArea.SourcePeg = currArea.AuxPeg;
     currArea.AuxPeg=temp;
     currArea.retAddr=3;
     goto start;

     //以下模拟返回第二次递归调用
L3:
     i = currArea.retAddr;
     s.Pop(currArea);         //出栈恢复当前工作区
     switch(i){
        case 1: goto L1;
        case 2: goto L2;
        case 3: goto L3;
     }
     //以下模拟返回主函数
L1:
     return;
}

int main(void)
{
    int n;
    cout << "请输入盘子数：";
    cin >> n; 
    SimuTowers(n,'A','B','C');
	system("PAUSE");  
	return 0;  
}


