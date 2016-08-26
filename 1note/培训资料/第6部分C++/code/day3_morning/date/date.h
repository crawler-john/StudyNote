#ifndef DATE_H
#define DATE_H

#include <iostream>

using namespace std;

//日期类
class date
{
public:

    //无参构造函数
    date();

    //有参构造函数
    date(int t_year,int t_month,int t_day);

    //copy构造函数
    date(const date &t_date);

    //赋值操作符
    date& operator = (const date &t_date);

    //析构函数
    ~date();

    //设置日期
    void setDate(int t_year,int t_month,int t_day);

    //打印信息
    void print();

private:

    int m_year;   //年
    int m_month;  //月
    int m_day;    //日
};

#endif // DATE_H
