#include "evaluation.h"

Evaluation::Evaluation():m_employee(0)
{
    cout << "�������Ա������ : " << endl;
    cin >> m_employeeNum;

    if(m_employeeNum > 10 || m_employeeNum < 0)
    {
        cout << "����Ĺ�Ա����������ȷ��������1-10" << endl;
        return;
    }

    //�����Ա�Ķ���
    m_employee = new Employee[m_employeeNum];

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

    //copy(t_evaluation.m_employee,t_evaluation.m_employee + m_employeeNum,m_employee);
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
    if(m_employeeNum > 10 || m_employeeNum < 0)
    {
        cout << "��Ա����������ȷ" << endl;
        return;
    }

    for(int i = 0; i < m_employeeNum; i++)
    {     
        //��ʱ���������ڱ���Ӽ������������
        string t_name;
        double t_score;
        cout << "�������Ա " << i + 1 << " ������" << endl;
        cin >> t_name;
        cout << "�������Ա " << i + 1 << " �ľ������������" << endl;
        cin >> t_score;

        //���������뵽��Ա��
        m_employee[i] = Employee(t_name,t_score);
    }

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
    Employee t_employee;

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
