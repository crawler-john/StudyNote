#ifndef MANAGER_H
#define MANAGER_H

#include "employee.h"

//经理类
class manager : virtual public employee
{
public:
    manager();

    ~manager();

    //提升级别
    virtual void raiseGrade();

    //计算月薪
    virtual void countSalary();

protected:

    int m_fixedSalary;   //固定薪水(底薪)
};

#endif // MANAGER_H
