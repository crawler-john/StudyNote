#include "employee.h"

//员工的数量(从1000开始)
int employee::m_number = 1000;

//构造函数
employee::employee()
{
    //员工的数量加一
    m_ID = ++m_number;
    m_type = "员工";
    m_grade = 1;
    m_salary = 0;

    cout << "请输入员工 " << m_number << " 的名字 : " << endl;
    cin >> m_name;
}

//析构函数
employee::~employee()
{
    m_number--;
}

//打印员工的信息
void employee::print()
{
    cout << "员工的名字 : " << m_name << endl;
    cout << "员工的工号 : " << m_ID << endl;
    cout << "员工的职位 : " << m_type << endl;
    cout << "员工的级别 : " << m_grade << endl;
    cout << "员工的月薪 : " << m_salary << endl;
}
