#ifndef SALESMAN_H
#define SALESMAN_H

#include "employee.h"

//销售人员类
class salesman : virtual public employee
{
public:

    salesman();

    ~salesman();

    //提升级别
    virtual void raiseGrade();

    //计算月薪
    virtual void countSalary();

    static int m_salesNumber;  //销售人员的数量

protected:

    int m_marketMoney;         //当月的市场销售额
    double m_marketPercent;    //销售提成

};

#endif // SALESMAN_H
