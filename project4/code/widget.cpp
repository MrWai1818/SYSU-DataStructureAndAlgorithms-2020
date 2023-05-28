#include "widget.h"
#include "ui_widget.h"
#include<QInputDialog>
#include<QTextEdit>
#include<QStandardItemModel>
#include<QLineEdit>
#include<QtDebug>

#include<string>
#include <iostream>
using namespace std;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
        QImage *img=new QImage;
        img->load("pan.png");
        ui->label->setPixmap(QPixmap::fromImage(*img));

        const QString fileName = "jfu.png";
        QPalette pal = ui->BFS->palette();
        pal.setBrush(QPalette::Base, QPixmap(fileName).scaled(ui->BFS->size()));
        ui->BFS->setAutoFillBackground(true);
        ui->BFS->setPalette(pal);

        const QString fileName2 = "yfu.png";
        QPalette pal2 = ui->DFS->palette();
        pal2.setBrush(QPalette::Base, QPixmap(fileName2).scaled(ui->DFS->size()));
        ui->DFS->setAutoFillBackground(true);
        ui->DFS->setPalette(pal2);

    bool isok1;
    n = QInputDialog::getInt(nullptr, "Vertex", "请输入节点个数", 1, 1, 10000, 1, &isok1, Qt::Dialog | Qt::WindowCloseButtonHint);
    if (!isok1)
        return;
    bool isok2;
    s = QInputDialog::getInt(nullptr, "Edge", "请输入边个数", 1, 1, 10000, 1, &isok2, Qt::Dialog | Qt::WindowCloseButtonHint);
    if (!isok2)
        return;
    fir= QInputDialog::getInt(nullptr, "Begin", "请输入起始节点", 1, 1, 10000, 1, &isok1, Qt::Dialog | Qt::WindowCloseButtonHint);
    if (!isok1)
        return;
    QStandardItemModel *model = new QStandardItemModel(ui->BFS);//创建模型指定父类
    ui->BFS->setModel(model);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Breadth-first Search"));
    QStandardItemModel *model2 = new QStandardItemModel(ui->DFS);//创建模型指定父类
    ui->DFS->setModel(model2);
    model2->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Depth-first Search"));
}
void Widget::toText(vector<vector<QString>> &p){
    for(int i=0;i<p.size();i++){
        for(int j=0;j< p[i].size();j++){
//            ui->""->append(p[i][j]);
        }
    }
}



QStandardItem *Widget::getItem(QStandardItemModel *model, QString s)
{
    QStandardItem *getitem = NULL;
    if(!model->hasChildren())//判断是否有孩子,没有则返回0
        return NULL;
    QList<QStandardItem*> list = model->findItems(s);
//    qDebug() << tr("list is %1").arg(list.length());//检测是否找到
    if(list.length() == 0)//如果链表长度为0，即没找到文本为s的条目
    {
        //将搜索子条目是否存在文本为s的条目
        for(int i = 0;i < model->rowCount()&& getitem == NULL;i++)//遍历model下的所有条目,如果getitem有获得对象，则退出循环
        {
            getitem = getItem(model->item(i),s);//寻找第i行条目下的子条目列中是否存在文本为s的条目。
        }
    }
    else
    {
        return list.at(0);
    }
    return getitem;
}

QStandardItem *Widget::getItem(QStandardItem *item, QString s)
{
    if(item == NULL)
        return NULL;
//    qDebug() << tr("fine %1").arg(item->text());  //检测是否找到
    QStandardItem *getitem = NULL;
    if(item->text().compare(s) == 0)
        return item;
    if(!item->hasChildren())//判断是否有孩子,没有则返回0
        return NULL;
    for(int i = 0;i < item->rowCount() && getitem == NULL;i++)//遍历item下所有子条目，若果getitme有获得对象，则退出循环
    {
        QStandardItem * childitem = item->child(i);
        getitem = getItem(childitem,s);//寻找这个子条目的所有子条目是否存在文本为s的条目。
    }
    return getitem;
}
//下下策，分节点树输出
//void Widget::maketree(vector<vector<QString>> &p){
//    QStandardItemModel *modelt = static_cast<QStandardItemModel*>(ui->BFS->model());//创建模型指定父类
//    ui->BFS->setModel(modelt);
//    for(int i=0;i<p.size();i++){
//        QString temp=p[i][0];
//        QStandardItem* itemProject = new QStandardItem(temp);
//        modelt->appendRow(itemProject);
//        for(int j=1;j<p[i].size();j++){
//            QString tst=p[i][j];
//            QStandardItem* it = new QStandardItem(tst);
//            itemProject->appendRow(it);
//        }
//    }
//}
void Widget::remkt(vector<vector<QString>> &p){
    QStandardItemModel *modelt = static_cast<QStandardItemModel*>(ui->BFS->model());//创建模型指定父类
    ui->BFS->setModel(modelt);
    QString temp=p[0][0];
    QStandardItem* itemProject = new QStandardItem(temp);
    modelt->appendRow(itemProject);
    for(int l=1;l<p[0].size();l++){
        QString ty=p[0][l];
        QStandardItem* ip = new QStandardItem(ty);
        itemProject->appendRow(ip);
    }
    for(int i=1;i<p.size();i++){
//       QList<QStandardItem*> list= modelt->findItems(p[i][0]);
       QStandardItem * getitem = getItem(itemProject,p[i][0]);
//       QStandardItem* getre=list.at(0);
        for(int j=1;j<p[i].size();j++){
           QString tst=p[i][j];
          QStandardItem* it = new QStandardItem(tst);
           getitem->appendRow(it);
//           getitem->parent()->setChild(getitem->row(),0,new QStandardItem(tst));
        }
    }
}

void Widget::remkt2(vector<vector<QString>> &p){
    QStandardItemModel *modelt = static_cast<QStandardItemModel*>(ui->DFS->model());//创建模型指定父类
    ui->DFS->setModel(modelt);
    QString temp=p[0][0];
    QStandardItem* itemProject = new QStandardItem(temp);
    modelt->appendRow(itemProject);
    for(int l=1;l<p[0].size();l++){
        QString ty=p[0][l];
        QStandardItem* ip = new QStandardItem(ty);
        itemProject->appendRow(ip);
    }
    for(int i=1;i<p.size();i++){
//       QList<QStandardItem*> list= modelt->findItems(p[i][0]);
       QStandardItem * getitem = getItem(itemProject,p[i][0]);
//       QStandardItem* getre=list.at(0);
        for(int j=1;j<p[i].size();j++){
           QString tst=p[i][j];
          QStandardItem* it = new QStandardItem(tst);
           getitem->appendRow(it);
//           getitem->parent()->setChild(getitem->row(),0,new QStandardItem(tst));
        }
    }
}
Widget::~Widget()
{
    delete ui;
}

