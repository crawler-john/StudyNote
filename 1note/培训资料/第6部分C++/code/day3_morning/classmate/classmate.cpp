#include "classmate.h"

void classmate::setInfo(const string &t_name, const string &t_ID, const string &t_birthDay)
{
    m_name = t_name;
    m_ID = t_ID;
    m_birthDay = t_birthDay;
}

void classmate::setInfo()
{
    cout << "������ͬѧ������ : " << endl;
    cin >> m_name;
    cout << "������ͬѧ��ID : " << endl;
    cin >> m_ID;
    cout << "������ͬѧ������ : " << endl;
    cin >> m_birthDay;
}

void classmate::print()
{
    cout << "ͬѧ������ : " << m_name << endl;
    cout << "ͬѧ��ID : " << m_ID << endl;
    cout << "ͬѧ������ : " << m_birthDay << endl;
}



