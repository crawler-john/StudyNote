#include <iostream>
#include <fstream>
#include <stdio.h>
#include "student.h"

using namespace std;

#define NUM 20

int main()
{
    string t_name[NUM]={"诸葛","司马","赵云","关羽","张飞",
                        "黄忠","马超","刘备","魏延","曹仁",
                        "夏侯","吕布","典韦","许褚","貂蝉",
                        "周瑜","黄盖","鲁肃","孙权","吕蒙"};

    //用于存放20个学生信息的数组
    vector<student *> t_stuVec;

    for(int i = 0; i < NUM; i++)
    {
        student *t_student = new student(t_name[i]);

        t_stuVec.push_back(t_student);
    }

    cout << "20个学生的信息如下 : " << endl;

    for(int i = 0; i < NUM; i++)
    {
        t_stuVec[i]->print();
        cout << endl;
    }

    cout << "2222222222222222222222222222222222" << endl;

    //声明统计对象
    Count t_count(t_stuVec);

    //获取男,女生的数量
    cout << "男生的数量为 : " << t_count.countMale() << endl;
    cout << "女生的数量为 : " << t_count.countFemale() << endl;

    //获取及格的人数
    cout << "语文成绩及格的人数为 : " << t_count.countChinese() << endl;
    cout << "数学成绩及格的人数为 : " << t_count.countMaths() << endl;
    cout << "英语成绩及格的人数为 : " << t_count.countEnglish() << endl;

    //排序
    cout << "语文成绩排序为 : ";
    t_count.sortChinese();

    for(t_count.m_iter1 = t_count.m_stuVec.begin();t_count.m_iter1 != t_count.m_stuVec.end();t_count.m_iter1++)
    {
        (*(t_count.m_iter1))->print();

        cout << "################" << endl;
    }

    cout << "数学成绩排序为 : ";
    t_count.sortMaths();

    cout << "英语成绩排序为 : ";
    t_count.sortEnglish();

    cout << "总成绩排序为 : ";
    t_count.sortAllScore();

    cout << "平均成绩排序为 : ";
    t_count.sortAvrgScore();

    cout << "可以通过学生的ID查询学生的信息" << endl;

    cout << "请输入要查询学生的ID : " << endl;

    int t_ID;

    cin >> t_ID;

    cout << "学生ID : " << t_ID << "的信息如下 : " << endl;

    if(t_count.getStuInfo(t_ID) != NULL)
    {
        (t_count.getStuInfo(t_ID))->print();
    }
    else
    {
        cout << "学生信息不存在！" << endl;
    }

    //释放资源
    for(int i = 0; i < NUM; i++)
    {
        delete t_stuVec[i];
        t_stuVec[i] = NULL;
    }

    t_stuVec.clear();

    cout << "Hello World!" << endl;
    return 0;
}

