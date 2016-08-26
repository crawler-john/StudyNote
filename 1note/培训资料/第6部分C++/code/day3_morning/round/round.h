#ifndef ROUND_H
#define ROUND_H


#include <iostream>

using namespace std;

#define pi 3.1415926

class round
{
public:

    //无参的构造函数
    round()
    {
        cout << "round()" << endl;
        m_r = 100.0;
    }

    //有参的构造函数
    round(double t_r)
        :m_r(t_r)
    {
        cout << "round(...)" << endl;
    }

    //copy构造函数
    round(const round &t_round)
    {
        cout << "copy round(...)" << endl;
        m_r = t_round.m_r;
    }

    //重载赋值操作符
    round& operator = (const round &t_round)
    {
        cout << "operator ======== " << endl;

        if(this != &t_round)
        {
            m_r = t_round.m_r;
        }

        return *this;
    }

    //析构函数
    ~round()
    {
        cout << "~round()" << endl;
    }

    void setR(double t_r);    //设置圆的半径
    double getR();            //获取圆的半径

    double getGirth();        //获取圆的周长
    double getArea();         //获取圆的面积

private:

    double m_r;          //圆的半径






};

#endif // ROUND_H
