#include <iostream>
#include "doctor.h"
#include "patient.h"

using namespace std;

int main()
{

    //创建三个病人
    Patient *t_patient = new Patient[3];

    //设置病人的姓名与血压
    #if 0
    for(int i = 0 ; i < 3; i++)
    {
        string t_patientName;
        double t_patientBloodPress;

        cout << "请输入病人 " << i+1 << " 的姓名 : " << endl;
        cin >> t_patientName;
        cout << "请输入病人 " << i+1 << " 的血压 : " << endl;
        cin >> t_patientBloodPress;

        t_patient[i].setName(t_patientName);
        t_patient[i].setBloodPress(t_patientBloodPress);
    }
    #endif

    cout << "看病前,病人的信息如下: " << endl;

    for(int i = 0; i < 3; i++)
    {
        t_patient[i].print();
        cout << endl;
    }

    //创建一个医生
    Doctor t_doctor("Hanson");

    //医生给病人看病
    for(int i = 0; i < 3; i++)
    {
        Doctor::setCurePlan(t_patient[i]);
    }

    //打印看病医生的姓名
    cout << "看病医生为 : " << t_doctor.getName() << endl;
    cout << "看病后,病人的信息如下: " << endl;

    //看病后的病人信息为
    for(int i = 0 ; i < 3; i++)
    {
        t_patient[i].print();
        cout << endl;
    }

    cout << "病人的数量是 : " << Patient::getNumber() << endl;

    //释放资源
    delete [] t_patient;
    t_patient = NULL;

    cout << "病人的数量是 : " << Patient::getNumber() << endl;










    cout << "Hello World!" << endl;
    return 0;
}

