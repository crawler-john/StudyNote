#include "date.h"

//�޲ι��캯��
date::date()
{
    m_year = 1970;
    m_month = 1;
    m_day = 1;
}

//�вι��캯��
date::date(int t_year, int t_month, int t_day)
    :m_year(t_year),m_month(t_month),m_day(t_day)
{
}

date::date(const date &t_date)
{
    cout << "copy date(...)" << endl;
    m_year = t_date.m_year;
    m_month = t_date.m_month;
    m_day = t_date.m_day;
}

date &date::operator =(const date &t_date)
{
    cout << "operator ======= " << endl;

    if(this != &t_date)
    {
        m_year = t_date.m_year;
        m_month = t_date.m_month;
        m_day = t_date.m_day;
    }

    return *this;
}

//��������
date::~date()
{
    cout << "~date()" << endl;
}

//��������
void date::setDate(int t_year, int t_month, int t_day)
{
    m_year = t_year;
    m_month = t_month;
    m_day = t_day;
}

//��ӡ��Ϣ
void date::print()
{
    cout << "����Ϊ : " << m_year << " �� " << m_month << " �� " << m_day << " �� " << endl;
}
