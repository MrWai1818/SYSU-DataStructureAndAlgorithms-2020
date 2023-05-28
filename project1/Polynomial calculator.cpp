#include <string>
#include <fstream>
#include <vector>
#include "function.h"
int main(){
	term p0[100];//储存多项式 
	int cnt=0,a=0;//指标 
	double x;
	char name,name1,name2;//输入的名称 
	int id,j,index1=-1,index2=-1,i;//指标 
	int ch;//选择操作 
	while(ch!=9){
		returnMenu();
		showMenu();
		while(ch!=9){ 
			while(!(cin>>ch)){//防止输入非数字 
				cin.clear();
				cin.sync();
				cout <<"************************无效输入**********************" << endl;
				cout <<"***********************请重新输入**********************" << endl;
				returnMenu();
				showMenu();
			}if(ch<0){//防止输入非数字 
                cin.clear();
				cin.sync();			
				cout <<"************************无效输入**********************" << endl;
		        cout <<"***********************请重新输入**********************" << endl;
		        returnMenu();
		        showMenu();
			} 
			system("cls");
			cout <<"*******************************************************" << endl;
			switch (ch)
			{
				case 0://添加多项式
					cout<<"****                  添加多项式                   ****"<<endl; 
					cout<<"****         输入ba后按回车保存多项式及返回        ****"<<endl;
					cout<<"****            输入模板【p=(1,2)(3,4)】           ****"<<endl;
					cout<<"****               注意模板之中无空格              ****"<<endl;
					cout<<"****         若定义多项式重名则直接返回菜单        ****"<<endl;
					for(i=cnt;i<100;i++){
						cin>>name;
						for(j=0;j<100;j++){
							if(p0[j]._name==name){//判断是否重名 
								cout<<"****            该多项式已存在,请重新输入          ****"<<endl;
								a=1;
							}
						}
						if(a==1){
							a=0;
							break;
						} 	
						setTerm(name,p0[i]);
						cout<<p0[i]._name<<" = "<<p0[i];
						cout<<"\n";
						cnt++;
						if(p0[i]._name=='b'){//返回菜单设置
							p0[i]._name='\0';
							cin.clear();
							cin.sync();
							break;
						}
					}   
					returnMenu();
					showMenu();
					break;
				case 1://进行加法运算
					cout<<"****                 多项式加法运算                ****"<<endl;
					cout<<"****             输入ba后按回车即可返回            ****"<<endl;
					cout<<"****              请输入第一个多项式               ****"<<endl; 
					cin>>name1;
					cout<<"****              请输入第二个多项式               ****"<<endl;
					cin>>name2;
					for(id=0;id<100;id++){//在多项式数组中寻找所要的多项式 
						if(p0[id]._name==name1){
							index1=id;
							break;
						}
					}
					if(id==100){//多项式不存在 
						cout << "******          多项式"<<name1<<"不存在请重新输入          ******";
						cout<<"\n";
					}
					for(j=0;j<100;j++){//在多项式数组中寻找所要的多项式 
						if(p0[j]._name==name2){
							index2=j;		
							break;
						}
					}
					if(j==100){
						cout << "******          多项式"<<name2<<"不存在请重新输入          ******";
						cout<<"\n";
					}
					if((index1!=-1)&&(index2!=-1)){//找要的多项式，并进行操作 
						add(p0[index1],p0[index2]);
						index1=-1;index2=-1;
					} 
					if((name1=='b')&&(name2=='a')){
						returnMenu();//输出返回菜单的语句
					} 				
					showMenu();		
					break;	
				case 2:
					cout<<"****                 多项式减法运算                ****"<<endl;
					cout<<"****             输入ba后按回车即可返回            ****"<<endl;
					cout<<"****              请输入第一个多项式               ****"<<endl; 
					cin>>name1;
					cout<<"****              请输入第二个多项式               ****"<<endl;
					cin>>name2;
					for(id=0;id<100;id++){//在多项式数组中寻找所要的多项式 
						if(p0[id]._name==name1){
							index1=id;
							break;
						}
					}
					for(j=0;j<100;j++){//在多项式数组中寻找所要的多项式 
						if(p0[j]._name==name2){
							index2=j;		
							break;
						}
					}
					if(id==100){//多项式不存在
						cout << "******          多项式"<<name1<<"不存在请重新输入          ******";
						cout<<"\n";
					}
					if(j==100){
						cout << "******          多项式"<<name2<<"不存在请重新输入          ******";
						cout<<"\n";
					}
					if((index1!=-1)&&(index2!=-1)){//找到多项式并操作 
						mus(p0[index1],p0[index2]);
						index1=-1;index2=-1;
					} 
					if((name1=='b')&&(name2=='a')){
						returnMenu();//输出返回菜单的语句
					} 				
					showMenu();		
					break;	
				case 3:	
					cout<<"****                 多项式乘法运算                ****"<<endl;
					cout<<"****             输入ba后按回车即可返回            ****"<<endl;
					cout<<"****              请输入第一个多项式               ****"<<endl; 
					cin>>name1;
					cout<<"****              请输入第二个多项式               ****"<<endl;
					cin>>name2;
					for(id=0;id<100;id++){//在多项式数组中寻找所要的多项式 
						if(p0[id]._name==name1){
							index1=id;
							break;
						}
					}
					for(j=0;j<100;j++){//在多项式数组中寻找所要的多项式 
						if(p0[j]._name==name2){
							index2=j;		
							break;
						}
					}
					if(id==100){//多项式不存在 
						cout << "******          多项式"<<name1<<"不存在请重新输入          ******";
						cout<<"\n";
					}
					if(j==100){
						cout << "******          多项式"<<name2<<"不存在请重新输入          ******";
						cout<<"\n";
					}
					if((index1!=-1)&&(index2!=-1)){//找到多项式并操作 
						multiply(p0[index1],p0[index2]); 
						index1=-1;index2=-1;
					} 
					if((name1=='b')&&(name2=='a')){
						returnMenu();//输出返回菜单的语句
					} 				
					showMenu();		
					break;	
				case 4://多项式求值
					cout<<"****                 多项式求值运算                ****"<<endl;
					cout<<"****                请输入多项式名称               ****"<<endl;
					cout<<"****             输入ba后按回车即可返回            ****"<<endl;
					cin>>name1;
					for(id=0;id<100;id++){ //在多项式数组中寻找所要的多项式 
						if(p0[id]._name==name1){
							index1=id;
							break;
						}
					}
					if(id==100){//多项式不存在 
						cout << "******          多项式"<<name1<<"不存在请重新输入          ******";
						cout<<"\n";
						showMenu();
						break;
					}
					cout<<"请输入x的值";//赋值 
					cout<<"\n"; 
					while(!(cin>>x)){//防止输入非数字 
						cin.clear();
						cin.sync();
						cout<<"无效输入";
						cout<<"\n";
						cout<<"请重新输入";
						cout<<"\n";
						
					}
					getValue(p0[index1],x);
					showMenu();
					break;
				case 5://多项式相等 
					cout<<"****              判断两个多项式是否相等           ****"<<endl;
					cout<<"****             输入ba后按回车即可返回            ****"<<endl;
					cout<<"****              请输入第一个多项式               ****"<<endl; 
					cin>>name1;
					cout<<"****              请输入第二个多项式               ****"<<endl;
					cin>>name2;
					for(id=0;id<100;id++){//在多项式数组中寻找所要的多项式 
						if(p0[id]._name==name1){
							index1=id;
							break;
						}
					}
					for(j=0;j<100;j++){//在多项式数组中寻找所要的多项式 
						if(p0[j]._name==name2){
							index2=j;		
							break;
						}
					}
					if(id==100){//多项式不存在 
						cout << "******          多项式"<<name1<<"不存在请重新输入          ******";
						cout<<"\n";
					}
					if(j==100){
						cout << "******          多项式"<<name2<<"不存在请重新输入          ******";
						cout<<"\n";
					}
					if((index1!=-1)&&(index2!=-1)){//找到多项式并操作 
						isEqual(p0[index1],p0[index2]); 
						index1=-1;index2=-1;
					} 
					if((name1=='b')&&(name2=='a')){
						returnMenu();//输出返回菜单的语句
					} 				
					showMenu();		
					break;	
				case 6://显示多项式 
					cout<<"****                显示保存的多项式               ****"<<endl;
					cout<<"****             输入ba后按回车即可返回            ****"<<endl;
					for(id=0;id<cnt-1;id++){//输出多项式数组里的多项式 
						if((p0[id]._name)!='\0'){
							cout<<p0[id]._name<<" = "<<p0[id];
							cout<<"\n"; 
						}
					}
					cout<<"****              输入任意字符返回菜单             ****"<<endl;
					cin>>name1;
					returnMenu();//输出返回菜单的语句
					showMenu();
					break;
				case 7://多项式求导 
					cout<<"****                   多项式求导                  ****"<<endl;
					cout<<"****                请输入多项式名称               ****"<<endl;
					cout<<"****             输入ba后按回车即可返回            ****"<<endl;
					cin>>name1;
					for(id=0;id<100;id++){ //在多项式数组中寻找所要的多项式 
						if(p0[id]._name==name1){
							index1=id;
							break;
						}
					}
					if(id==100){
						cout << "******          多项式"<<name1<<"不存在请重新输入          ******";
						cout<<"\n";
						showMenu();
						break;
					}
					cout<<name1<<"的导数为";	
					derivation(p0[index1]);
					showMenu();
					break;		
				case 8://清空屏幕 
					cout<<"****              输入任意字符清空屏幕             ****"<<endl;
					cout<<"****           输入字符a清除保存的多项式           ****"<<endl; 
					cin>>name1;
					if(name1!='a'){
						system("cls");
					}else{
						for(i=0;i<100;i++){//清空保存的多项式 
							p0[i]._name='\0';
							p0[i]._size1=0;
							p0[i]._size2=0;
							p0[i]._count[0]='\0';
							p0[i]._index[0]='\0';
						}
						cout<<"****                     已清空                    ****"<<endl; 
						showMenu();
					}	
					break;
				case 9://结束程序 
					cout << "###                   *感谢使用*                    ###" << endl;
					cout << "*******************************************************" << endl;
					break;
				default://排错 
					cout << "###                     错误输入                    ###" << endl;
					cout << "###                请输入菜单中的选项               ###" << endl;
			}
		}
	}
	return 0;
}
