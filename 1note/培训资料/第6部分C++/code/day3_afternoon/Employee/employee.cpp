#include "employee.h"

Employee::Employee():m_name(0)
{
    m_salary = 5000;   //工资开始都是5000
    m_score = 0;       //评分默认为0
    m_name = new char[1];
    *m_name = '\0';    //名字开始都为空字符串
}

Employee::Employee(const string &t_name,double t_score):m_name(0)
{
    m_salary = 5000;   //工资开始都是5000
    m_score = t_score;
    m_name = new char[t_name.length() + 1];
    strcpy(m_name,t_name.c_str());
}

//copy构造函数
Employee::Employee(const Employee &t_employee)
    :m_salary(t_employee.m_salary),m_score(t_employee.m_score),m_name(0)
{
    m_name = new char[strlen(t_employee.m_name) + 1];
    strcpy(m_name,t_employee.m_name);
}

//赋值操作符
Employee& Employee::operator = (const Employee &t_employee)
{
    if(this != &t_employee)
    {
        m_salary = t_employee.m_salary;
        m_score = t_employee.m_score;

        delete [] m_name;
        m_name = new char[strlen(t_employee.m_name) + 1];
        strcpy(m_name,t_employee.m_name);
    }

    return *this;
}

//析构函数
Employee::~Employee()
{
    delete [] m_name;
    m_name = NULL;
}

//打印信息函数
void Employee::print()
{
    cout << "雇员的名字为 : " << m_name << endl;
    cout << "雇员的工资为 : " << m_salary << endl;
    cout << "经理对该雇员的评分为 : " << m_score << endl;
}
