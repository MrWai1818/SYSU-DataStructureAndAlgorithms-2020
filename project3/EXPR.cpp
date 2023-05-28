#include <iostream>
#include <cstring>
#include <cmath>
#include<string>
#include<vector>
#include<stack>
using namespace std;
class Node{ //结点类
public:
	Node* l;	//左孩子
	Node* r;	//右孩子	
	double value;	//结点为数值
	string op;	//结点为操作符
	string var;
	Node(){	//构造函数
		l = NULL;
		r = NULL;
		value=0;
		var=" ";
		op="#";
	}
};
int type[100];	//区分输入为操作符或数值
vector<string> ops(100);	//存操作符
vector<double> num(100);	//存操作数
vector<string> vari(100);		//存变量
int isvar=0; //判断表达式是否含参
Node* create(vector<string> put,Node *&tree,int len){//建树函数
	Node *treenode[100];
	for(int i=0;i<len;i++){
		treenode[i] =new Node;
	}
	int *iook=new int [100];
	for(int i=0;i<len;i++){		//判断是否为操作符或者操作数
		if(type[i]==1){
			iook[i]=1;
		}else if(type[i]==2){
			iook[i]=3;
		}else{
			iook[i]=0;
		}
	}
	if(len==1) treenode[0]->value=num[0];
	for(int i=len-1;i>=0;i--){
		if(iook[i]==0){	//如果为操作符，创建节点
			treenode[i]->op=ops[i];
			int nsnum=2;	//判断是否有左右结点，2为左子树赋值，1为右子树赋值
			if((ops[i]=="sin")||(ops[i]=="cos")||(ops[i]=="tan")||(ops[i]=="ln")||(ops[i]=="arcsin")||(ops[i]=="arccos")||(ops[i]=="arctan")||(ops[i]=="log")){
				nsnum=1;
			}
			for(int j=i+1;j<len;j++){
				if(iook[j]==3){
					if(nsnum==2){
						treenode[i]->l=treenode[j];
						treenode[j]->var=vari[j];
					}
					if(nsnum==1){
						treenode[i]->r=treenode[j];
						treenode[j]->var=vari[j];
					}
					iook[j]=0;
					nsnum--;
				}
				if(iook[j]==1){
					if(nsnum==2){
						treenode[i]->l=treenode[j];
						treenode[j]->value=num[j];
					}
					if(nsnum==1){
						treenode[i]->r=treenode[j];
						treenode[j]->value=num[j];
					}
					iook[j]=0;
					nsnum--;
				}
				if(iook[j]==2){
					if(nsnum==2) treenode[i]->l=treenode[j];
					if(nsnum==1) treenode[i]->r=treenode[j];
					iook[j]=0;
					nsnum--;
				}
				if(nsnum==0) j=len;
			}
			iook[i]=2;//将操作后的结点设置为当前节点
		}
	}
	tree =treenode[0];
    return tree;
}
int IsExist(Node *&p,string x){//查找是否有字符存在
	int ret=0;
	if(p->var==x){
			return 1;
	}
	if(IsExist(p->l,x)){
		return 1;
	}
	if(IsExist(p->r,x)){
		return 1;
	}
	return ret;
}
void findtype(vector<string> p, int len){//判断表达式中字符为操作数或变量或操作符
	for (int i = 0; i < len; i++) {
		if ((p[i][0] >= '0')&&(p[i][0] <= '9')) {
			num[i]=atof(p[i].c_str());
			type[i] = 1;
		}else if(((p[i][0] >= 'a')&&(p[i][0] <= 'z')&&(p[i].size()==1))||(((p[i][0]>= 'A')&&(p[i][0] <= 'Z'))&&(p[i].size()==1))){
			vari[i]=p[i][0];
			type[i] =2;
		}else{
			ops[i] = p[i];
			type[i] = 0;
		}
	}
}
void inOrd(Node *&p){//中序遍历输出并且带括号
	if(p!=NULL){
		int bra=0;
		if ((p->op == "+" )|| (p->op == "-")){
			cout << "(";
			bra++;
		}
		inOrd(p->l);
		if(p->var!=" "){
			cout<<p->var;
			isvar++;
		}
		if(p->value!=0){
			cout<<p->value;
		}
		if(p->op!="#"){
			cout<<p->op;
			if((p->op == "sin")|| (p->op == "cos")|| (p->op == "tan")|| (p->op == "arcsin")|| (p->op == "arccos")|| (p->op == "arctan")|| (p->op == "ln")||(p->op=="log")){
				cout << "(";
				bra++;
			}
			
		}		
		inOrd(p->r);
		if(bra){
			cout<<")";
			bra--;
		}
	}else{
		return;
	}
}
void clearTree(Node *&p){//清空树
	if(p!=NULL){	
		clearTree(p->l);
		clearTree(p->r);
		p=NULL;
	}
	if(p==NULL){
		return;
	}
}
double count(Node* p){//求值
	if(p==NULL){return 0;}
	if((p->l==NULL)&&(p->r==NULL)){return p->value;}
	double temp1=count(p->l);
	double temp2=count(p->r);
	if (p->op == "+")//做相应运算
		p->value = temp1 + temp2;//加
	else if (p->op == "-")
		p->value = temp1 - temp2;//减
	else if (p->op == "*")
		p->value = temp1 * temp2;//乘
	else if (p->op == "/")
		p->value = temp1 / temp2;//除
	else if (p->op == "^")
		p->value = pow(temp1,temp2);//幂
	else if (p->op == "sin")
		p->value = sin(temp2); 
	else if (p->op == "cos")
		p->value = cos(temp2);	
	else if (p->op == "tan")
		p->value = tan(temp2);
	else if (p->op == "arcsin")
		p->value = asin(temp2);
	else if (p->op == "arccos")
		p->value = acos(temp2);
	else if (p->op == "arctan")
		p->value = atan(temp2);
	else if (p->op == "ln")
		p->value = log(temp2);
	else if (p->op == "log")
		p->value = log10(temp2);
	else cout << "错误请重新输入表达式"<<endl;
	return p->value;
}
void Assign(Node *& p,string pv,double x){//赋值函数
	if(p!=NULL){
		Assign(p->l,pv,x);
		if(p->var==pv){
			p->value=x;
			isvar--;
		}
		Assign(p->r,pv,x);
	}
}
void Diff(Node *&p, string x){//求偏导函数
	if(p!=NULL){
		if(p->op=="+"){ //加法的偏导
			int temp=0; 
			if(p->l->var==x){cout<<"1";	temp=1;}
			if((p->l->op!="#")&&IsExist(p->l,x)){Diff(p->l,x);temp=1;}
			if(p->r->var==x){if(temp==1){cout<<"+";}cout<<"1";}
			if((p->r->op!="#")&&IsExist(p->r,x)){if(temp==1){cout<<"+";}Diff(p->r,x);}
		}
		if(p->op=="-"){ //减法的偏导
			int temp=0; 
			if(p->l->var==x){cout<<"1";	temp=1;}
			if((p->l->op!="#")&&IsExist(p->l,x)){Diff(p->l,x);temp=1;}
			if(p->r->var==x){if(temp==1){cout<<"-";}cout<<"1";}
			if((p->r->op!="#")&&IsExist(p->r,x)){if(temp==1){cout<<"-";}Diff(p->r,x);}
		}
		if(p->op=="*"){ //乘法的偏导
			if(p->l->var==x){
				if(p->r->var==x){//x*x
					cout<<"2*"<<x;
				}else if(p->r->op!="#"&&IsExist(p->r,x)){//x*f(x)
					inOrd(p->r);
					cout<<"+";
					if(p->r->op!="#"){
						cout<<"(";
					}
					Diff(p->r,x);
					if(p->r->op!="#"){
					cout<<")";
					}
					cout<<"*x";
				}else{//x*a
					inOrd(p->r);
				}
			}else if(p->l->op!="#"&&IsExist(p->l,x)){
				if(p->r->var==x){//f(x)*x
					inOrd(p->l);
					cout<<"+";
				if(p->l->op!="#"){
					cout<<"(";
				}
				Diff(p->l,x);
				if(p->l->op!="#"){
					cout<<")";
				}
				cout<<"*x";
				}else if(p->r->op!="#"&&IsExist(p->r,x)){//f(x)*f(x)
					cout<<"(";
					Diff(p->l,x);
					cout<<"*";
					inOrd(p->r);
					cout<<")+(";
					Diff(p->r,x);
					cout<<"*";
					inOrd(p->l);
					cout<<")";
				}else{//f(x)*a
					Diff(p->l,x);
					cout<<"*";
					if(p->r->op!="#"){
						cout<<"(";
					}
					inOrd(p->r);
					if(p->r->op!="#"){
						cout<<")";
					}
				}
		}else{
			if(p->r->var==x){//a*x
				inOrd(p->l);
			}else if(p->r->op!="#"&&IsExist(p->r,x)){//a*f(x)
				if(p->l->op!="#"){
					cout<<"(";
				}
				inOrd(p->l);
				if(p->l->op!="#"){
					cout<<")";
				}
				cout<<"*(";
				Diff(p->r,x);
				cout<<")";
			}else{//a*a
				cout<<0;
			}
		}
	}
		if(p->op=="/"){ //除法的偏导
			if(p->l->var==x){
				if(p->r->var==x){//x/x
					cout<<0;
				}else if(p->r->op!="#"&&IsExist(p->r,x)){//x/f(x)
					cout<<"(";
					inOrd(p->r);
					cout<<"-"<<x<<"*";
					if(p->r->op!="#"){
						cout<<"(";
					}
					Diff(p->r,x);
					if(p->r->op!="#"){
						cout<<")";
					}
					cout<<")/";
					cout<<"(";
					if(p->r->op!="#"){
						cout<<"(";
					}
					inOrd(p->r);
					if(p->r->op!="#"){
						cout<<")";
					}
					cout<<"^2)";	
				}else{//x/a
					cout<<"1/";
					if(p->r->op!="#"){
						cout<<"(";
					}
					inOrd(p->r);
					if(p->r->op!="#"){
						cout<<")";
					}
				}
			}else if(p->l->op!="#"&&IsExist(p->l,x)){
				if(p->r->var==x){//f(x)/x
					cout<<"(";
					if(p->l->op!="#"){
						cout<<"(";
					}
					Diff(p->l,x);
					if(p->l->op!="#"){
						cout<<")";
					}
					cout<<"*"<<x<<"-(";
					inOrd(p->l);
					cout<<"))";
					cout<<"/"<<x<<"^2";
				}else if(p->r->op!="#"&&IsExist(p->r,x)){//f(x)/f(x)
					cout<<"((";
					Diff(p->l,x);
					cout<<")*";
					if(p->r->op!="#"){
						cout<<"(";
					}
					inOrd(p->r);
					if(p->r->op!="#"){
						cout<<")";
					}
					cout<<"-";
					if(p->l->op!="#"){
						cout<<"(";
					}
					inOrd(p->l);
					if(p->l->op!="#"){
						cout<<")";
					}
					cout<<"*(";
					Diff(p->r,x);
					cout<<"))/(";
					inOrd(p->r);
					cout<<"^2)";
				}else{//f(x)/a
					cout<<"(";
					Diff(p->l,x);
					cout<<")/";
					if(p->r->op!="#"){
						cout<<"(";
					}
					inOrd(p->r);
					if(p->r->op!="#"){
						cout<<")";
					}
				}
			}else{
				if(p->r->var==x){//a/x
					cout<<"-";
					if(p->l->op!="#"){
						cout<<"(";
					}
					inOrd(p->l);
					if(p->l->op!="#"){
						cout<<"(";
					}
					cout<<"/"<<x<<"^2";
				}else if(p->r->op!="#"&&IsExist(p->r,x)){//a/f(x)
					cout<<"-";
					if(p->l->op!="#"){
						cout<<"(";
					}
					inOrd(p->l);
					if(p->l->op!="#"){
						cout<<"(";
					}
					cout<<"*(";
					Diff(p->r,x);
					cout<<")/";
					if(p->r->op!="#"){
						cout<<"(";
					}
					inOrd(p->r);
					if(p->r->op!="#"){
						cout<<")";
					}
					cout<<"^2";
				}else{//a/a
					cout<<0;
				}
			}
		}	
		if(p->op=="^"){ //幂的偏导
				if(p->l->var==x){
					if(p->r->var==x){//x^x
						
					}else if(p->r->op!="#"&&IsExist(p->r,x)){//x^f(x)
						
					}else{//x^a
						if(p->r->op!="#"){
							cout<<"(";
						}
						inOrd(p->r);
						if(p->r->op!="#"){
							cout<<")";
						}
						cout<<"*"<<x<<"^(";
						inOrd(p->r);
						cout<<"-1)";
					}
				}else if(p->l->op!="#"&&IsExist(p->l,x)){
					if(p->r->var==x){//f(x)^x
						
					}else if(p->r->op!="#"&&IsExist(p->r,x)){//f(x)^f(x)
						
					}else{//f(x)^a
						cout<<"(";
						Diff(p->l,x);
						cout<<")*";
						if(p->r->op!="#"){
							cout<<"(";
						}
						inOrd(p->r);
						if(p->r->op!="#"){
							cout<<")";
						}
						cout<<"*(";
						inOrd(p->r);
						cout<<")^(";
						inOrd(p->r);
						cout<<"-1)";
					}
				}else{
					if(p->r->var==x){//a^x
						if(p->l->op!="#"){
							cout<<"(";
						}
						inOrd(p->l);
						if(p->l->op!="#"){
							cout<<")";
						}
						cout<<"^"<<x<<"*ln";
						if(p->l->op!="#"){
							cout<<"(";
						}
						inOrd(p->l);
						if(p->l->op!="#"){
							cout<<")";
						}
					}else if(p->r->op!="#"&&IsExist(p->r,x)){//a^f(x)
						cout<<"(";
						Diff(p->r,x);
						cout<<")*";
						if(p->l->op!="#"){
							cout<<"(";
						}
						inOrd(p->l);
						if(p->l->op!="#"){
							cout<<")";
						}
						cout<<"^(";
						inOrd(p->r);
						cout<<")*ln";
						if(p->l->op!="#"){
							cout<<"(";
						}
						inOrd(p->l);
						if(p->l->op!="#"){
							cout<<")";
						}
					}else{//a^a
						cout<<0;
					}
				}
			}
		if(p->op=="sin"){//sin的偏导
				if(p->r->var==x){
					cout<<"cos";
					inOrd(p->r);
				}
				if(p->r->op!="#"&&IsExist(p->r,x)){
					cout<<"cos(";
					Diff(p->r,x);
					cout<<")";
				}
		}
		if(p->op=="cos"){//cos的偏导
			if(p->r->var==x){
				cout<<"-sin";
				inOrd(p->r);
			}
			if(p->r->op!="#"&&IsExist(p->r,x)){
				cout<<"-sin(";
				Diff(p->r,x);
				cout<<")";
			}
		}
		if(p->op=="tan"){//tan的偏导
			if(p->r->var==x){
				cout<<"1/(cos";
				inOrd(p->r);
				cout<<")^2";
			}
			if(p->r->op!="#"&&IsExist(p->r,x)){
				cout<<"(";
				Diff(p->r,x);
				cout<<")/(cos";
				inOrd(p->r);
				cout<<")^2";
			}
		}
		if(p->op=="arcsin"){//arcsin的偏导
			if(p->r->var==x){
				cout<<"1/(1-"<<x<<")^(1/2)";
			}
			if(p->r->op!="#"&&IsExist(p->r,x)){
				cout<<"1/(1-(";
				inOrd(p->r);
				cout<<"))^(1/2)";
				cout<<"*(";
				Diff(p->r,x);
				cout<<")";
			}
		}
		if(p->op=="arccos"){//arccos的偏导
			if(p->r->var==x){
				cout<<"-1/(1-"<<x<<"^2)^(1/2)";
			}
			if(p->r->op!="#"&&IsExist(p->r,x)){
				cout<<"-1/(1-(";
				inOrd(p->r);
				cout<<")^2)^(1/2)";
				cout<<"*(";
				Diff(p->r,x);
				cout<<")";
			}
		}
		if(p->op=="arctan"){//arctan的偏导
			if(p->r->var==x){
				cout<<"1/1+"<<x<<"^2";
			}
			if(p->r->op!="#"&&IsExist(p->r,x)){
				cout<<"1/1+(";
				inOrd(p->r);
				cout<<")^2";
				cout<<"*(";
				Diff(p->r,x);
				cout<<")";
			}
		}
	}
}
void MergeConst(Node *&p){//合并同类项函数
	if (p!=NULL){
		MergeConst(p->l);
		if(p->op!="#"){
			if((p->l->value!=0)&&(p->r->value!=0)){
				if (p->op == "+")
					p->value =p->l->value+p->r->value;//加
				else if (p->op == "-")
					p->value = p->l->value-p->r->value;//减
				else if (p->op == "*")
					p->value = p->l->value*p->r->value;//乘
				else if (p->op == "/")
					p->value = p->l->value/p->r->value;//除
				else if (p->op == "^")
					p->value = pow(p->l->value,p->r->value);//幂
				p->op="#";
				p->l=NULL;
				p->r=NULL;
			}else if((p->l==NULL)&&(p->r->value!=0)){
				if (p->op == "sin")
					p->value = sin(p->r->value); 
				else if (p->op == "cos")
					p->value = cos(p->r->value);	
				else if (p->op == "tan")
					p->value = tan(p->r->value);
				else if (p->op == "arcsin")
					p->value = asin(p->r->value);
				else if (p->op == "arccos")
					p->value = acos(p->r->value);
				else if (p->op == "arctan")
					p->value = atan(p->r->value);
				else if (p->op == "ln")
					p->value = log(p->r->value);
				else if (p->op == "log")
					p->value = log10(p->r->value);
				p->op="#";
				p->l=NULL;
				p->r=NULL;
			}
		}
		MergeConst(p->r);
	}else{
		return;
	}
}
Node *CompoundExpr(string link,Node *&p1,Node *&p2){//构成复合表达式
	Node *temp=new Node();
	temp->op=link;
	temp->l=p1;
	temp->r=p2;
	return temp;
}
void menu(){//菜单
	cout<<"#######***********************************************************#######"<<endl;
	cout<<"####      1.Assign(V,c)            对变量 V 的赋值                   ####"<<endl;
	cout<<"####      2.Value(E)               对表达式求值                      ####"<<endl;
	cout<<"####      3.CompoundExpr(P,E1,E2)  构成新复合表达式(E1)P(E2)         ####"<<endl;
	cout<<"####      4.Diff(E,V)              求表达式E对变量V的导数            ####"<<endl;
	cout<<"####      5.MergeConst(E)          合并表达式E中所有常数运算         ####"<<endl;
	cout<<"####      6.RereadExpr(E)          重新读取新的表达式                ####"<<endl;
	cout<<"####      7.EXIT                   退出程序                         ####"<<endl;
	cout<<"#######***********************************************************#######"<<endl;
}
int main(){
		string p,co;
		Node *tree=NULL;
		Node *temptree=NULL;
		vector<string> pv,pvtemp;
		Node *diffTree=new Node();
		string px;
		cout<<"#######***********************************************************#######"<<endl;
		cout<<"#######                   请输入将要读取的前缀表达式              #######"<<endl;
		cout<<"#######                    每输入一个单位打一次回车               #######"<<endl;
		cout<<"#######                   最后输入一次回车来结束操作              #######"<<endl;
		cout<<"#######***********************************************************#######"<<endl;
		getline(cin,p);
		while(p!=""){
			pv.push_back(p);
			getline(cin,p);
		}
		findtype(pv,pv.size());
		create(pv,tree,pv.size());
		cout<<"#######                           建树成功                        #######"<<endl;
		cout<<"#######                   该表达式带括号的中缀形式为              #######"<<endl;
		inOrd(tree);
		cout<<endl;
	cout<<"#######***********************************************************#######"<<endl;
	cout<<"#######                 请依照菜单输入数字来确定操作:             #######"<<endl;
	cout<<"#######***********************************************************#######"<<endl;
	menu();
	int operate=0;
	string tempop; //为CompoundExpr准备的链接符
	while (operate!=7){
		while(!(cin>>operate)){
			cin.clear();
			cin.sync();				  
		}
		if(operate<0){
			cout<<"未找到该指令"<<endl;
			cout<<"请重新输入"<<endl; 
		}
		switch (operate)
		{
		case 1:
			system("cls");
			if(isvar==0){
				cout<<"#######                    该表达式没有变量                         #######"<<endl;
				menu();
				break;
			}
			cout<<"#######              请输入将要赋值的变量名和对应值:                 #######"<<endl;
			while (isvar){	//变量赋值
				int t=isvar;
				string pvar;
				double px;
				cout<<"变量："<<endl;
				cin>>pvar;
				cout<<"赋值为："<<endl;
				cin>>px;
				Assign(tree,pvar,px);
				if (t==isvar){
					cout<<"#######                    该变量不存在                           #######"<<endl;
					cout<<"#######                    请重新输入                             #######"<<endl;
				}else{
					cout<<"#######                    赋值成功                               #######"<<endl;
				}	
			}
			menu();
			break;
		case 2:
			system("cls");
			if(isvar==0){ 
				cout<<"#######   	           表达式的值为：                       #######"<<endl;
				cout<<count(tree)<<endl;
			}else{ 
				cout<<"#######              表达式中仍有变量未赋值                       #######"<<endl;
				cout<<"#######              	请重新操作               		  #######"<<endl;
			}
			menu();
			break;
		case 3:
			system("cls");
			cout<<"#######                      ！！！请注意！！！                  #######"<<endl;
			cout<<"#######               合并后的各项操作均为合并后的表达式           #######"<<endl;
			cout<<"#######                   请输入将要合并的前缀表达式              #######"<<endl;
			cin.get();
			getline(cin,co);
			while(co!=""){
				pvtemp.push_back(co);
				getline(cin,co);
			}
			findtype(pvtemp,pvtemp.size());
			create(pvtemp,temptree,pvtemp.size());
			cout<<"#######                           建树成功                        #######"<<endl;
			cout<<"#######                   该表达式带括号的中缀形式为              #######"<<endl;
			inOrd(temptree);
			cout<<endl;
			cout<<"#######                   请输入将要用于合并的连接符              #######"<<endl;
			cin>>tempop;
			tree=CompoundExpr(tempop,tree,temptree);
			inOrd(tree);
			cout<<endl;
			menu();
			break;
		case 4:
			system("cls");
			diffTree=tree;
			cout<<"#######                       请输入将要求导的变量                #######"<<endl;
			cin>>px;
			cout<<"#######                   关于"<<px<<"的偏导结果为                #######"<<endl;
			Diff(diffTree,px);
			cout<<endl;
			menu();
			break;
		case 5:
			system("cls");
			MergeConst(tree);
			cout<<"#######                 合并后的表达式为:             #######"<<endl;
			inOrd(tree);
			cout<<endl;
			menu();
			break;
		case 6:
			system("cls");
			clearTree(tree);
			pv.clear();
			p.clear();
			for(int i;i<100;i++){
				type[i]=0;
			}
			num.clear();
			ops.clear();
			vari.clear();
			isvar=0;
			cout<<"#######***********************************************************#######"<<endl;
			cout<<"#######                   请输入将要读取的前缀表达式              #######"<<endl;
			cout<<"#######                    每输入一个单位打一次回车               #######"<<endl;
			cout<<"#######                   最后输入一次回车来结束操作              #######"<<endl;
			cout<<"#######***********************************************************#######"<<endl;
			cin.get(); 
			getline(cin,p);
			while(p!=""){
				pv.push_back(p);
				getline(cin,p);
			}
			findtype(pv,pv.size());
			create(pv,tree,pv.size());
			cout<<"#######                           建树成功                        #######"<<endl;
			cout<<"#######                   该表达式带括号的中缀形式为              #######"<<endl;
			inOrd(tree);
			cout<<endl;
			menu();
			break;
		default:
			break;
		} 
	}
	return 0;
}
