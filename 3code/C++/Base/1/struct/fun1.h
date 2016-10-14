#ifndef FUN1_H
#define FUN1_H

#include <string>
#include <iostream>

using namespace std;

//C++中的struct可以声明定义函数
struct Person
{
    string m_name;
    int m_age;
    int m_weight;

    void print()
    {
        cout << "person name : " << m_name << endl;
        cout << "person age : " << m_age << endl;
        cout << "person weight : " << m_weight << endl;
    }
};

#endif // FUN1_H

