#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include<QStandardItem>
#include<QStandardItemModel>

#include<iostream>
#include<vector>
#include<map>
#include<string.h>
using namespace std;

struct listHash
{
    int key;
    string name;
    int st;
    listHash *next;
    listHash(){
        key=-1;
        name="";
        st=0;
        next=NULL;
    }
};
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QString randhash[50]; //存好的名字
    int randst[50]; //存好名字的查找长度
    QString randmsg[50];
    QString ravl=0;
    QString searchone;
    void switchPage();
    vector<QString> listm;
    pair<string,int> nap[30]={{"",0}};
    int LineMkHash(int,string);
    QString listSearch(int,string );
    double listASLcnt(double );
    double listasl=0;

private slots:

    void on_mkhash_clicked();

    void on_search_clicked();

    void on_lmkhash_clicked();

    void on_lsrch_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
