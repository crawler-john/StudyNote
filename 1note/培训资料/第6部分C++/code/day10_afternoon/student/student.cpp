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
    return t_sex == "男";
}

bool isFemale(const string &t_sex)
{
    return t_sex == "女";
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

    //随机产生学生的信息
    srand(time(NULL)*m_sID);

    m_chinese = rand()%100;
    m_maths = rand()%100;
    m_english = rand()%100;

    if(rand()%2 == 1)
    {
        m_sex = "男";
    }
    else
    {
        m_sex = "女";
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

Count::Count(const vector<student*> &t_vec)
{
    //开辟空间
    m_stuVec.resize(t_vec.size());

    //copy数据
    copy(t_vec.begin(),t_vec.end(),m_stuVec.begin());

    //将数据分流
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

//给语文成绩排序
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

//给数学成绩排序
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

//给英语成绩排序
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

//给总成绩排序
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

//给平均成绩排序
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

//计算男生的数量
int Count::countMale()
{
    return count_if(m_sexVec.begin(),m_sexVec.end(),isMale);
}

//计算女生的数量
int Count::countFemale()
{
    return count_if(m_sexVec.begin(),m_sexVec.end(),isFemale);
}

//计算语文成绩及格的人数
int Count::countChinese()
{
    return count_if(m_chineseVec.begin(),m_chineseVec.end(),isPass);
}

//计算数学成绩及格的人数
int Count::countMaths()
{
    return count_if(m_mathsVec.begin(),m_mathsVec.end(),isPass);
}

//计算英语成绩及格的人数
int Count::countEnglish()
{
    return count_if(m_englishVec.begin(),m_englishVec.end(),isPass);
}

//通过学生的ID查询学生的信息
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
