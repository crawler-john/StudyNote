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

//学生类
class student
{
public:
    student(const string &t_name = "匿名");
    ~student(){/*cout << "~student()" << endl;*/}

    //打印学生信息
    void print();
public:
    char m_name[50];  //姓名
    int m_ID;         //学号
    char m_sex[5];    //性别  男/女
    double m_chinese; //语文成绩
    double m_maths;   //数学成绩
    double m_english; //英语成绩
    static int m_sID; //用于自动产生学号
};



#endif // STUDENT_H
