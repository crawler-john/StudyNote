#include "point.h"

//�޲εĹ��캯��
point::point()
    :m_X(0.0),m_Y(0.0)
{
    cout << "point()" << endl;
}

//�вεĹ��캯��
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

//��������
point::~point()
{
    cout << "~point()" << endl;
}

//�ƶ�����
void point::move(double t_xOffset,double t_yOffset)
{
    m_X += t_xOffset;
    m_Y += t_yOffset;
}

//��ӡ��Ϣ
void point::print()
{
    cout << "X����Ϊ : " << m_X << " Y����Ϊ : " << m_Y << endl;
}
