#include <iostream>
#include "employee.h"
#include "technician.h"
#include "salesman.h"
#include "manager.h"
#include "salesmanager.h"

using namespace std;

int main()
{
    //创建4个员工对象,分别为技术员,销售员,经理,销售经理
    technician t_technician;
    salesman t_salesman;
    manager t_manager;
    SalesManager t_SalesManager;

    employee *t_array[4] = {&t_technician,&t_salesman,&t_manager,&t_SalesManager};

    //打印未升级和未计算薪水的员工信息
    for(int i = 0; i < 4; i++)
    {
        t_array[i]->print();

        cout << "-------------------------" << endl;
    }

    cout << "开始升级员工级别和计算员工月薪........" << endl;
    cout << endl;

    //将员工升级并计算月薪
    for(int i = 0; i < 4; i++)
    {
        t_array[i]->raiseGrade();
        t_array[i]->countSalary();
    }

    cout << "升级员工级别并计算月薪后..." << endl;
    cout << endl;

    //打印计算月薪后的员工信息
    for(int i = 0; i < 4; i++)
    {
        t_array[i]->print();
        cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}

