#include "manager.h"

manager::manager()
{
    m_type = "����";

    m_fixedSalary = 8000;  //Ĭ�ϵ�нΪ8000
}

manager::~manager()
{

}

//��������
void manager::raiseGrade()
{
    m_grade = 4;
}

//������н
void manager::countSalary()
{

    cout << "Ա�� : " << m_name << " ְλ : " << m_type << "�ĵ�нΪ : " << m_fixedSalary << endl;

    //��нΪ
    m_salary = m_fixedSalary;

}
