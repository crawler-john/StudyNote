#include "classmate.h"

void classmate::setInfo(const string &t_name, const string &t_ID, const string &t_birthDay)
{
    m_name = t_name;
    m_ID = t_ID;
    m_birthDay = t_birthDay;
}

void classmate::setInfo()
{
    cout << "请输入同学的名字 : " << endl;
    cin >> m_name;
    cout << "请输入同学的ID : " << endl;
    cin >> m_ID;
    cout << "请输入同学的生日 : " << endl;
    cin >> m_birthDay;
}

void classmate::print()
{
    cout << "同学的名字 : " << m_name << endl;
    cout << "同学的ID : " << m_ID << endl;
    cout << "同学的生日 : " << m_birthDay << endl;
}



