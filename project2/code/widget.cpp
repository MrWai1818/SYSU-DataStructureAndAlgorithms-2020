#include "widget.h"
#include<QString>
#include<QLineEdit>
#include<QTextEdit>
#include"function.h"
#include<QPushButton>
#include<QMessageBox>
#include "ui_widget.h"
#include<QKeySequence>
#include <stack>
#include<string>
#include<iomanip>
#include <cmath>
#include<cstdlib>
#include<cstring>
#include <QLabel>
#include <QMovie>
using namespace std;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QFont lineEditFont ( "Microsoft YaHei", 33, 80);
    ui->lineEdit->setFont(lineEditFont);
    QMovie *movie = new QMovie("qqemoji.gif");
    ui->label_2->setMovie(movie);
    movie->start();
    connect(ui->pushButton_0,&QPushButton::clicked,[this](){pushButton_0();});
    connect(ui->pushButton_1,&QPushButton::clicked,[this](){pushButton_1();});
    connect(ui->pushButton_2,&QPushButton::clicked,[this](){pushButton_2();});
    connect(ui->pushButton_3,&QPushButton::clicked,[this](){pushButton_3();});
    connect(ui->pushButton_4,&QPushButton::clicked,[this](){pushButton_4();});
    connect(ui->pushButton_5,&QPushButton::clicked,[this](){pushButton_5();});
    connect(ui->pushButton_6,&QPushButton::clicked,[this](){pushButton_6();});
    connect(ui->pushButton_7,&QPushButton::clicked,[this](){pushButton_7();});
    connect(ui->pushButton_8,&QPushButton::clicked,[this](){pushButton_8();});
    connect(ui->pushButton_9,&QPushButton::clicked,[this](){pushButton_9();});
    connect(ui->pushButton_add,&QPushButton::clicked,[this](){pushButton_add();});
    connect(ui->pushButton_sub,&QPushButton::clicked,[this](){pushButton_sub();});
    connect(ui->pushButton_mul,&QPushButton::clicked,[this](){pushButton_mul();});
    connect(ui->pushButton_div,&QPushButton::clicked,[this](){pushButton_div();});
    connect(ui->pushButton_equ,&QPushButton::clicked,[this](){pushButton_equ();});
    connect(ui->pushButton_del,&QPushButton::clicked,[this](){pushButton_del();});
    connect(ui->pushButton_pow,&QPushButton::clicked,[this](){pushButton_pow();});
    connect(ui->pushButton_ls,&QPushButton::clicked,[this](){pushButton_ls();});
    connect(ui->pushButton_rs,&QPushButton::clicked,[this](){pushButton_rs();});
    connect(ui->pushButton_point,&QPushButton::clicked,[this](){pushButton_point();});
    connect(ui->pushButton_clear,&QPushButton::clicked,[this](){pushButton_clear();});
}
void showError(){
    QMessageBox message(QMessageBox::NoIcon, " ", "输入有问题呢");
    message.setIconPixmap(QPixmap("error.png"));
    message.exec();
}
double Widget::compute(string put){
    stack<char> sym;
    stack<double> num;
    char bench[9] = "+-*/^()#";
    sym.push('#');
    put=put+'#';
    QString s1="",s2="",s3="",s4="";
    double num1,num2,result,value;
    char op;
    int i=0,j;
    while(true){
        j=put.find_first_of(bench,i);
        if(j==string::npos)break;
        if(j!=i){
            string temp(put,i,j-i);
            value =atof(temp.c_str());
            num.push(value);
            QString t="";
            t= QString::number(value,'g',6);
            t+="入num栈";
            ui->textEdit->append(t);
        }
        switch (Jugde(sym.top(),put[j])){
        case -1:
            sym.push(put[j]);
            if(put[j]!='#'){
                char a=put[j];
                QString t="  ";
                t+=a;
                t+="入sym栈";
                ui->textEdit->append(t);
            }
            i=j+1;
            break;
        case 0:
            sym.pop();
            if(put[j]!='#'){
                char a=put[j];
                QString t="  ";
                t+=a;
                t+="出sym栈";
                ui->textEdit->append(t);
            }
            i=j+1;
            break;
        case 1:
            op=sym.top();
            sym.pop();
            if(put[j]!='#'){
                char a=put[j];
                QString t="  ";
                t+=a;
                t+="出sym栈";
                ui->textEdit->append(t);
            }
            num2=num.top();
            s1= QString::number(num2,'g',6);
            s1+="出num栈";
            ui->textEdit->append(s1);
            num.pop();
            num1=num.top();
            s2= QString::number(num1,'g',6);
            s2+="出num栈";
            ui->textEdit->append(s2);
            num.pop();
            result = operate(num1,op,num2);
            s3="得出计算结果";
            s3+=QString::number(result,'g',6);
            ui->textEdit->append(s3);
            num.push(result);
            s4= QString::number(result,'g',6);
            s4+="入num栈";
            ui->textEdit->append(s4);
            i=j;
            break;
        default:
            break;
        }
    }
    return num.top();
}
void Widget::pushButton_0(){
    put+="0";
    if(index==1){
        index=0;
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_1(){
    put+="1";
    rse++;
    if(index==1){
        index=0;
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_2(){
    put+="2";
    rse++;
    if(index==1){
        index=0;
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_3(){
    put+="3";
    rse++;
    if(index==1){
        index=0;
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_4(){
    put+="4";
    rse++;
    if(index==1){
        index=0;
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_5(){
    put+="5";
    rse++;
    if(index==1){
        index=0;
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_6(){
    put+="6";
    rse++;
    if(index==1){
        index=0;
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_7(){
    put+="7";
    rse++;
    if(index==1){
        index=0;
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_8(){
    put+="8";
    rse++;
    if(index==1){
        index=0;
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_9(){
    put+="9";
    rse++;
    if(index==1){
        index=0;
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_add(){
    if(index==0){
        put+="+";
        index++;
        rse=0;
        if(perr==1){
            perr=0;
        }
    }else{
        showError();
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_sub(){
    if(index==0){
        put+="-";
        index++;
        rse=0;
        if(perr==1){
            perr=0;
        }
    }else{
        showError();
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_mul(){
    if(index==0){
        put+="*";
        index++;
        rse=0;
        if(perr==1){
            perr=0;
        }
    }else{
        showError();
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_div(){
    if(index==0){
        put+="/";
        index++;
        rse=0;
        if(perr==1){
            perr=0;
        }
    }else{
        showError();
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_pow(){
    if(index==0){
        put+="^";
        index++;
        rse=0;
        if(perr==1){
            perr=0;
        }
    }else{
        showError();
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_ls(){
    if(put.endsWith("1")||put.endsWith("2")||put.endsWith("3")||put.endsWith("4")||put.endsWith("5")||put.endsWith("6")||put.endsWith("7")||put.endsWith("8")||put.endsWith("9")||put.endsWith("0")){
        showError();//左括号的排错
    }else{
        put+="(";
        index=1;
        ui->lineEdit->setText(put);
    }
}
void Widget::pushButton_rs(){
    if(rse==0){
        showError();
    }else{
        if(put.endsWith("(")){
            showError();
        }else{
            put+=")";
            rse=1;
            ui->lineEdit->setText(put);
        }
    }
}
void Widget::pushButton_point(){
    if(index==0){
        if(perr==0){
            put+=".";
            index++;
            perr++;
        }else{
            showError();
        }
    }else{
        showError();
    }
    ui->lineEdit->setText(put);
}
void Widget::pushButton_del(){
    ui->lineEdit->backspace();
    put.chop(1);
    if(index==1){
        index=0;
    }
    if(rse==0){
        rse=1;
    }
}
void Widget::pushButton_equ(){
    if(put.endsWith("+")||put.endsWith("-")||put.endsWith("*")||put.endsWith("/")||put.endsWith("^")||put.endsWith("(")||put.endsWith(".")){
        showError();
    }else{
        double temp=0;
        string temp1 =put.toStdString();
        temp=compute(temp1);
        put.clear();
        put= QString::number(temp,'g',6);
        ui->lineEdit->setText(put);
    }
}
void Widget::pushButton_clear(){
    put.clear();
    ui->lineEdit->setText(put);
    ui->textEdit->clear();
}
Widget::~Widget()
{
    delete ui;
}

