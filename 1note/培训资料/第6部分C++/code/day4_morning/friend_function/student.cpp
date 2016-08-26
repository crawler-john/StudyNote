#include "student.h"


void getStuScore(const student &t_student)
{
    cout << "student chinese : " << t_student.m_chinese << endl;
    cout << "student maths : " << t_student.m_maths << endl;
    cout << "student english : " << t_student.m_english << endl;
}


void teacher::setStuScore(student &t_student)
{
    t_student.m_chinese = 60;
    t_student.m_maths = 70;
    t_student.m_english = 80;
}


double Count::getStuAllScore(const student &t_student)
{
    return t_student.m_chinese + t_student.m_maths + t_student.m_english;
}

double Count::getStuAverScore(const student &t_student)
{
    return getStuAllScore(t_student)/3;
}


string student::getCountName(const Count &t_count)
{
    return t_count.m_name;
}

//����Ԫ����ʵ�ֲ�����������
ostream& operator << (ostream& os,const student &t_student)
{
    os << "ѧ�������� : " << t_student.m_name << endl;
    os << "ѧ����ѧ�� : " << t_student.m_ID << endl;
    os << "ѧ�������ĳɼ� : " << t_student.m_chinese << endl;
    os << "ѧ������ѧ�ɼ� : " << t_student.m_maths << endl;
    os << "ѧ����Ӣ��ɼ� : " << t_student.m_english << endl;

    return os;
}
istream& operator >> (istream& is,student &t_student)
{
    cout << "������ѧ�������� : " << endl;
    is >> t_student.m_name;
    cout << "������ѧ����ѧ�� : " << endl;
    is >> t_student.m_ID;

    char t_score[10];

    cout << "������ѧ�������ĳɼ� : " << endl;
    is >> t_score;
    t_student.m_chinese = atof(t_score);

    cout << "������ѧ������ѧ�ɼ� : " << endl;
    is >> t_score;
    t_student.m_maths = atof(t_score);

    cout << "������ѧ����Ӣ��ɼ� : " << endl;
    is >> t_score;
    t_student.m_english = atof(t_score);

    return is;
}
