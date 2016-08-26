#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

using namespace std;

//雇员类  -- 虚基类  --抽象基类
class employee
{
public:

    //构造函数
    employee();

    //析构函数
    virtual ~employee();

    //提升级别
    virtual void raiseGrade() = 0;

    //计算月薪
    virtual void countSalary() = 0;

    //打印员工的信息
    void print();

protected:

    string m_name;       //名字
    string m_type;       //职位
    int m_ID;            //工号
    int m_grade;         //级别
    int m_salary;        //薪水
    static int m_number; //员工的数量(从1000开始)

};

#endif // EMPLOYEE_H
