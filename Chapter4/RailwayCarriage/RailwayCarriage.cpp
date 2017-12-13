#include "SeqQueue.h"	// 循环队列类

int main(void)
{
    SeqQueue<int> qa;
    int n, x, d, No;
    
    cout << "输入车厢数："; 
    cin >> n;
    No = 1;        //  No表示排在主轨道左边最前面的车厢编号，初始值为1. 
    cout << "输入 " << n << " 节车厢的出站顺序："; 
    for (int i = 1; i <= n; i++){
        cin >> d;
        if (qa.GetHead(x) == SUCCESS && x == d) {
           cout << "第 " << x << " 号车厢从辅轨道进入主轨道右边." << endl;
           qa.DelQueue(x);
        }
        else if (No <= d) {
           while (No <= n && No < d) {
              cout << "第 " << No << " 号车厢从主轨道左边进入辅轨道." << endl;
              qa.EnQueue(No++);
           }
           if (No == d) {
              cout << "第 " << No << " 号车厢从主轨道左边进入主轨道右边." << endl;
              No++;
           }
        }
        else 
           break;
    }
    if (qa.IsEmpty())
        cout << "调度完成." << endl;
    else
        cout << "调度无法完成." << endl;

	system("PAUSE");
	return 0; 
}


