#include "patient.h"

//��ʼ�����˵�����
int Patient::m_number = 0;

//���캯��
Patient::Patient()
{
    #if 0
    m_name = "Jack";
    m_bloodPress = 100.0;
    m_curePlan = NORMAL;
    m_number++;

    #else
    m_number++;
    cout << "�����벡�� " << m_number << " ������  : " << endl;
    cin >> m_name;
    cout << "�����벡�� " << m_number << " ��Ѫѹ : " << endl;
    cin >> m_bloodPress;
    m_curePlan = NORMAL;
    #endif
}

Patient::Patient(const string &t_name, double t_bloodPress, Plan t_curePlan)
    :m_name(t_name),m_bloodPress(t_bloodPress),m_curePlan(t_curePlan)
{
    m_number++;
}

