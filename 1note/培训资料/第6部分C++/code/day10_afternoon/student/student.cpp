#include "student.h"

int student::m_sID = 1000;

bool riseChinese(student *t_stu1,student* t_stu2)
{
    return t_stu1->m_chinese < t_stu2->m_chinese;
}

bool riseMaths(student *t_stu1,student* t_stu2)
{
    return t_stu1->m_maths < t_stu2->m_maths;
}

bool riseEnglish(student *t_stu1,student* t_stu2)
{
    return t_stu1->m_english < t_stu2->m_english;
}

bool riseAllScore(student *t_stu1,student* t_stu2)
{
    double t_stuAllScore1 = t_stu1->m_chinese + t_stu1->m_maths + t_stu1->m_english;
    double t_stuAllScore2 = t_stu2->m_chinese + t_stu2->m_maths + t_stu2->m_english;

    return t_stuAllScore1 < t_stuAllScore2;
}

bool riseAvrgScore(student *t_stu1,student* t_stu2)
{
    double t_stuAvrgScore1 = (t_stu1->m_chinese + t_stu1->m_maths + t_stu1->m_english)/3;
    double t_stuAvrgScore2 = (t_stu2->m_chinese + t_stu2->m_maths + t_stu2->m_english)/3;

    return t_stuAvrgScore1 < t_stuAvrgScore2;
}

bool isMale(const string &t_sex)
{
    return t_sex == "��";
}

bool isFemale(const string &t_sex)
{
    return t_sex == "Ů";
}

bool isPass(double t_score)
{
    return t_score >= 60;
}

student::student(const string &t_name)
    :m_name(t_name)
{
    m_sID++;

    m_ID = m_sID;

    //�������ѧ������Ϣ
    srand(time(NULL)*m_sID);

    m_chinese = rand()%100;
    m_maths = rand()%100;
    m_english = rand()%100;

    if(rand()%2 == 1)
    {
        m_sex = "��";
    }
    else
    {
        m_sex = "Ů";
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

Count::Count(const vector<student*> &t_vec)
{
    //���ٿռ�
    m_stuVec.resize(t_vec.size());

    //copy����
    copy(t_vec.begin(),t_vec.end(),m_stuVec.begin());

    //�����ݷ���
    vector<student *>::iterator t_iter;

    for(t_iter = m_stuVec.begin();t_iter != m_stuVec.end();t_iter++)
    {
        m_chineseVec.push_back((*t_iter)->m_chinese);
        m_mathsVec.push_back((*t_iter)->m_maths);
        m_englishVec.push_back((*t_iter)->m_english);
        m_allScoreVec.push_back((*t_iter)->m_chinese + (*t_iter)->m_maths + (*t_iter)->m_english);
        m_avrgScoreVec.push_back(((*t_iter)->m_chinese + (*t_iter)->m_maths + (*t_iter)->m_english)/3);
        m_sexVec.push_back((*t_iter)->m_sex);
        m_stuMap.insert(pair<int,student*>((*t_iter)->m_ID,*t_iter));
    }
}

Count::~Count()
{
    m_stuVec.clear();
    m_sexVec.clear();
    m_chineseVec.clear();
    m_mathsVec.clear();
    m_englishVec.clear();
    m_allScoreVec.clear();
    m_avrgScoreVec.clear();
    m_stuMap.clear();
}

//�����ĳɼ�����
void Count::sortChinese()
{
    sort(m_chineseVec.begin(),m_chineseVec.end());
    sort(m_stuVec.begin(),m_stuVec.end(),riseChinese);

    vector<double>::iterator t_iter;

    for(t_iter = m_chineseVec.begin();t_iter != m_chineseVec.end();t_iter++)
    {
        cout << *t_iter << " ";
    }

    cout << endl;
}

//����ѧ�ɼ�����
void Count::sortMaths()
{
    sort(m_mathsVec.begin(),m_mathsVec.end());
    sort(m_stuVec.begin(),m_stuVec.end(),riseMaths);

    vector<double>::iterator t_iter;

    for(t_iter = m_mathsVec.begin();t_iter != m_mathsVec.end();t_iter++)
    {
        cout << *t_iter << " ";
    }

    cout << endl;
}

//��Ӣ��ɼ�����
void Count::sortEnglish()
{
    sort(m_englishVec.begin(),m_englishVec.end());
    sort(m_stuVec.begin(),m_stuVec.end(),riseEnglish);

    vector<double>::iterator t_iter;

    for(t_iter = m_englishVec.begin();t_iter != m_englishVec.end();t_iter++)
    {
        cout << *t_iter << " ";
    }

    cout << endl;
}

//���ܳɼ�����
void Count::sortAllScore()
{
    sort(m_allScoreVec.begin(),m_allScoreVec.end());
    sort(m_stuVec.begin(),m_stuVec.end(),riseAllScore);

    vector<double>::iterator t_iter;

    for(t_iter = m_allScoreVec.begin();t_iter != m_allScoreVec.end();t_iter++)
    {
        cout << *t_iter << " ";
    }

    cout << endl;
}

//��ƽ���ɼ�����
void Count::sortAvrgScore()
{
    sort(m_avrgScoreVec.begin(),m_avrgScoreVec.end());
    sort(m_stuVec.begin(),m_stuVec.end(),riseAvrgScore);

    vector<double>::iterator t_iter;

    for(t_iter = m_avrgScoreVec.begin();t_iter != m_avrgScoreVec.end();t_iter++)
    {
        cout << *t_iter << " ";
    }

    cout << endl;
}

//��������������
int Count::countMale()
{
    return count_if(m_sexVec.begin(),m_sexVec.end(),isMale);
}

//����Ů��������
int Count::countFemale()
{
    return count_if(m_sexVec.begin(),m_sexVec.end(),isFemale);
}

//�������ĳɼ����������
int Count::countChinese()
{
    return count_if(m_chineseVec.begin(),m_chineseVec.end(),isPass);
}

//������ѧ�ɼ����������
int Count::countMaths()
{
    return count_if(m_mathsVec.begin(),m_mathsVec.end(),isPass);
}

//����Ӣ��ɼ����������
int Count::countEnglish()
{
    return count_if(m_englishVec.begin(),m_englishVec.end(),isPass);
}

//ͨ��ѧ����ID��ѯѧ������Ϣ
student* Count::getStuInfo(int t_ID)
{
    map<int,student*>::iterator t_iter;

    t_iter = m_stuMap.find(t_ID);

    if(t_iter != m_stuMap.end())
    {
        return t_iter->second;
    }
    else
    {
        return 0;
    }
}
