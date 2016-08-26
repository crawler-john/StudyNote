#ifndef CLASSMATE_H
#define CLASSMATE_H

#include <iostream>
#include <string>

using namespace std;

class classmate
{
public:

    //设置同学的信息,传参
    void inPut(const string &t_name,const string &t_ID,const string &t_birthDay);

    //设置同学的信息,从键盘输入
    void inPut();

    //打印同学的信息
    void outPut();

private:

    string m_name;            //同学的名字
    string m_ID;              //同学的学号
    string m_birthDay;        //同学的生日

};

#endif // CLASSMATE_H
