#include "manager.h"

manager::manager()
{
    m_type = "经理";

    m_fixedSalary = 8000;  //默认底薪为8000
}

manager::~manager()
{

}

//提升级别
void manager::raiseGrade()
{
    m_grade = 4;
}

//计算月薪
void manager::countSalary()
{

    cout << "员工 : " << m_name << " 职位 : " << m_type << "的底薪为 : " << m_fixedSalary << endl;

    //月薪为
    m_salary = m_fixedSalary;

}
