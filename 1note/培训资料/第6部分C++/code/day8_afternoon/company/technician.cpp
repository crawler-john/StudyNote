#include "technician.h"

//构造函数
technician::technician()
{
    //员工的职位为兼职技术员
    m_type = "兼职技术员";

    m_hourNum = 0;       //默认工作小时数为0
    m_hourSalary = 100;  //时薪为100
}

//析构函数
technician::~technician()
{

}

//提升级别
void technician::raiseGrade()
{
    m_grade = 3;
}

//计算月薪
void technician::countSalary()
{
    cout << "请输入员工 : " << m_name << " 职位 : " << m_type << " 的工作小时数 : " << endl;
    cin >> m_hourNum;

    cout << "员工 : " << m_name << " 的工作小时数为 : " << m_hourNum << endl;
    cout << "员工 : " << m_name << " 的时薪为 : " << m_hourSalary << endl;

    //月薪为
    m_salary = m_hourNum*m_hourSalary;
}
