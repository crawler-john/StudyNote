#ifndef ROUND_H
#define ROUND_H

#include <iostream>

using namespace std;

#define pi 3.14159

class round
{
public:

    void setR(double t_r);    //设置圆的半径

    double getR();            //获取圆的半径

    double getArea();         //获取圆的面积

    double getGirth();        //获取圆的周长

private:

    double m_r;        //圆的半径
};

#endif // ROUND_H
