#include "employee.h"

//员工数量开始为0,增加一个员工,数量加一
int Employee::m_number = 0;

Employee::Employee(empType t_type):m_name(0)
{
    if(t_type == NOT_Default)
    {
        //增加一个员工,数量加一
        m_number++;

        m_salary = 5000;   //工资开始都是5000

        cout << "请输入员工 " << m_number << " 的名字(小于256字符) : " << endl;
        m_name = new char[256];
        cin >> m_name;

        cout << "请输入员工 " << m_number << " 的经理给的评分 : " << endl;
        cin >> m_score;
    }
    else
    {
        m_salary = 0;
        m_score = 0;
        m_name = new char[1];
        *m_name = '\0';
    }
}

//copy构造函数
Employee::Employee(const Employee &t_employee)
    :m_salary(t_employee.m_salary),m_score(t_employee.m_score),m_name(0)
{
    //增加一个员工,数量加一
    m_number++;

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
    //减少一个员工,数量减一
    m_number--;

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
