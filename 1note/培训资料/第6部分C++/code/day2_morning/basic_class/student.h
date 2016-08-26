#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

//类
//类的作用域:类声明部分和类的成员函数定义部分
//类内和类外
class student
{
public:

    string m_name;      //类的成员变量

    string getName();   //类的成员函数

    //类的所有区间的成员函数可以访问类的所有区间的成员(成员变量和成员函数)
    void test_fun1()
    {
        m_name;
        getName();

        m_ID;
        getID();

        m_age;
        getAge();
    }

    inline void setName(const string &t_name);

    void print();

    //类中成员函数的重载
//    void setInfo(const string &t_name);
//    void setInfo(const string &t_name,const string &t_ID);
//    void setInfo(const string &t_name ,const string &t_ID,int t_age);

    void setInfo(const string &t_name = "Bill",const string &t_ID = "000",int t_age = 30);

protected:

    string m_ID;

    string getID();


private:

    int m_age;

    int getAge();


};


inline void student::setName(const string &t_name)
{
    m_name = t_name;
}


















#endif // STUDENT_H
