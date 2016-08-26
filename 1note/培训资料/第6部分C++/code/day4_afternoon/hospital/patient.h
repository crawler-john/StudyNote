#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
#include "Common.h"

using namespace std;

//病人类
class Patient
{
public:
    Patient();

    Patient(const string &t_name,double t_bloodPress,Plan t_curePlan);

    //设置病人血压的函数
    void setBloodPress(double t_bloodPress)
    {
        m_bloodPress = t_bloodPress;
    }

    //设置病人的名字
    void setName(const string &t_name)
    {
        m_name = t_name;
    }

    //析构函数
    ~Patient()
    {
        m_number--;
    }

    //打印病人的信息
    void print()
    {
        cout << "patient name : " << m_name << endl;
        cout << "patient bloodPress : " << m_bloodPress << endl;
        cout << "patient curePlan : " << tran_plan(m_curePlan) << endl;
    }

    //将医生类设置为病人类的友元类
    friend class Doctor;

    //获取病人的数量
    static int getNumber() {return m_number;}

private:
    string m_name;         //病人的姓名
    double m_bloodPress;   //病人的血压
    Plan m_curePlan;       //治疗方案
    static int m_number;   //病人的数量
};

#endif // PATIENT_H
