#include <iostream>
#include "student.h"

using namespace std;



void fun1()
{
    student t_student1;

    //静态类的对象只构造一次
    //静态类的对象生存周期是整个程序
    //局部的静态类对象的作用域是在函数fun1里面
    static student t_student4;

    cout << "student num2 : " << student::getNumber() << endl;
}

int main()
{
//    student t_student1;
//    student t_student2;

//    t_student1.print();
//    t_student2.print();

//    cout << "111111111111111111" << endl;

//    //常用调用静态成员的方法
//    cout << "student number : " << student::m_number << endl;
//    cout << "student number2 : " << student::getNumber() << endl;

    //不常用调用静态成员的方法
//    cout << "student number3 : " << t_student1.m_number << endl;
//    cout << "student number4 : " << t_student1.getNumber() << endl;
//    cout << "student number5 : " << t_student2.m_number << endl;
//    cout << "student number6 : " << t_student2.getNumber() << endl;

    student t_student1;
    student t_student2;

    cout << "student num1 : " << student::getNumber() << endl;

    fun1();

    fun1();

    cout << "student num3 : " << student::getNumber() << endl;

    cout << "Hello World!" << endl;

    return 0;
}

