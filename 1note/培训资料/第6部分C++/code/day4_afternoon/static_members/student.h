#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class student
{
public:

    student()
    {
        cout << "student()" << endl;
        m_name = "Jim";
        m_ID = "001";
        m_chinese = 100;

        m_number++;

    }


    ~student()
    {
        cout << "~student()" << endl;

        m_number--;
    }


    //一般的非静态成员函数可以访问类的静态成员(成员变量和成员函数)
    void print()
    {
        getNumber();
        getCount();

        cout << "student name : " << this->m_name << endl;
        cout << "student ID : " << m_ID << endl;
        cout << "student chinese : " << m_chinese << endl;
        cout << "student number : " << m_number << endl;
    }

    //静态成员函数,不能直接访问类的非静态成员(成员变量和成员函数)
    //静态成员函数,可以访问类的静态成员(成员变量和成员函数)
    //设计层面:类的静态成员是属于整个类的,不属于类的任何一个对象,但同时又被该类的所有对象共享
    //技术层面:类的静态成员函数没有this指针
    static int getNumber()
    {
//        this->m_name;
//        this->m_ID;

//        print();

//        cout << "2222222222222222" << endl;

//        m_count;

//        getCount();


        return m_number;
    }

    static int getCount()
    {
        return m_count;
    }

private:

    string m_name;
    string m_ID;
    double m_chinese;

public:

    //静态成员变量
    static int m_number;
    static int m_count;

};






#endif // STUDENT_H
