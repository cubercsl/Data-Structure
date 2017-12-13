#include "LinkStack.h"			// 链式栈类
int OperPrior(char op1, char op2)
// 操作结果：返回操作符op1和op2优先级比较结果 
{
   int prior;								// 优先级比较结果 
   switch (op1) {
      case '+' :
      case '-' : if (op2 == '+' || op2 == '-' || op2 == ')' || op2 == '#')
                    prior = 2;
                 else
                    prior = 1;
                 break;
      case '*' :
      case '/' :
      case '^' :  if (op2 == '^' || op2 == '(')
                     prior = 1;
	                else
                     prior = 2;
	                break;
      case '(' :  if (op2 == ')')
                     prior = 0;
                  else if (op2 == '#')
                     prior = -1;
	                else
                     prior = 1;
	                break;
      case ')' :  if (op2 == '(')
                     prior = -1;
	                else
                     prior = 2;
	                break;
      case '#' :  if (op2 == ')')
                     prior = -1;
	                else if (op2 == '#')
	                   prior = 3;
	                else   
                     prior = 1;
	                break;
  }                
	return prior;									// 返回优先级
}

double Operate(double first, char op, double second)
// 操作结果：执行运算first op second
{
   double result;
   switch (op) {
	    case '+' : result = first + second;			    // 加法运算
                 break;
	    case '-' : result = first - second;			    // 减法运算
                 break;
	    case '*' : result = first * second;			    // 乘法运算
                 break;
	    case '/' : if (second == 0)                 // 除法运算 
                    throw Error("除数不能为零!");	// 抛出异常
                 result = first / second;			  
                 break;
	    case '^' : result = pow(first, second);	    // 幂运算
	               break;
   }             
	 return result;									                // 返回运算结果 
}

bool IsOperator(char ch)
// 操作结果：判断ch是否为操作符 
{
   if (ch == '#' || ch == '(' || ch == '^' || ch == '*' ||
      ch == '/' || ch == '+' || ch== '-' || ch == ')')
      return true;
   else
      return false;
};

void PostfixExpressionCalculation ()
// 操作结果：后缀式的计算 
{
   LinkStack<double> opnd;						// 操作数栈
   char ch;							            // 临时字符
   double operand, first, second;			    // 操作数

   cout << "输入后缀表达式,以'#'号结束:";
   ch = GetChar();						        // 读入一个字符
   while (ch != '#') {	                        // 当前表达式还未运算结束, 继续运算
	  if (isdigit(ch) || ch == '.')		{	    // ch为一个操作数的第1个字符
         cin.putback(ch);			            // 将字符ch放回输入流
         cin >> operand;				        // 读入操作数
         opnd.Push(operand);			        // 操作数入栈 
	  }
	  else if(!IsOperator(ch) || ch == '(' || ch ==')') {// ch既不是操作数,也不属于操作符
           throw Error("表达式中有非法符号!");  // 抛出异常
	  }
	  else {	                                // ch为操作符
         if (opnd.Pop(second) == UNDER_FLOW)    // 取第二操作数 
            throw Error("缺少操作数!");	        // 取数失败，则抛出异常
         if (opnd.Pop(first) == UNDER_FLOW)     // 取第一操作数 
            throw Error("缺少操作数!");	        // 取数失败，抛出异常
		 opnd.Push(Operate(first, ch, second));	// 运算结果入opnd栈
	  }
	  ch = GetChar();			                // 读入新字符
   }
   if (opnd.Pop(operand) == UNDER_FLOW)
      throw Error("缺少操作数!");	            // 抛出异常
   if (!opnd.IsEmpty())
      throw Error("缺少操作符!");	            // 抛出异常
   cout << "表达式结果为：" << operand << endl;	// 显示表达式的值
};

void InfixInToPostfix()
// 操作结果：中缀式转换为后缀式 
{
   LinkStack<char>   optr;						// 操作符栈
   char ch;							            // 临时字符
   char priorChar;						        // 当前输入的前一个字符
   char op = '#';						        // 操作符栈的栈顶字符
   double operand;							    // 操作数 
   int operandCount = 0;                        // 操作数计数器 
   optr.Push('#');						        // 在操作符栈中加入一个'#'
   priorChar = '#';					            // 前一字符
   cout << "输入中缀表达式,以'#'号结束:";
   ch = GetChar();						        // 读入一个字符
   while (op != '#' || ch != '#') {	    // 当前表达式还未运算结束, 继续运算
      if (isdigit(ch) || ch == '.')		{	    // ch为一个操作数的第1个字符
	     if (priorChar == '0' || priorChar == ')')
            throw Error("两个操作数之间缺少运算符!");     // 抛出异常
         cin.putback(ch);			            // 将字符ch放回输入流
         cin >> operand;				        // 读入操作数
         cout << operand << "  ";			    // 输出操作数 
         operandCount++;                        // 操作数数目加1 
         priorChar = '0';			            // 前一字符是操作数
         ch = GetChar();				        // 读入下一个字符
	  }
	  else if(!IsOperator(ch)) {	            // 既不是操作数,也不是操作符
         throw Error("表达式中有非法符号!");    // 抛出异常
	  }
	  else {	// ch为操作符
         if (ch == '(' && (priorChar == '0' || priorChar == ')'))
            throw Error("'('前缺少操作符!");	// 抛出异常
         while (OperPrior(op, ch) == 2) {
            if (operandCount < 2)
               throw Error("缺少操作数!");
            operandCount--;
            optr.Pop(op);
            cout << op << "  ";
		    if (optr.Top(op) == UNDER_FLOW)
               throw Error("缺少操作符!");	    // 抛出异常
         }
		 switch (OperPrior(op, ch)) {
			case -1 : throw Error("括号不匹配!");	
			case 0  : optr.Pop(op);
                      if (optr.Top(op) == UNDER_FLOW) 
                         throw Error("缺少操作符!");  // 抛出异常
			          priorChar = ch;		    // 新的前一字符为(
			          ch = GetChar();			// 读入新字符
                      break;
            case 1  : optr.Push(ch);
			          op = ch;
			          priorChar = ch;		    // 新的前一字符为)
			          ch = GetChar();			// 读入新字符
                      break;
         }
	  }
   }
   if (operandCount != 1)
      throw Error("缺少操作数!");	                        // 抛出异常
   cout << endl;
};
