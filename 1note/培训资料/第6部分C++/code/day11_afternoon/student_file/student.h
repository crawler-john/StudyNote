#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
#include <vector>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;

//ѧ����
class student
{
public:
    student(const string &t_name = "����");
    ~student(){/*cout << "~student()" << endl;*/}

    //��ӡѧ����Ϣ
    void print();
public:
    char m_name[50];  //����
    int m_ID;         //ѧ��
    char m_sex[5];    //�Ա�  ��/Ů
    double m_chinese; //���ĳɼ�
    double m_maths;   //��ѧ�ɼ�
    double m_english; //Ӣ��ɼ�
    static int m_sID; //�����Զ�����ѧ��
};



#endif // STUDENT_H
