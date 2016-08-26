#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

class student
{
public:

    student()
    {
        cout << "student()" << endl;
        m_name = "Jim";
        m_ID = "000";
        m_age = 20;
    }

    student(const string &t_name,const string &t_ID,int t_age)
        :m_name(t_name),m_ID(t_ID),m_age(t_age)
    {
        cout << "student(...)" << endl;
    }

    student(const student &t_student)
        :m_name(t_student.m_name),m_ID(t_student.m_ID),m_age(t_student.m_age)
    {
        cout << "copy student(...)" << endl;
    }

    student& operator = (const student &t_student)
    {
        cout << "operator ======= " << endl;

        if(this != &t_student)
        {
            m_name = t_student.m_name;
            m_ID = t_student.m_ID;
            m_age = t_student.m_age;
        }

        return *this;
    }

    ~student()
    {
        cout << "~student()" << endl;
    }

    void print()
    {
        cout << "student name : " << m_name << " ID : " << m_ID
             << " age : " << m_age << endl;
    }

private:

    string m_name;
    string m_ID;
    int m_age;
};

#endif // STUDENT_H
