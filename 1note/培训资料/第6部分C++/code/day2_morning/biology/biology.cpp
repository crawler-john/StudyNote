#include "biology.h"

void biology::move()
{
    cout << "biology : " << m_name << " move! " << endl;
}

void biology::eat()
{
    cout << "biology : " << m_name << " eat! " << endl;
}

void biology::setName(const string &t_name)
{
    m_name = t_name;
}

string biology::getName()
{
    return m_name;
}




