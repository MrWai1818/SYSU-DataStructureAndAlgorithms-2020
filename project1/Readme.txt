一、项目名称：实现一元稀疏多项式计算的计算器
二、文件说明：
  该程序总共分成两个文件。
"Polynomial calculator.cpp"是存放类成员函数的实现的文件。
"function.h"是存放程序使用到的函数的声明的文件。
该文件包括表示多项式的类、显示菜单的函数、获取用户输入的多项式的函数、读取多项式的系数和次数的函数、显示已经保存的多项式、进行多项式加法运算的函数、进行多项式减法运算的函数、进行多项式乘法运算的函数、进行多项式赋值的函数。
三、子模块描述
ostream& operator<<(ostream &cout,term &t)//重载cout<< 

void multiply(term p1,term p2)//多项式的乘法 

void add(term p1,term p2)//多项式的加法 

void mus(term p1,term p2)//多项式减法 

void getValue(term p,int x)//多项式求值 

void isEqual(term p1,term p2)//判断多项式相等 

void derivation(term p)//多项式求导 

void setTerm(char name,term &p)//设置多项式的项 

void returnMenu()//返回菜单并清空屏幕 

void showMenu()//显示菜单选项

四、类设计描述
class term{//存放多项式的项 
friend void add(term p1,term p2);//友元函数多项式的项相加 
friend void mus(term p1,term p2);//友元函数多项式的项相减 
friend ostream& operator<<(ostream &cout,term &t);//cout<<重载为直接输出多项式 
public:
	int _count[100];//多项式的系数 
	int _index[100];//多项式的指数 
	int _size1;//多项式的系数个数 
	int _size2;//多项式的指数个数 
	char _name;//多项式名称 
	term(){//构造函数初始化多项式 
		_name='\0';
		_size1=0;
		_size2=0;
		_count[0]='\0';
		_index[0]='\0';
	}
	void setCount(int count){//输入多项式系数 
		_count[_size1++]=count;
	}
	void setIndex(int index){//输入多项式指数 
		_index[_size2++]=index;
	} 
	void setName(char name){//输入多项式名称 
		_name=name;
	}
};

五、实验环境
本实验基于Visual Studio Code平台开发


