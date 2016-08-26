#include "employee.h"

//Ա��������ʼΪ0,����һ��Ա��,������һ
int Employee::m_number = 0;

Employee::Employee(empType t_type):m_name(0)
{
    if(t_type == NOT_Default)
    {
        //����һ��Ա��,������һ
        m_number++;

        m_salary = 5000;   //���ʿ�ʼ����5000

        cout << "������Ա�� " << m_number << " ������(С��256�ַ�) : " << endl;
        m_name = new char[256];
        cin >> m_name;

        cout << "������Ա�� " << m_number << " �ľ���������� : " << endl;
        cin >> m_score;
    }
    else
    {
        m_salary = 0;
        m_score = 0;
        m_name = new char[1];
        *m_name = '\0';
    }
}

//copy���캯��
Employee::Employee(const Employee &t_employee)
    :m_salary(t_employee.m_salary),m_score(t_employee.m_score),m_name(0)
{
    //����һ��Ա��,������һ
    m_number++;

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
    //����һ��Ա��,������һ
    m_number--;

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
