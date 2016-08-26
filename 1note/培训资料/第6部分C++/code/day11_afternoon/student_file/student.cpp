#include "student.h"

int student::m_sID = 1000;


student::student(const string &t_name)

{
    strcpy(m_name,t_name.c_str());

    m_sID++;

    m_ID = m_sID;

    //随机产生学生的信息
    srand(time(NULL)*m_sID);

    m_chinese = rand()%100;
    m_maths = rand()%100;
    m_english = rand()%100;

    if(rand()%2 == 1)
    {
        strcpy(m_sex,"男");
    }
    else
    {
        strcpy(m_sex,"女");
    }
}

//打印学生信息
void student::print()
{
    /*cout << "姓名 : " << m_name << endl;
    cout << "学号 : " << m_ID << endl;
    cout << "性别 : " << m_sex << endl;
    cout << "语文成绩 : " << m_chinese << endl;
    cout << "数学成绩 : " << m_maths << endl;
    cout << "英语成绩 : " << m_english << endl;*/

    cout << "姓名:" << m_name << "  学号:" << m_ID << "  性别:" << m_sex << "  语文成绩:" << m_chinese
         << "  数学成绩:" << m_maths << "  英语成绩:" << m_english << endl;
}

