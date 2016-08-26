#include "patient.h"

//初始化病人的数量
int Patient::m_number = 0;

//构造函数
Patient::Patient()
{
    #if 0
    m_name = "Jack";
    m_bloodPress = 100.0;
    m_curePlan = NORMAL;
    m_number++;

    #else
    m_number++;
    cout << "请输入病人 " << m_number << " 的名字  : " << endl;
    cin >> m_name;
    cout << "请输入病人 " << m_number << " 的血压 : " << endl;
    cin >> m_bloodPress;
    m_curePlan = NORMAL;
    #endif
}

Patient::Patient(const string &t_name, double t_bloodPress, Plan t_curePlan)
    :m_name(t_name),m_bloodPress(t_bloodPress),m_curePlan(t_curePlan)
{
    m_number++;
}

