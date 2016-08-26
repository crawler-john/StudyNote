#include <iostream>
#include <fstream>
#include <stdio.h>
#include "student.h"

using namespace std;

#define NUM 20

int main()
{
    string t_name[NUM]={"���","˾��","����","����","�ŷ�",
                        "����","��","����","κ��","����",
                        "�ĺ�","����","��Τ","����","����",
                        "���","�Ƹ�","³��","��Ȩ","����"};

    //���ڴ��20��ѧ����Ϣ������
    vector<student *> t_stuVec;

    for(int i = 0; i < NUM; i++)
    {
        student *t_student = new student(t_name[i]);

        t_stuVec.push_back(t_student);
    }

    cout << "20��ѧ������Ϣ���� : " << endl;

    for(int i = 0; i < NUM; i++)
    {
        t_stuVec[i]->print();
        cout << endl;
    }

    cout << "2222222222222222222222222222222222" << endl;

    //����ͳ�ƶ���
    Count t_count(t_stuVec);

    //��ȡ��,Ů��������
    cout << "����������Ϊ : " << t_count.countMale() << endl;
    cout << "Ů��������Ϊ : " << t_count.countFemale() << endl;

    //��ȡ���������
    cout << "���ĳɼ����������Ϊ : " << t_count.countChinese() << endl;
    cout << "��ѧ�ɼ����������Ϊ : " << t_count.countMaths() << endl;
    cout << "Ӣ��ɼ����������Ϊ : " << t_count.countEnglish() << endl;

    //����
    cout << "���ĳɼ�����Ϊ : ";
    t_count.sortChinese();

    for(t_count.m_iter1 = t_count.m_stuVec.begin();t_count.m_iter1 != t_count.m_stuVec.end();t_count.m_iter1++)
    {
        (*(t_count.m_iter1))->print();

        cout << "################" << endl;
    }

    cout << "��ѧ�ɼ�����Ϊ : ";
    t_count.sortMaths();

    cout << "Ӣ��ɼ�����Ϊ : ";
    t_count.sortEnglish();

    cout << "�ܳɼ�����Ϊ : ";
    t_count.sortAllScore();

    cout << "ƽ���ɼ�����Ϊ : ";
    t_count.sortAvrgScore();

    cout << "����ͨ��ѧ����ID��ѯѧ������Ϣ" << endl;

    cout << "������Ҫ��ѯѧ����ID : " << endl;

    int t_ID;

    cin >> t_ID;

    cout << "ѧ��ID : " << t_ID << "����Ϣ���� : " << endl;

    if(t_count.getStuInfo(t_ID) != NULL)
    {
        (t_count.getStuInfo(t_ID))->print();
    }
    else
    {
        cout << "ѧ����Ϣ�����ڣ�" << endl;
    }

    //�ͷ���Դ
    for(int i = 0; i < NUM; i++)
    {
        delete t_stuVec[i];
        t_stuVec[i] = NULL;
    }

    t_stuVec.clear();

    cout << "Hello World!" << endl;
    return 0;
}

