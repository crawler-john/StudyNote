#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

#define eps   0.0000001
#define eps1 -0.0000001

using namespace std;

//复数类
class complex
{
public:

    complex();
    complex(double t_real,double t_vir);
    complex(const complex &t_complex);

    complex& operator = (const complex &t_complex);

    complex& operator += (const complex &t_complex);
    complex& operator -= (const complex &t_complex);


    complex operator + (const complex &t_complex);

    //用友元函数来实现操作符的重载
    friend complex operator + (const complex &t_complex1,const complex &t_complex2);

    friend complex operator - (const complex &t_complex1,const complex &t_complex2);
    friend bool operator == (const complex &t_complex1,const complex &t_complex2);
    friend bool operator != (const complex &t_complex1,const complex &t_complex2);
    friend ostream& operator << (ostream &os,const complex &t_complex);
    friend istream& operator >> (istream &is,complex &t_complex);
    void print()
    {
        cout << m_real << "+" << m_vir << "i" <<endl;
    }

private:
    double m_real;  //实部
    double m_vir;   //虚部
};

#endif // COMPLEX_H
