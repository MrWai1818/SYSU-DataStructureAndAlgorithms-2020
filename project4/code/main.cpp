#include "widget.h"

#include <QApplication>
#include <QString>
#include <iostream>
#include <cstring>
#include <cmath>
#include<string>
#include<string>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
vector<int> step(1000,0);
struct  Graph{
    vector<vector<int>> adj; //图的邻接表
    vector<string> name;    //顶点名称
    vector<int> val;    // 权
    int vertex;// 顶点数
    int edge;//边数
    Graph(int n=0, int m=0):vertex(n), edge(m){
        adj.resize(n);
   }
};

template< class T >
class Stack{
    public:
        Stack():take(new T[capacity] ),size(0),capacity(1){};//构造函数
        Stack(const Stack&);//拷贝构造函数
        ~Stack();//析构函数
        Stack& operator=(const Stack&) ;//重载赋值运算符
        int Size() const;//返回栈中元素数目
        int Capacity() const;//返回当前栈的容量
        bool IsEmpty() const;//判断栈是否为空栈
        T& Top() const;//返回栈顶元素
        void Push(const T&);//将元素压入栈中，当元素数目超过栈的容量时重建栈
        void Pop();//弹出栈顶元素
    protected:
        int size;//栈中元素数目
        int capacity;//栈的容量
        void Expand();//扩充栈
        void Decrease();//压缩栈
    private:
        T* take;//保存栈中元素的数组
} ;

template< class T >
Stack<T>::Stack(const Stack<T> &s):take(new T[capacity]),size(s.size),capacity(s.capacity){
     for(int i=0;i<capacity;++i){
        take[i]=s.take[i];
    }
}

template< class T >
Stack< T >::~Stack(){
    delete [] take;
}

template< class T >
Stack< T >& Stack< T >::operator = (const Stack& s){
    take=new T[s.capacity];
    size=s.size;
    capacity=s.capacity;
    for(int i=0;i<capacity;++i){
        take[i]=s.take[i];
    }
}

template< class T >
int Stack< T >::Size() const{
    return size;
}

template< class T >
int Stack< T >::Capacity() const{
    return capacity;
}

template< class T >
bool Stack< T >::IsEmpty() const{
    if(size==0){
        return 1;
    }else{
        return 0;
    }
}

template< class T >
T& Stack< T >::Top() const{
    return take[size - 1];
}

template< class T >
void Stack< T >::Pop(){
    if(size == capacity/2)
        Decrease( );
        --size;
}

template< class T >
void Stack< T >::Push( const T& obj ){
    if( size == capacity )
        Expand();
        take[size++]=obj;
}

template< class T >
void Stack< T >::Expand(){
    capacity=4*capacity;
    T* temp= new T [capacity];
    for(int i = 0 ;i<size;i++){
        temp[i]=take[i];
    }
    delete [] take;
    take = temp;

}

template< class T >
void Stack< T >::Decrease(){
    capacity=capacity/4;
    T* temp= new T[ capacity ] ;
    for(int i = 0 ;i<size;++i){
        temp[i]=take[i];
    }
    delete [] take;
    take = temp;
}

struct node{
    int index;
    int value;
    string name;
    vector<node*> next;
    node(){
        index=-1;
        value=0;
    }
};
vector<node *> bftree(1000);
vector<node *> dftree(1000);
vector<vector<string>> bop;
vector<vector<string>> dop;
void botree(node *&p){
    vector<string> temp;
    temp.push_back(p->name);
    for(int i=0;i<p->next.size();i++){
        temp.push_back(p->next[i]->name);
    }
    bop.push_back(temp);
    for(int i=0;i<p->next.size();i++){
        botree(p->next[i]);
    }
}
void dotree(node *&p){
    vector<string> temp;
    temp.push_back(p->name);
    for(int i=0;i<p->next.size();i++){
        temp.push_back(p->next[i]->name);
    }
    dop.push_back(temp);
    for(int i=0;i<p->next.size();i++){
        dotree(p->next[i]);
    }
}
void dfs(Graph &p,int put){ //深度优先遍历
    Stack<int> temp;
    temp.Push(put);
    cout<<temp.Top();
    cout<<p.name[temp.Top()]<<" ";
    step[put]=1;
    while(!temp.IsEmpty()){
        int s=temp.Top();
        int sizeofs=p.adj[s].size();
        int i;
        for(i=0;i<sizeofs;i++){
            int t=p.adj[s][i];
            if(step[t]!=1){
                temp.Push(t);
                cout<<t;
                cout<<p.name[t]<<" ";
                step[t]=1;
                dftree[s]->next.push_back(dftree[t]);
                break;
            }
        }
        if(i==p.adj[s].size()){
            temp.Pop();
        }
    }
    for(int j=0;j<step.size();j++){ //最后将记录是否走过的数组置零
        step[j]=0;
    }
    cout<<endl;
    node *scantree=new node;    //建树并存入树的数组
    scantree=dftree[put];
    dotree(scantree);
}
void bfs(Graph &p,int put){ //广度优先遍历
    queue<int> temp;
    temp.push(put);
    step[put]=1;
    while(!temp.empty()){
        int t=temp.front();
        cout<<t;
        cout<<p.name[t]<<" ";
        temp.pop();
        for(int i=0;i<p.adj[t].size();i++){
            if(step[p.adj[t][i]]!=1){
                step[p.adj[t][i]]=1;
                temp.push(p.adj[t][i]);
                bftree[t]->next.push_back(bftree[p.adj[t][i]]);
            }
        }
    }
    for(int i=0;i<step.size();i++){ //最后将记录是否走过的数组置零
        step[i]=0;
    }
    cout<<endl;
    node *scantree=new node;    //建树并存入树的数组
    scantree=bftree[put];
    botree(scantree);
}
Graph makeGraph(int n,int s){  //建图的函数
    Graph temp(n,s);
    int count=s,na=n;
    for(int i=0;i<na;i++){
        string p;
        cin>>p;
        temp.name.push_back(p);
        bftree[i]=new node;
        bftree[i]->index=i;
        bftree[i]->name=p;
        dftree[i]=new node;
        dftree[i]->index=i;
        dftree[i]->name=p;
    }
    while(count--){
        int fa,son;
        cin>>fa>>son;
        temp.adj[fa].push_back(son);
        temp.adj[son].push_back(fa);
    }
    return temp;
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    Graph t(0,0);
    int pn=w.n;
    int ps=w.s;
    t=makeGraph(pn,ps);
    dftree.resize(pn);
    bftree.resize(pn);
    int first;
    first=w.fir;
    bfs(t,first);
    cout<<endl;
    dfs(t,first);
    cout<<endl;
    for(int i=0;i<bop.size();i++){ //将树的节点与临近子节点输到数组中
        vector<QString> ts;
        for(auto temp:bop[i]){
//            cout<<temp<<" ";
            QString tt = QString(QString::fromLocal8Bit(temp.c_str()));
            ts.push_back(tt);
        }
        w.qso.push_back(ts);
        cout<<endl;
    }

    for(int i=0;i<dop.size();i++){ //将树的节点与临近子节点输到数组中
        vector<QString> ts;
        for(auto temp:dop[i]){
//            cout<<temp<<" ";
            QString tt = QString(QString::fromLocal8Bit(temp.c_str()));
            ts.push_back(tt);
        }
        w.qso2.push_back(ts);
        cout<<endl;
    }
//    w.maketree(w.qso);
    w.remkt(w.qso);
    w.remkt2(w.qso2);
    w.show();
    return a.exec();
}
