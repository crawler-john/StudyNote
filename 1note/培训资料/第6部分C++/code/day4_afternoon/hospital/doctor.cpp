#include "doctor.h"

Doctor::Doctor()
{
    m_name = "Bill";
}

Doctor::Doctor(const string &t_name)
    :m_name(t_name)
{
}

void Doctor::setCurePlan(Patient &t_patient)
{
    cout << "���� " << t_patient.m_name << " ��ѪѹΪ : " << t_patient.m_bloodPress << endl;

    int t_bloodPress = t_patient.m_bloodPress;

    if(t_bloodPress >= 70 && t_bloodPress <= 130)
    {
        t_patient.m_curePlan = NORMAL;
    }
    else if((t_bloodPress >=50 && t_bloodPress <=69) || (t_bloodPress >= 131 && t_bloodPress <= 150) )
    {
        t_patient.m_curePlan = MEDICINE;
    }
    else
    {
        t_patient.m_curePlan = HOSPITAL;
    }

    cout << "����ҽ��������,�ò������Ʒ���Ϊ : " << tran_plan(t_patient.m_curePlan) << endl;
}
