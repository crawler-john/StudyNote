#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>

using namespace std;

class student
{
public:

    student()
    {
        cout << "student()" << endl;
        m_name = "Jim";
        m_ID = "001";
        m_age = 20;

    }

    student(const string &t_name,const string &t_ID,int t_age)
        :m_name(t_name),m_ID(t_ID),m_age(t_age)
    {
        cout << "student(...)" << endl;
    }


    ~student()
    {
        cout << "~student()" << endl;

    }

    //一般的成员函数可以调用const成员函数
    void print()
    {
//        getID();

        getName();
        getAge();

        cout << "student name : " << m_name << endl;
        cout << "student ID : " << m_ID << endl;
        cout << "student age : " << m_age << endl;
    }

    //类的const成员函数不能修改类的成员变量,只能访问
    //类的const成员函数不能调用非const成员函数,可以访问调用其它的const成员函数
    string getName() const
    {
//        m_name = "123";

        //getID();

        getAge();

        return m_name;
    }

    string getID()
    {
//        m_name = "123";

        return m_ID;
    }

    int getAge() const;

private:

    string m_name;
    string m_ID;
    int m_age;
};

#endif // STUDENT_H
