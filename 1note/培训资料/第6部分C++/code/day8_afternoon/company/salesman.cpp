#include "salesman.h"

int salesman::m_salesNumber = 0;

//���캯��
salesman::salesman()
{
    m_type = "��ְ����Ա";
    m_marketMoney = 0;       //Ĭ���г������۶�Ϊ0
    m_marketPercent = 0.04;  //Ĭ���������Ϊ4%

    //������Ա������һ
    m_salesNumber++;

}

//��������
salesman::~salesman()
{
    //������Ա������һ
    m_salesNumber--;
}

//��������
void salesman::raiseGrade()
{
    m_grade = 1;
}

//������н
void salesman::countSalary()
{
    cout << "������Ա�� : " << m_name << " ְλ : " << m_type << " �ĵ��µ��г����۶� : " << endl;
    cin >> m_marketMoney;

    cout << "Ա�� : " << m_name << " �ĵ��µ��г����۶�Ϊ : " << m_marketMoney << endl;
    cout << "Ա�� : " << m_name << " ���г����Ϊ : " << m_marketPercent << endl;

    //��нΪ
    m_salary = m_marketMoney*m_marketPercent;
}
