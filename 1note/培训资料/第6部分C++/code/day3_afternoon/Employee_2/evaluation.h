#ifndef EVALUATION_H
#define EVALUATION_H

#include <iostream>
#include <string>
#include <algorithm>
#include "employee.h"

using namespace std;

//评价类
class Evaluation
{
public:

    //构造函数
    Evaluation();

    //copy构造函数
    Evaluation(const Evaluation &t_evaluation);

    //赋值操作符
    Evaluation& operator = (const Evaluation &t_evaluation);

    //析构函数
    ~Evaluation();

    //输入雇员的函数
    void input();

    //选择雇员得分最高的函数
    Employee& choice();

    //获取数量
    int getNumber(){return m_employeeNum;}

    //获取指针
    Employee *getEmployee() {return m_employee;}

private:
    Employee *m_employee;    //声明多个雇员的指针
    int m_employeeNum;       //雇员的数量
};

#endif // EVALUATION_H
