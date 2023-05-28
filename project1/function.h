#include <fstream>
#include <iostream>
#include <vector>
#include<iomanip>
#include <cmath>
using namespace std;
class term{//多项式
	friend void add(term p1,term p2);//友元函数多项式的项相加 
	friend void mus(term p1,term p2);//友元函数多项式的项相减 
	friend ostream& operator<<(ostream &cout,term &t);//cout<<重载为直接输出多项式 
	public:
		double _count[100];//多项式的系数 
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
		void setCount(double count){//输入多项式系数 
			_count[_size1++]=count;
		}
		void setIndex(int index){//输入多项式指数 
			_index[_size2++]=index;
		} 
		void setName(char name){//输入多项式名称 
			_name=name;
		}
};
ostream& operator<<(ostream &cout,term &t){//重载cout<< 
    for(int i=0;i<t._size2;i++){
        if(t._count[i]!=0){
            if((t._count[i]==1)&&(t._index[i]!=1)&&(t._index[i]!=0)){//判断系数和指数为一为0输出的不同情况 
                cout<<"x^"<<t._index[i];
            }else if((t._index[i]==1)&&(t._count[i]==1)){
                cout<<"x";
            }else if((t._index[i]==0)){
                cout<<setiosflags(ios::fixed)<<setprecision(2);
                cout<<t._count[i];
            }else if((t._index[i]==1)&&(t._index[i]!=0)){
                cout<<setiosflags(ios::fixed)<<setprecision(2);
                cout<<t._count[i]<<"x";
            }else{
                cout<<setiosflags(ios::fixed)<<setprecision(2);
                cout<<t._count[i]<<"x^"<<t._index[i];
            }
            while(i<t._size2-1){
                cout<<" + ";
                break;
            }
        }
	}
}
void multiply(term p1,term p2){//多项式的乘法 
    int i,j,r=0,cnt=0,k;
    term temp;//临时对象存储乘积 
    temp._size2=p1._size2*p2._size2; 
    temp._size1=temp._size2;
    for(i=0;i<p2._size2;i++){//存入两个多项式乘积（未化简 
        for(j=0;j<p1._size2;j++){
            temp._count[r]=p1._count[j]*p2._count[i];
            temp._index[r++]=p1._index[j]+p2._index[i];
        }
    }
    for(k=0;k<temp._size2;k++){//合并同类项 
        for(j=k+1;j<temp._size2;j++){
            if(temp._index[j]==temp._index[k]){
                temp._count[k]=temp._count[k]+temp._count[j];
                    for(i=j;i<temp._size2;i++){
                        temp._count[i]=temp._count[i+1];
                    }
                cnt++;	
            }
        }
    }
    temp._size2=temp._size2-cnt;
    temp._size1=temp._size2;
    cnt=0;
    cout<<temp;
    cout<<"\n";
}
void add(term p1,term p2){//多项式的加法 
    int i,j=0,d;
    term temp0;//用临时的对象储存p1 
    if(p1._size2<=p2._size2){//输入的一个多项式的项数比第一个少 
        for(i=0;i<p1._size2;i++){
            temp0=p1;
        }
        for(i=0;i<p2._size2+1;i++){
            j=0;//判断如果指数相等则相加，否则指标j=1 
            for(d=0;d<p1._size2;d++){	
                if(temp0._index[d]==p2._index[i]){
                    temp0._count[d]=temp0._count[d]+p2._count[i];
                    j=1;
                }     
            }//如果指标j=0，则扩大临时对象容量，加入与p2不同的项 
            if(j==0){
                temp0._size2=temp0._size2+1;
                temp0._size1=temp0._size2;
                temp0._count[temp0._size1]=p2._count[i];
                temp0._index[temp0._size2]=p2._index[i];	
            } 
        }  
    }else{//输入的一个多项式的项数比第一个多 
        for(i=0;i<p2._size2;i++){
            temp0=p2;
        }
        for(i=0;i<p1._size2+1;i++){
            j=0;//判断如果指数相等则相加，否则指标j=1 
            for(d=0;d<p2._size2;d++){
                if(temp0._index[d]==p1._index[i]){
                    temp0._count[d]=temp0._count[d]+p1._count[i];
                    j=1;
                }   
            }
            if(j==0){
                temp0._size2=temp0._size2+1;
                temp0._size1=temp0._size2;
                temp0._count[temp0._size1]=p1._count[i];
                temp0._index[temp0._size2]=p1._index[i];	
            } 
        }  
    }   
    cout<<p1._name<<" + "<<p2._name<<" = "<<temp0;
    cout<<"\n";
}
void mus(term p1,term p2){//多项式减法 
    int i,j=0,d;
    term temp0;//做法同加法 
    for(i=0;i<p1._size2;i++){
        temp0=p1;
    }
    for(i=0;i<p2._size2+1;i++){
        j=0;
        for(d=0;d<p1._size2;d++){	
            if(temp0._index[d]==p2._index[i]){
                temp0._count[d]=temp0._count[d]-p2._count[i];
                j=1;   
            }      
        }
        if(j==0){
            temp0._size2=temp0._size2+1;
            temp0._size1=temp0._size2;
            temp0._count[temp0._size1]=p2._count[i]*-1;
            temp0._index[temp0._size2]=p2._index[i];	
        }
    }     
    cout<<p1._name<<" - "<<p2._name<<" = "<<temp0;
    cout<<"\n";
}
void getValue(term p,double x){//多项式求值 
	double value=0,y=1;
    int i;
	for(i=0;i<p._size2;i++){
		y=pow(x,p._index[i]);
		value=value+p._count[i]*y;
	}
    cout<<setiosflags(ios::fixed)<<setprecision(2);
	cout<<"当x ="<<x<<"时，多项式的值为"<<value;
	cout<<"\n";
}
void isEqual(term p1,term p2){//判断多项式相等 
    int i,cnt=0;
    if(p1._size2==p2._size1){//只有长度相同才需要考虑 
        for(i=0;i<p1._size2;i++){
            if((p1._count[i]==p2._count[i])&&(p1._index[i]==p2._index[i])){
                cnt++;
            }
        }
    }
    if(cnt==i){
        cout<<"多项式"<<p1._name<<"和"<<"多项式"<<p2._name<<"相等";
        cout<<"\n"; 
    }else{
        cout<<"多项式"<<p1._name<<"和"<<"多项式"<<p2._name<<"不相等";
        cout<<"\n"; 
    }
}
void derivation(term p){//多项式求导 
    int i;
    term temp; 
    temp._size2=p._size2;
    temp._size1=p._size1;
    for(i=0;i<p._size2;i++){
        temp._count[i]=p._count[i]*(p._index[i]);
        temp._index[i]=p._index[i]-1;
    }
    cout<<temp;
    cout<<"\n";
}
void setTerm(char name,term &p){//设置多项式的项 
    double c;
    int i,cnt=0;
    char p1,q,r;
    char a1; 
    cin>>a1; 
    p.setName(name);//设置多项式名称 
    if((name!='b')&&(a1!='a')){//判断结束条件 
        while((cin>>p1>>c>>q>>i>>r)){//在结束前输入任意个项 
            p.setCount(c);
            p.setIndex(i);
            if(cin.get()=='\n'){//结束单个项的赋值 
                break;
            }else{
                cin.putback(r);
            }
        }
    } 
    for(int k=0;k<p._size2;k++){//合并同类项 
        for(int j=k+1;j<p._size2;j++){
            if(p._index[j]==p._index[k]){
                p._count[k]=p._count[k]+p._count[j];
                for(int z=j;z<p._size2;z++){
                    p._count[z]=p._count[z+1];
                }
                cnt++;	
            }
        }
    }
    for(int k=0;k<p._size2;k++){//将多项式进行降序排列 
        for(int j=0;j<p._size2;j++){
            if(p._index[j+1]>p._index[j]){
                int temp1=p._index[j];
                double temp2=p._count[j];
                p._index[j]=p._index[j+1];
                p._index[j+1]=temp1;
                p._count[j]=p._count[j+1];
                p._count[j+1]=temp2;
            }
        }
    }
    p._size2=p._size2-cnt;
    p._size1=p._size2;
    cnt=0;  
}
void returnMenu()//返回菜单并清空屏幕 
{
    system("cls");
    cout << "*******************************************************" << endl;
    cout << "##                一元多项式简易计算器               ##" << endl;
}
void showMenu()//显示菜单选项
{
	cout << "*******************************************************" << endl;
	cout << "##***          输入选项对应数字以进行操作         ***##" << endl;
	cout << "                    0: 添加多项式                      "<< endl;
	cout << "                    1: 多项式加法运算                  " << endl;
	cout << "                    2: 多项式减法运算                  " << endl;
	cout << "                    3: 多项式乘法运算                  " << endl;
	cout << "                    4: 多项式求值运算                  " << endl;
	cout << "                    5: 判断两个多项式是否相等          " << endl;
	cout << "                    6: 显示保存的多项式                " << endl;
	cout << "                    7: 多项式求导                      " << endl;
	cout << "                    8: 清空屏幕或清空保存的多项式      " << endl;
	cout << "                    9: 结束程序                        " << endl;
	cout << "##***          #**#**#**#**#**#**#**#**#         ***##" << endl;
	cout << "*******************************************************" << endl;
}

