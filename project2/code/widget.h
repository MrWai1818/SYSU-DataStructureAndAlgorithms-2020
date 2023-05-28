#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include<QString>
#include<QTextEdit>
#include<string>
QT_BEGIN_NAMESPACE
using namespace std;
namespace Ui { class Widget; }
QT_END_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QString put="";//输入字符串
    QString inf="";//输出相关栈操作字符串
    int index=1,perr=0,rse=0,lse=1;//分别为+-*/运算符的排错提示，.运算符的排错提示，左右括号的排错提示
private:
    Ui::Widget *ui;
    void pushButton_0();
    void pushButton_1();
    void pushButton_2();
    void pushButton_3();
    void pushButton_4();
    void pushButton_5();
    void pushButton_6();
    void pushButton_7();
    void pushButton_8();
    void pushButton_9();
    void pushButton_add();
    void pushButton_mul();
    void pushButton_sub();
    void pushButton_point();
    void pushButton_div();
    void pushButton_rs();
    void pushButton_ls();
    void pushButton_pow();
    void pushButton_del();
    void pushButton_equ();
    void pushButton_clear();
    double compute(string p);
};
#endif // WIDGET_H
