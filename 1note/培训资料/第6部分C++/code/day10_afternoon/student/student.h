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
    string m_name;    //����
    int m_ID;         //ѧ��
    string m_sex;     //�Ա�  ��/Ů
    double m_chinese; //���ĳɼ�
    double m_maths;   //��ѧ�ɼ�
    double m_english; //Ӣ��ɼ�
    static int m_sID; //�����Զ�����ѧ��
};

//ͳ����
class Count
{
public:
    Count(){}
    Count(const vector<student*> &t_vec);
    ~Count();

    void sortChinese();         //�����ĳɼ�����
    void sortMaths();           //����ѧ�ɼ�����
    void sortEnglish();         //��Ӣ��ɼ�����
    void sortAllScore();        //���ܳɼ�����
    void sortAvrgScore();       //��ƽ���ɼ�����

    int countMale();           //��������������
    int countFemale();         //����Ů��������
    int countChinese();        //�������ĳɼ����������
    int countMaths();          //������ѧ�ɼ����������
    int countEnglish();        //����Ӣ��ɼ����������

    student* getStuInfo(int t_ID);  //ͨ��ѧ����ID��ѯѧ������Ϣ

    vector<student*>::iterator m_iter1;

    vector<student *> m_stuVec;     //���ѧ����Ϣ������

private:

    vector<string> m_sexVec;        //���ѧ���Ա������
    vector<double> m_chineseVec;    //������ĳɼ�������
    vector<double> m_mathsVec;      //�����ѧ�ɼ�������
    vector<double> m_englishVec;    //���Ӣ��ɼ�������
    vector<double> m_allScoreVec;   //����ܳɼ�����
    vector<double> m_avrgScoreVec;  //���ƽ���ɼ�����
    map<int,student*> m_stuMap;     //���ڲ�ѯ��Ϣ
};

#endif // STUDENT_H
