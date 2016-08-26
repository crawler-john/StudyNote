#include "date.h"

//无参构造函数
date::date()
{
    m_year = 1970;
    m_month = 1;
    m_day = 1;
}

//有参构造函数
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

//析构函数
date::~date()
{
    cout << "~date()" << endl;
}

//设置日期
void date::setDate(int t_year, int t_month, int t_day)
{
    m_year = t_year;
    m_month = t_month;
    m_day = t_day;
}

//打印信息
void date::print()
{
    cout << "日期为 : " << m_year << " 年 " << m_month << " 月 " << m_day << " 日 " << endl;
}
