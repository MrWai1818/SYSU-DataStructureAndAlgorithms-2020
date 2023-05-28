#ifndef FUNCTION_H
#define FUNCTION_H
#include <stack>
#include<string>
#include<iomanip>
#include <cmath>
#include<cstdlib>
#include<cstring>
#include<iterator>
using namespace std;
int Jugde(char a, char b){
    int i=1;
    switch (a)
    {
    case '+':
        if((b == '+' )||(b== '-') ||(b== ')') ||(b== '#')){
            i= 1;
            break;
        }else{
            i= -1;
            break;
        }
        break;
    case '-':
        if((b == '+' )||(b== '-') ||(b== ')') ||(b== '#')){
            i= 1;
            break;
        }else{
            i= -1;
            break;
        }
        break;
    case '*':
        if((b == '(')||(b=='^')){
            i= -1;
            break;
        }else{
            i= 1;
            break;
        }
        break;
    case '/':
        if((b == '(')||(b=='^')){
            i= -1;
            break;
        }else{
            i= 1;
            break;
        }
        break;
    case '^':
        if(b == '('){
            i= -1;
            break;
        }else{
            i= 1;
            break;
        }
        break;
    case '(':
        if(b == ')'){
            i= 0;
            break;
        }else{
            i= -1;
            break;
        }
        break;
    case ')':
        i= 1;
        break;
    case '#':
        if(b == '#'){
                i= 0;
                break;
            }else{
                i= -1;
                break;
            }
            break;
    default:
        break;
    }
    return i;
}
double operate(double a, char op, double b){
    double temp=0;
    if(op == '+'){
        temp=a + b;
    }else if(op == '-'){
        temp= a - b;
    }else if(op == '*'){
        temp=a * b;
    }else if(op == '/'){
        temp=a / b;
    }else if(op == '^'){
        temp=pow(a,b);
    }
    return temp;
}
#endif // FUNCTION_H
