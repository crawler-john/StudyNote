#include <iostream>
#include "employee.h"
#include "technician.h"
#include "salesman.h"
#include "manager.h"
#include "salesmanager.h"

using namespace std;

int main()
{
    //����4��Ա������,�ֱ�Ϊ����Ա,����Ա,����,���۾���
    technician t_technician;
    salesman t_salesman;
    manager t_manager;
    SalesManager t_SalesManager;

    employee *t_array[4] = {&t_technician,&t_salesman,&t_manager,&t_SalesManager};

    //��ӡδ������δ����нˮ��Ա����Ϣ
    for(int i = 0; i < 4; i++)
    {
        t_array[i]->print();

        cout << "-------------------------" << endl;
    }

    cout << "��ʼ����Ա������ͼ���Ա����н........" << endl;
    cout << endl;

    //��Ա��������������н
    for(int i = 0; i < 4; i++)
    {
        t_array[i]->raiseGrade();
        t_array[i]->countSalary();
    }

    cout << "����Ա�����𲢼�����н��..." << endl;
    cout << endl;

    //��ӡ������н���Ա����Ϣ
    for(int i = 0; i < 4; i++)
    {
        t_array[i]->print();
        cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}

