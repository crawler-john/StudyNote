#include "complex.h"

complex::complex()
    :m_real(0.0),m_vir(0.0)
{
}

complex::complex(double t_real, double t_vir)
    :m_real(t_real),m_vir(t_vir)
{
}

complex::complex(const complex &t_complex)
    :m_real(t_complex.m_real),m_vir(t_complex.m_vir)
{
}

complex &complex::operator =(const complex &t_complex)
{
    if(this != &t_complex)
    {
        m_real = t_complex.m_real;
        m_vir = t_complex.m_vir;
    }

    return *this;
}

complex &complex::operator +=(const complex &t_complex)
{
    m_real += t_complex.m_real;
    m_vir += t_complex.m_vir;

    return *this;
}

complex &complex::operator -=(const complex &t_complex)
{
    m_real -= t_complex.m_real;
    m_vir -= t_complex.m_vir;

    return *this;
}

complex complex::operator +(const complex &t_complex)
{
    cout << "not friend" <<endl;
    complex t_complex1;
    t_complex1.m_real = m_real + t_complex.m_real;
    t_complex1.m_vir = m_vir + t_complex.m_vir;
    return t_complex1;
}


//用友元函数来实现操作符的重载
complex operator + (const complex &t_complex1,const complex &t_complex2)
{
    cout << "friend " <<endl;
    complex t_complex;
    t_complex.m_real = t_complex1.m_real + t_complex2.m_real;
    t_complex.m_vir = t_complex1.m_vir + t_complex2.m_vir;

    return t_complex;
}

complex operator - (const complex &t_complex1,const complex &t_complex2)
{
    complex t_complex;
    t_complex.m_real = t_complex1.m_real - t_complex2.m_real;
    t_complex.m_vir = t_complex1.m_vir - t_complex2.m_vir;

    return t_complex;
}

bool operator == (const complex &t_complex1,const complex &t_complex2)
{
    bool t_real = (t_complex1.m_real - t_complex2.m_real) > eps1 && (t_complex1.m_real - t_complex2.m_real) < eps;
    bool t_vir = (t_complex1.m_vir - t_complex2.m_vir) > eps1 && (t_complex1.m_vir - t_complex2.m_vir) < eps;

    return t_real && t_vir;
}

bool operator != (const complex &t_complex1,const complex &t_complex2)
{
    return !(t_complex1 == t_complex2);
}

ostream& operator << (ostream &os,const complex &t_complex)
{
    os << "real : " << t_complex.m_real << " vir : " << t_complex.m_vir;
    return os;
}

istream& operator >> (istream &is,complex &t_complex)
{
    is >> t_complex.m_real >> t_complex.m_vir;
    return is;
}




