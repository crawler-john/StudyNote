#include "classmate.h"

//����ͬѧ����Ϣ,����
void classmate::inPut(const string &t_name, const string &t_ID, const string &t_birthDay)
{
    m_name = t_name;
    m_ID = t_ID;
    m_birthDay = t_birthDay;
}

//����ͬѧ����Ϣ,�Ӽ�������
void classmate::inPut()
{
    cout << "������ͬѧ������ : " << endl;
    cin >> m_name;
    cout << "������ͬѧ��ѧ�� : " << endl;
    cin >> m_ID;
    cout << "������ͬѧ������ : " << endl;
    cin >> m_birthDay;

}

//��ӡͬѧ����Ϣ
void classmate::outPut()
{
    cout << "ͬѧ������ : " << m_name << endl;
    cout << "ͬѧ��ѧ�� : " << m_ID << endl;
    cout << "ͬѧ������ : " << m_birthDay << endl;
}


