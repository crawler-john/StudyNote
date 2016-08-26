#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class student;

class Count;

class teacher
{
public:

    teacher()
    {
        m_name = "Jim";
    }

    ~teacher(){}

    void setStuScore(student &t_student);

private:

    string m_name;
};

class student
{
public:

    student()
    {
        cout << "student()" << endl;
        m_name = "Jim";
        m_ID = "001";

        m_chinese = 100;
        m_maths = 100;
        m_english= 100;

    }


    ~student()
    {
        cout << "~student()" << endl;
    }

    string getCountName(const Count &t_count);

    void print()
    {
        cout << "student name : " << m_name << endl;
        cout << "student ID : " << m_ID << endl;
        cout << "student chinese : " << m_chinese << endl;
        cout << "student maths : " << m_maths << endl;
        cout << "student english : " << m_english << endl;
    }

    //将一个普通函数设置为一个类的友元函数
    friend void getStuScore(const student &t_student);

    //将一个类的某个成员函数设置为另外一个类的友元函数
    friend void teacher::setStuScore(student &t_student);

    //将一个类设置为另外一个类的友元类
    friend class Count;

    //用友元函数实现操作符的重载
    friend ostream& operator << (ostream& os,const student &t_student);
    friend istream& operator >> (istream& is,student &t_student);

private:

    string m_name;
    string m_ID;

    double m_chinese;
    double m_maths;
    double m_english;

};


class Count
{
public:

    Count()
    {
        m_name = "count1";
    }

    double getStuAllScore(const student &t_student);

    double getStuAverScore(const student &t_student);

    friend class student;

private:

    string m_name;
};






#endif // STUDENT_H
