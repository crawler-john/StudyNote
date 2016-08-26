#include "employee.h"

Employee::Employee():m_name(0)
{
    m_salary = 5000;   //���ʿ�ʼ����5000
    m_score = 0;       //����Ĭ��Ϊ0
    m_name = new char[1];
    *m_name = '\0';    //���ֿ�ʼ��Ϊ���ַ���
}

Employee::Employee(const string &t_name,double t_score):m_name(0)
{
    m_salary = 5000;   //���ʿ�ʼ����5000
    m_score = t_score;
    m_name = new char[t_name.length() + 1];
    strcpy(m_name,t_name.c_str());
}

//copy���캯��
Employee::Employee(const Employee &t_employee)
    :m_salary(t_employee.m_salary),m_score(t_employee.m_score),m_name(0)
{
    m_name = new char[strlen(t_employee.m_name) + 1];
    strcpy(m_name,t_employee.m_name);
}

//��ֵ������
Employee& Employee::operator = (const Employee &t_employee)
{
    if(this != &t_employee)
    {
        m_salary = t_employee.m_salary;
        m_score = t_employee.m_score;

        delete [] m_name;
        m_name = new char[strlen(t_employee.m_name) + 1];
        strcpy(m_name,t_employee.m_name);
    }

    return *this;
}

//��������
Employee::~Employee()
{
    delete [] m_name;
    m_name = NULL;
}

//��ӡ��Ϣ����
void Employee::print()
{
    cout << "��Ա������Ϊ : " << m_name << endl;
    cout << "��Ա�Ĺ���Ϊ : " << m_salary << endl;
    cout << "����Ըù�Ա������Ϊ : " << m_score << endl;
}
