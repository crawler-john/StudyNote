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

    student():m_sex(0)
    {
        cout << "student()" << endl;
        m_name = "Jim";
        m_ID = "001";
        m_age = 20;

        m_sex = new char[4];
        strcpy(m_sex,"Man");
    }

    student(const string &t_name,const string &t_ID,int t_age,const string &t_sex)
        :m_name(t_name),m_ID(t_ID),m_age(t_age),m_sex(0)
    {
        cout << "student(...)" << endl;

        m_sex = new char[t_sex.length() + 1];
        strcpy(m_sex,t_sex.c_str());
    }

    //没有自定义自己的copy构造函数时,C++编译器会自动生成一个默认copy构造函数
    //如果自定义自己的copy构造函数,C++编译器不会生成默认的copy构造函数
    student(const student &t_student)
        :m_name(t_student.m_name),m_ID(t_student.m_ID),m_age(t_student.m_age)
    {
        cout << "copy student(...)" << endl;

//        m_name = t_student.m_name;
//        m_ID = t_student.m_ID;
//        m_age = t_student.m_age;

        m_sex = new char[strlen(t_student.m_sex) + 1];
        strcpy(m_sex,t_student.m_sex);
    }

    ~student()
    {
        cout << "~student()" << endl;

        cout << "sex : " << m_sex << endl;

        delete [] m_sex;
        m_sex = NULL;
    }

    void print()
    {
        cout << "student name : " << m_name << endl;
        cout << "student ID : " << m_ID << endl;
        cout << "student age : " << m_age << endl;
        cout << "student sex : " << m_sex << endl;
        printf("sex address : %p\n",m_sex);
    }

private:

    string m_name;
    string m_ID;
    int m_age;
    char *m_sex;
};

#endif // STUDENT_H
