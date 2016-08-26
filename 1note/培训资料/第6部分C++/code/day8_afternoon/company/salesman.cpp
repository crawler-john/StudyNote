#include "salesman.h"

int salesman::m_salesNumber = 0;

//构造函数
salesman::salesman()
{
    m_type = "兼职销售员";
    m_marketMoney = 0;       //默认市场月销售额为0
    m_marketPercent = 0.04;  //默认销售提成为4%

    //销售人员数量加一
    m_salesNumber++;

}

//析构函数
salesman::~salesman()
{
    //销售人员数量减一
    m_salesNumber--;
}

//提升级别
void salesman::raiseGrade()
{
    m_grade = 1;
}

//计算月薪
void salesman::countSalary()
{
    cout << "请输入员工 : " << m_name << " 职位 : " << m_type << " 的当月的市场销售额 : " << endl;
    cin >> m_marketMoney;

    cout << "员工 : " << m_name << " 的当月的市场销售额为 : " << m_marketMoney << endl;
    cout << "员工 : " << m_name << " 的市场提成为 : " << m_marketPercent << endl;

    //月薪为
    m_salary = m_marketMoney*m_marketPercent;
}
