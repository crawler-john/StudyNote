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

//学生类
class student
{
public:
    student(const string &t_name = "匿名");
    ~student(){/*cout << "~student()" << endl;*/}

    //打印学生信息
    void print();
public:
    string m_name;    //姓名
    int m_ID;         //学号
    string m_sex;     //性别  男/女
    double m_chinese; //语文成绩
    double m_maths;   //数学成绩
    double m_english; //英语成绩
    static int m_sID; //用于自动产生学号
};

//统计类
class Count
{
public:
    Count(){}
    Count(const vector<student*> &t_vec);
    ~Count();

    void sortChinese();         //给语文成绩排序
    void sortMaths();           //给数学成绩排序
    void sortEnglish();         //给英语成绩排序
    void sortAllScore();        //给总成绩排序
    void sortAvrgScore();       //给平均成绩排序

    int countMale();           //计算男生的数量
    int countFemale();         //计算女生的数量
    int countChinese();        //计算语文成绩及格的人数
    int countMaths();          //计算数学成绩及格的人数
    int countEnglish();        //计算英语成绩及格的人数

    student* getStuInfo(int t_ID);  //通过学生的ID查询学生的信息

    vector<student*>::iterator m_iter1;

    vector<student *> m_stuVec;     //存放学生信息的数组

private:

    vector<string> m_sexVec;        //存放学生性别的数组
    vector<double> m_chineseVec;    //存放语文成绩的数组
    vector<double> m_mathsVec;      //存放数学成绩的数组
    vector<double> m_englishVec;    //存放英语成绩的数组
    vector<double> m_allScoreVec;   //存放总成绩数组
    vector<double> m_avrgScoreVec;  //存放平均成绩数组
    map<int,student*> m_stuMap;     //用于查询信息
};

#endif // STUDENT_H
