#include "round.h"

void round::setR(double t_r)
{
    m_r = t_r;
}

double round::getR()
{
    return m_r;
}

double round::getArea()
{
    return pi*m_r*m_r;
}

double round::getGirth()
{
    return 2*pi*m_r;
}



