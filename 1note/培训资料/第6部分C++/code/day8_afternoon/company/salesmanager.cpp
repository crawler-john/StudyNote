#include "salesmanager.h"

SalesManager::SalesManager()
{
    m_type = "销售经理";
    m_fixedSalary = 5000;   //默认底薪为5000
    m_marketPercent = 0.05; //默认市场提成为5%
}

SalesManager::~SalesManager()
{

}

//提升级别
void SalesManager::raiseGrade()
{
    m_grade = 3;
}

//计算月薪
void SalesManager::countSalary()
{
    cout << "请输入员工 : " << m_name << " 职位 : " << m_type << " 的部门当月的销售额 : " << endl;
    cin >> m_marketMoney;

    cout << "员工 : " << m_name << " 的部门当月的销售额为 :" << m_marketMoney << endl;
    cout << "员工 : " << m_name << " 的市场提成为 : "<< m_marketPercent << endl;
    cout << "员工 : " << m_name << " 的底薪为 : " << m_fixedSalary << endl;

    //月薪为
    m_salary = m_marketMoney*m_marketPercent + m_fixedSalary;
}
