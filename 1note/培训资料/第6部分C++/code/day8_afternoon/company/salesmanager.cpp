#include "salesmanager.h"

SalesManager::SalesManager()
{
    m_type = "���۾���";
    m_fixedSalary = 5000;   //Ĭ�ϵ�нΪ5000
    m_marketPercent = 0.05; //Ĭ���г����Ϊ5%
}

SalesManager::~SalesManager()
{

}

//��������
void SalesManager::raiseGrade()
{
    m_grade = 3;
}

//������н
void SalesManager::countSalary()
{
    cout << "������Ա�� : " << m_name << " ְλ : " << m_type << " �Ĳ��ŵ��µ����۶� : " << endl;
    cin >> m_marketMoney;

    cout << "Ա�� : " << m_name << " �Ĳ��ŵ��µ����۶�Ϊ :" << m_marketMoney << endl;
    cout << "Ա�� : " << m_name << " ���г����Ϊ : "<< m_marketPercent << endl;
    cout << "Ա�� : " << m_name << " �ĵ�нΪ : " << m_fixedSalary << endl;

    //��нΪ
    m_salary = m_marketMoney*m_marketPercent + m_fixedSalary;
}
