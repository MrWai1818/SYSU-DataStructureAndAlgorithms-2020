#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QString>

#include<vector>
#include <iostream>
#include <cstring>
#include <cmath>
#include<string>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<QStandardItem>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    int n,s,fir;
    vector<vector<QString>> qso;
    vector<vector<QString>> qso2;
    void toText(vector<vector<QString>> &);
    void maketree(vector<vector<QString>> &);
    void remkt(vector<vector<QString>> &);
    QStandardItem *getItem(QStandardItemModel *model, QString s);
    QStandardItem *getItem(QStandardItem *item, QString s);
    void remkt2(vector<vector<QString>> &);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
