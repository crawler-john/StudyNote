#ifndef CLASSMATE_H
#define CLASSMATE_H


#include <iostream>
#include <string>

using namespace std;

class classmate
{
public:

    //无参的构造函数
    classmate()
    {
        cout << "classmate()" << endl;
        m_name = "Jack";
        m_ID = "001";
        m_birthDay = "1990-1-1";
    }

    //有参的构造函数
    classmate(const string &t_name,const string &t_ID,const string &t_birthDay)
        :m_name(t_name),m_ID(t_ID),m_birthDay(t_birthDay)
    {
        cout << "classmate(...)" << endl;
    }

    //copy构造函数
    classmate(const classmate &t_classmate)
        :m_name(t_classmate.m_name)
    {
        cout << "copy classmate(...)" << endl;
        m_ID = t_classmate.m_ID;
        m_birthDay = t_classmate.m_birthDay;
    }

    //赋值操作符
    classmate& operator = (const classmate &t_classmate)
    {
        cout << "operator ======== " << endl;

        if(this != &t_classmate)
        {
            m_name = t_classmate.m_name;
            m_ID = t_classmate.m_ID;
            m_birthDay = t_classmate.m_birthDay;
        }

        return *this;
    }



    //析构函数
    ~classmate()
    {
        cout << "~classmate()" << endl;
    }

    //设置同学的信息
    void setInfo(const string &t_name,const string &t_ID,const string &t_birthDay);

    //设置同学的信息(从键盘输入)
    void setInfo();

    //输出同学的信息
    void print();

private:

    string m_name;       //同学的名字
    string m_ID;         //同学的ID
    string m_birthDay;   //同学的生日

};

#endif // CLASSMATE_H
