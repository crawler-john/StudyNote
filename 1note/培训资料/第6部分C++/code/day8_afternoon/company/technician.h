#ifndef TECHNICIAN_H
#define TECHNICIAN_H

#include "employee.h"

//技术人员类
class technician : public employee
{
public:

    technician();

    ~technician();

    //提升级别
    virtual void raiseGrade();

    //计算月薪
    virtual void countSalary();

private:

    int m_hourNum;    //工作小时数
    int m_hourSalary; //时薪

};

#endif // TECHNICIAN_H
