#ifndef SALESMANAGER_H
#define SALESMANAGER_H

#include "salesman.h"
#include "manager.h"

//销售经理类
class SalesManager : public salesman,public manager
{
public:
    SalesManager();

    ~SalesManager();

    //提升级别
    virtual void raiseGrade();

    //计算月薪
    virtual void countSalary();


};

#endif // SALESMANAGER_H
