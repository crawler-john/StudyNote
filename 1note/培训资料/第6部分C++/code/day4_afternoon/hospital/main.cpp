#include <iostream>
#include "doctor.h"
#include "patient.h"

using namespace std;

int main()
{

    //������������
    Patient *t_patient = new Patient[3];

    //���ò��˵�������Ѫѹ
    #if 0
    for(int i = 0 ; i < 3; i++)
    {
        string t_patientName;
        double t_patientBloodPress;

        cout << "�����벡�� " << i+1 << " ������ : " << endl;
        cin >> t_patientName;
        cout << "�����벡�� " << i+1 << " ��Ѫѹ : " << endl;
        cin >> t_patientBloodPress;

        t_patient[i].setName(t_patientName);
        t_patient[i].setBloodPress(t_patientBloodPress);
    }
    #endif

    cout << "����ǰ,���˵���Ϣ����: " << endl;

    for(int i = 0; i < 3; i++)
    {
        t_patient[i].print();
        cout << endl;
    }

    //����һ��ҽ��
    Doctor t_doctor("Hanson");

    //ҽ�������˿���
    for(int i = 0; i < 3; i++)
    {
        Doctor::setCurePlan(t_patient[i]);
    }

    //��ӡ����ҽ��������
    cout << "����ҽ��Ϊ : " << t_doctor.getName() << endl;
    cout << "������,���˵���Ϣ����: " << endl;

    //������Ĳ�����ϢΪ
    for(int i = 0 ; i < 3; i++)
    {
        t_patient[i].print();
        cout << endl;
    }

    cout << "���˵������� : " << Patient::getNumber() << endl;

    //�ͷ���Դ
    delete [] t_patient;
    t_patient = NULL;

    cout << "���˵������� : " << Patient::getNumber() << endl;










    cout << "Hello World!" << endl;
    return 0;
}

