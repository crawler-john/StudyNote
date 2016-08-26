#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

enum empType
{
    DEFAULT = 1,      //默认类型
    NOT_Default = 2   //非默认类型
};

//雇员类
class Employee
{
public:

    //构造函数
    Employee(empType t_type = NOT_Default);

    //copy构造函数
    Employee(const Employee &t_employee);

    //赋值操作符
    Employee& operator = (const Employee &t_employee);

    //析构函数
    ~Employee();

    //加工资函数
    void addSalary() {m_salary = m_salary*1.5;}

    //获取经理给该雇员的评分
    double getScore() {return m_score;}

    //打印信息函数
    void print();

private:
    char *m_name;        //雇员的名字
    double m_salary;     //雇员的工资
    double m_score;      //经理对雇员的评分
    static int m_number; //员工的数量
};

#endif // EMPLOYEE_H
