#include "technician.h"

//���캯��
technician::technician()
{
    //Ա����ְλΪ��ְ����Ա
    m_type = "��ְ����Ա";

    m_hourNum = 0;       //Ĭ�Ϲ���Сʱ��Ϊ0
    m_hourSalary = 100;  //ʱнΪ100
}

//��������
technician::~technician()
{

}

//��������
void technician::raiseGrade()
{
    m_grade = 3;
}

//������н
void technician::countSalary()
{
    cout << "������Ա�� : " << m_name << " ְλ : " << m_type << " �Ĺ���Сʱ�� : " << endl;
    cin >> m_hourNum;

    cout << "Ա�� : " << m_name << " �Ĺ���Сʱ��Ϊ : " << m_hourNum << endl;
    cout << "Ա�� : " << m_name << " ��ʱнΪ : " << m_hourSalary << endl;

    //��нΪ
    m_salary = m_hourNum*m_hourSalary;
}
