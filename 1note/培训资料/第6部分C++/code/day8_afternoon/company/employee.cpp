#include "employee.h"

//Ա��������(��1000��ʼ)
int employee::m_number = 1000;

//���캯��
employee::employee()
{
    //Ա����������һ
    m_ID = ++m_number;
    m_type = "Ա��";
    m_grade = 1;
    m_salary = 0;

    cout << "������Ա�� " << m_number << " ������ : " << endl;
    cin >> m_name;
}

//��������
employee::~employee()
{
    m_number--;
}

//��ӡԱ������Ϣ
void employee::print()
{
    cout << "Ա�������� : " << m_name << endl;
    cout << "Ա���Ĺ��� : " << m_ID << endl;
    cout << "Ա����ְλ : " << m_type << endl;
    cout << "Ա���ļ��� : " << m_grade << endl;
    cout << "Ա������н : " << m_salary << endl;
}
