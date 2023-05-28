#include "widget.h"
#include "ui_widget.h"

#include<QString>
#include<QByteArray>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QLineEdit>
#include<QInputDialog>
#include<QTableView>
#include<QMessageBox>
#include <QMovie>

#include<iostream>
#include<vector>
#include<map>
#include<string.h>
using namespace std;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QMovie *movie = new QMovie("qq1.gif");
    ui->mov1->setMovie(movie);
    movie->start();
    QMovie *movie1 = new QMovie("qq2.gif");
    ui->mov2->setMovie(movie1);
    movie1->start();
    ui->rasl->setFont(QFont( "Timers" , 28 , QFont::Bold) );
    ui->listasl->setFont(QFont( "Timers" , 28 , QFont::Bold) );
}
listHash* mylHash[50];
Widget::~Widget()
{
    delete ui;
}
void Widget::on_mkhash_clicked()
{
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem("姓名") );
    this->ui->hashm->setModel(model);
    QStandardItemModel *modelt = static_cast<QStandardItemModel*>(ui->hashm->model());//创建模型指定父类
    ui->hashm->setModel(modelt);
    for(int i=0;i<50;i++){
           modelt->setItem(i, 0, new QStandardItem(randhash[i]) );
           modelt->setHeaderData(i,Qt::Vertical, i);
    }
    for(int i=0;i<randmsg->size()+1;i++){
        ui->msg->append(randmsg[i]);
    }
    ui->rasl->setText(ravl);
}

void Widget::on_search_clicked()
{
    bool isOK;
    searchone = QInputDialog::getText(NULL, "Input ","Please input your the name to be searched",QLineEdit::Normal,"input",&isOK);
    int nf=0;
    QString t="";
    for(int i=0;i<50;i++){
        if(searchone==randhash[i]){
            t+= searchone+" is at : "+QString::number(i,10,0)+"\n"+"It's search length is : "+QString::number(randst[i],10,0);
            nf++;
        }
    }
    if(nf==0){
        t= searchone+" isn't in this table";
    }
    if(isOK) {
              QMessageBox::information(NULL, "Result",t, QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
   }
}

int Widget::LineMkHash(int pkey,string pnam){
    int H=pkey%47;
    if(mylHash[H]->key==-1){
        mylHash[H]->key=pkey;
        mylHash[H]->name=pnam;
        mylHash[H]->st++;
        listm.push_back("Final Address : "+QString::number(H,10,0)+" Name : "+QString(QString::fromLocal8Bit(pnam.c_str())));
        return 1;
    }else{
        listHash *p=mylHash[H];
        while(p->next!=NULL){
            p=p->next;
        }
        listHash * temp=new listHash();
        temp->key=pkey;
        temp->name=pnam;
        temp->st=p->st+1;
        p->next=temp;
        listm.push_back("Final Address : "+QString::number(H,10,0)+" Name : "+QString(QString::fromLocal8Bit(pnam.c_str()))+" after :"+QString(QString::fromLocal8Bit(p->name.c_str())));
        return 1;
    }
    return 0;
}
QString Widget::listSearch(int kk,string sname){
    int H=kk%47;
    if(mylHash[H]->key==-1){
        QString temp1=QString(QString::fromLocal8Bit(sname.c_str()))+" isn't in this table";
        return temp1;
    }
    if(mylHash[H]->key==kk){
        QString temp1=QString(QString::fromLocal8Bit(sname.c_str()))+" is at : "+QString::number(H,10,0)+"\n"+"It's search length is : "+QString::number(mylHash[H]->st,10,0);
        return temp1;
    }
    string prename=mylHash[H]->name;
    listHash *temp=mylHash[H]->next;
    while(temp!=NULL){
        if(temp->name==sname){
            QString temp1=QString(QString::fromLocal8Bit(sname.c_str()))+" is at : "+QString::number(H,10,0)+" after: "+QString(QString::fromLocal8Bit(prename.c_str()))+"\n"+"It's search length is : "+QString::number(temp->st,10,0);
            return temp1;
        }
        prename=temp->name;
        temp=temp->next;
    }
    QString temp1=QString(QString::fromLocal8Bit(sname.c_str()))+" isn't in this table";
    return temp1;
}

void Widget::on_lmkhash_clicked()
{
    QStandardItemModel *modelj = new QStandardItemModel();
    modelj->setHorizontalHeaderItem(0, new QStandardItem("姓名") );
    this->ui->listshow->setModel(modelj);
    for(int i=0;i<50;i++){
        mylHash[i]=new listHash();
    }
    for(int i=0;i<30;i++){
        LineMkHash(nap[i].second,nap[i].first);
    }
    for(int i=0;i<listm.size()+1;i++){
        ui->lmsg->append(listm[i]);
    }

    QStandardItemModel *modelt = static_cast<QStandardItemModel*>(ui->listshow->model());//创建模型指定父类
    ui->listshow->setModel(modelt);
    for(int i=0;i<50;i++){
           int cnt=0;
           modelt->setItem(i, cnt, new QStandardItem(QString(QString::fromLocal8Bit(mylHash[i]->name.c_str()))) );
           listHash* p=new listHash();
           p->next=mylHash[i];
           p=p->next;
           while(p->next!=NULL){
               p=p->next;
               cnt=cnt+1;
               modelt->setItem(i, cnt, new QStandardItem(QString(QString::fromLocal8Bit(p->name.c_str()))) );
           }
           modelt->setHeaderData(i,Qt::Vertical, i);
    }

    for(int i=0;i<50;i++){
        while(mylHash[i]!=NULL){
            listasl+=mylHash[i]->st;
            mylHash[i]=mylHash[i]->next;
        }
    }
    listasl=listasl/30;
    QString y=QString::number(listasl,'g',5);
    ui->listasl->setText(y);
}


void Widget::on_lsrch_clicked()
{
    for(int i=0;i<50;i++){
        mylHash[i]=new listHash();
    }
    for(int i=0;i<30;i++){
        LineMkHash(nap[i].second,nap[i].first);
    }
    bool isOK;
    searchone = QInputDialog::getText(NULL, "Input ","Please input your the name to be searched",QLineEdit::Normal,"input",&isOK);
    QByteArray o=searchone.toLocal8Bit();
    string j=string(o);
    int kk=0;
    for(auto t:j){
        kk+=toascii(t);
    }
    QString yy=listSearch(kk,j);
    if(isOK) {
              QMessageBox::information(NULL, "Result",yy, QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
   }
}

