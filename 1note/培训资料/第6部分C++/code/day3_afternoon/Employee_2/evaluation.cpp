#include "evaluation.h"

Evaluation::Evaluation():m_employee(0)
{
    cout << "�������Ա������ : " << endl;
    cin >> m_employeeNum;

    while(m_employeeNum > 10 || m_employeeNum < 0)
    {
        cout << "����Ĺ�Ա����������ȷ��������1-10" << endl;

        cout << "�����������Ա������ : (1 ~ 10)" << endl;
        cin >> m_employeeNum;
    }

}

//copy���캯��
Evaluation::Evaluation(const Evaluation &t_evaluation):m_employee(0)
{
    m_employeeNum = t_evaluation.m_employeeNum;

    m_employee = new Employee[m_employeeNum];

    for(int i = 0; i < m_employeeNum; i++)
    {
        m_employee[i] = t_evaluation.m_employee[i];
    }
}

//��ֵ������
Evaluation& Evaluation::operator = (const Evaluation &t_evaluation)
{
    cout << "Evaluation operator ========" << endl;

    if(this != &t_evaluation)
    {
        m_employeeNum = t_evaluation.m_employeeNum;

        delete [] m_employee;

        m_employee = new Employee[m_employeeNum];

        for(int i = 0; i < m_employeeNum; i++)
        {
            m_employee[i] = t_evaluation.m_employee[i];
        }
    }

    return *this;
}

//��������
Evaluation::~Evaluation()
{
    delete [] m_employee;
    m_employee = NULL;
}

//�����Ա�ĺ���
void Evaluation::input()
{

    m_employee = new Employee[m_employeeNum];

    cout << "�����Ա��Ϣ��ɺ󣬴�ӡ���й�Ա����Ϣ" << endl;

    for(int i = 0; i < m_employeeNum; i++)
    {
        m_employee[i].print();
    }

    cout << "��ӡ���й�Ա��Ϣ��ɣ�" << endl;

}

//ѡ���Ա�÷���ߵĺ���
Employee& Evaluation::choice()
{
    if(m_employee == NULL || m_employeeNum < 0 || m_employeeNum > 10)
    {
        cout << "��Ա����������ȷ���ǲ����ڣ�" << endl;
        return *m_employee;
    }

    //����һ���ֲ��Ĺ�Ա�������ڽ���
    Employee t_employee(DEFAULT);

    //ʹ��ð�����򣬽���Ź�Ա�������������
    for(int j = 0; j < m_employeeNum - 1; j++)
    {
        for(int i = 0; i < m_employeeNum - 1 -j; i++)
        {
            if(m_employee[i].getScore() > m_employee[i+1].getScore())
            {
                t_employee = m_employee[i];
                m_employee[i] = m_employee[i+1];
                m_employee[i+1] = t_employee;
            }
        }
    }

    //���ؾ���������ߵĹ�Ա��Ϣ
    return m_employee[m_employeeNum-1];
}
