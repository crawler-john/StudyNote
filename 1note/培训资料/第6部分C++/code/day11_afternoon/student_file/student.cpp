#include "student.h"

int student::m_sID = 1000;


student::student(const string &t_name)

{
    strcpy(m_name,t_name.c_str());

    m_sID++;

    m_ID = m_sID;

    //�������ѧ������Ϣ
    srand(time(NULL)*m_sID);

    m_chinese = rand()%100;
    m_maths = rand()%100;
    m_english = rand()%100;

    if(rand()%2 == 1)
    {
        strcpy(m_sex,"��");
    }
    else
    {
        strcpy(m_sex,"Ů");
    }
}

//��ӡѧ����Ϣ
void student::print()
{
    /*cout << "���� : " << m_name << endl;
    cout << "ѧ�� : " << m_ID << endl;
    cout << "�Ա� : " << m_sex << endl;
    cout << "���ĳɼ� : " << m_chinese << endl;
    cout << "��ѧ�ɼ� : " << m_maths << endl;
    cout << "Ӣ��ɼ� : " << m_english << endl;*/

    cout << "����:" << m_name << "  ѧ��:" << m_ID << "  �Ա�:" << m_sex << "  ���ĳɼ�:" << m_chinese
         << "  ��ѧ�ɼ�:" << m_maths << "  Ӣ��ɼ�:" << m_english << endl;
}

