#include "point.h"

//无参的构造函数
point::point()
    :m_X(0.0),m_Y(0.0)
{
    cout << "point()" << endl;
}

//有参的构造函数
point::point(double t_X,double t_Y)
    :m_X(t_X),m_Y(t_Y)
{
    cout << "point(...)" << endl;
}

point::point(const point &t_point)
    :m_X(t_point.m_X),m_Y(t_point.m_Y)
{
    cout << "copy point(...)" << endl;
}

point &point::operator =(const point &t_point)
{
    cout << "operator ======== " << endl;

    if(this != &t_point)
    {
        m_X = t_point.m_X;
        m_Y = t_point.m_Y;
    }

    return *this;
}

//析构函数
point::~point()
{
    cout << "~point()" << endl;
}

//移动坐标
void point::move(double t_xOffset,double t_yOffset)
{
    m_X += t_xOffset;
    m_Y += t_yOffset;
}

//打印信息
void point::print()
{
    cout << "X坐标为 : " << m_X << " Y坐标为 : " << m_Y << endl;
}
