#include <iostream>
#include "employee.h"
#include "evaluation.h"

using namespace std;

//ȫ�ֶ���,���ڱ���������ߵĹ�Ա��Ϣ
Employee g_employee;

int main()
{
    //����һ��������Ķ���
    Evaluation t_evaluation;
//    Evaluation t_evaluation2;

//    t_evaluation2 = t_evaluation;

    //�Ӽ���������Ϣ����Ա�����е�ÿ����Ա��
    t_evaluation.input();

    //Evaluation t_evaluation1(t_evaluation);

    //ѡ����������õĹ�Ա
    g_employee = t_evaluation.choice();

    //���ù�Ա�Ĺ��ʼ�50%
    g_employee.addSalary();

    //
    cout << "������ߵĹ�Ա�ӹ��ʺ����ϢΪ : " << endl;

    //����ӡ�ù�Ա����Ϣ
    g_employee.print();

    /*for(int i = 0; i < t_evaluation1.getNumber(); i++)
    {
        (t_evaluation1.getEmployee())[i].print();
        cout << "%%%%%%%%%%%%%" << endl;
    }*/

    cout << "Hello World!" << endl;
    return 0;
}

