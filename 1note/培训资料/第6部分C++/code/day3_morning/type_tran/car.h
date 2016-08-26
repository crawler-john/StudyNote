#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>

using namespace std;

class car
{
public:

    car()
    {
        cout << "car()" << endl;
        m_name = "BMW";
        m_age = 0;
    }

    //抑制一个参数的构造函数的隐式转换
    explicit car(const char *t_name)
    {
        cout << "car(const char *t_name)" << endl;
        m_name = string(t_name);
        m_age = 1;
    }

    /*explicit*/ car(int t_age)
    {
        cout << "car(int t_age)" << endl;
        m_name = "BYD";
        m_age = t_age;
    }

    car(const string &t_name,int t_age)
        :m_name(t_name),m_age(t_age)
    {
        cout << "car(const string &t_name,int t_age)" << endl;
    }

    ~car()
    {
        cout << "~car()" << endl;
    }

    void print() const
    {
        cout << "car name : " << m_name << endl;
        cout << "car age : " << m_age << endl;
    }

private:

    string m_name;
    int m_age;
};

#endif // CAR_H
