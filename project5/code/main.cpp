#include "widget.h"

#include <QApplication>
#include<QString>

#include<iostream>
#include<vector>
#include<map>
#include<string.h>
using namespace std;
struct Hash
{
    int key;
    string name;
    int st;
    Hash(){
        key=-1;
        name="";
        st=0;
    }
};

vector<Hash> myHash(50);
vector<pair<string,int>> nametp;
void putName(){
    for(int i=0;i<30;i++){
        string pname;
        int pkey=0;
        cin>>pname;
        for(auto t:pname){
            pkey+=toascii(t);
        }
        nametp.push_back({pname,pkey});
    }
}
vector<QString> randm;
int rst[50];
int RandMkHash(int pkey,string pnam){
    int H=pkey%47;
    if(myHash[H].key==-1){
        myHash[H].key=pkey;
        myHash[H].name=pnam;
        myHash[H].st++;
        randm.push_back("Final Address : "+QString::number(H,10,0)+" Name : "+QString(QString::fromLocal8Bit(pnam.c_str())));
        return 1;
    }else{
        int cnt=0;
        QString temp="";
        for(int i=0;i<50;i++){
            int Hi=(pkey+rand()%30)%47;
            cnt++;
            if(myHash[Hi].key==-1){
                myHash[Hi].key=pkey;
                myHash[Hi].name=pnam;
                myHash[Hi].st=cnt;
                temp+="Final Address : "+QString::number(Hi,10,0)+" Name : "+QString(QString::fromLocal8Bit(pnam.c_str()));
                randm.push_back(temp);
                return 1;
            }else{
                temp+="Conflict with : "+QString::number(Hi,10,0)+" "+QString(QString::fromLocal8Bit(myHash[Hi].name.c_str())+"\n");
            }
        }
    }
    return 0;
}
double ASLcnt(double p){
    for(int i=0;i<50;i++){
        if(myHash[i].key!=-1){
            p+=myHash[i].st;
        }
    }
    p=p/30;
    return p;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    putName();

    for(int i=0;i<30;i++){
        RandMkHash(nametp[i].second,nametp[i].first);
    }
    for(int i=0;i<50;i++){
        w.randhash[i]=QString(QString::fromLocal8Bit(myHash[i].name.c_str()));
        w.randst[i]=myHash[i].st;
    }
    for(int i=0;i<nametp.size();i++){
        w.nap[i].first=nametp[i].first;
        w.nap[i].second=nametp[i].second;
    }
    double asl=0;
    w.ravl=QString::number(ASLcnt(asl),10,5);
    for(int i=0;i<randm.size();i++){
        w.randmsg[i]=randm[i];
    }

    w.show();

    return a.exec();
}
