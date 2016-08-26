#include "classmate.h"

//设置同学的信息,传参
void classmate::inPut(const string &t_name, const string &t_ID, const string &t_birthDay)
{
    m_name = t_name;
    m_ID = t_ID;
    m_birthDay = t_birthDay;
}

//设置同学的信息,从键盘输入
void classmate::inPut()
{
    cout << "请输入同学的名字 : " << endl;
    cin >> m_name;
    cout << "请输入同学的学号 : " << endl;
    cin >> m_ID;
    cout << "请输入同学的生日 : " << endl;
    cin >> m_birthDay;

}

//打印同学的信息
void classmate::outPut()
{
    cout << "同学的名字 : " << m_name << endl;
    cout << "同学的学号 : " << m_ID << endl;
    cout << "同学的生日 : " << m_birthDay << endl;
}


