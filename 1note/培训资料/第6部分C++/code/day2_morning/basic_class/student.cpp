#include "student.h"

//this指针存放类的对象的首地址,
//this指针是隐藏在成员函数中的第一个行参；
string student::getName()
{
    cout << "11111111111111" << endl;
    return m_name;
}



string student::getID()
{
    return m_ID;
}

int student::getAge()
{
    return this->m_age;
}

void student::print()
{
    cout << "student name : " << m_name << endl;
    cout << "student ID : " << m_ID << endl;
    cout << "student age : " << m_age << endl;
}

void student::setInfo(const string &t_name, const string &t_ID, int t_age)
{
    m_name = t_name;
    m_ID = t_ID;
    m_age = t_age;

}

//void student::setInfo(const string &t_name)
//{
//    m_name = t_name;
//}

//void student::setInfo(const string &t_name, const string &t_ID)
//{
//    m_name = t_name;
//    m_ID = t_ID;
//}

//void student::setInfo(const string &t_name, const string &t_ID, int t_age)
//{
//    m_name = t_name;
//    m_ID = t_ID;
//    m_age = t_age;
//}



