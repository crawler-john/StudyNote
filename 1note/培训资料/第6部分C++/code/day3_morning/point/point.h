#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>

using namespace std;

class point
{
public:

    //无参的构造函数
    point();

    //有参的构造函数
    point(double t_X,double t_Y);

    //copy构造函数
    point(const point &t_point);

    //赋值操作符
    point& operator = (const point &t_point);

    //析构函数
    ~point();

    //移动坐标
    void move(double t_xOffset,double t_yOffset);

    //打印信息
    void print();


private:

    double m_X;   //X坐标
    double m_Y;   //Y坐标
};

#endif // POINT_H
