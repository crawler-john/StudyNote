#ifndef DOCTOR_H
#define DOCTOR_H

#include "patient.h"

class Doctor
{
public:
    Doctor();
    Doctor(const string &t_name);
    ~Doctor(){}

    //根据病人的情况，为病人设置治疗方案
    static void setCurePlan(Patient &t_patient);

    string& getName() {return m_name;}

private:
    string m_name;   //医生的名字
};

#endif // DOCTOR_H
