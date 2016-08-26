#include <iostream>
#include "employee.h"
#include "evaluation.h"

using namespace std;

//全局对象,用于保存评分最高的雇员信息
Employee g_employee;

int main()
{
    //声明一个评价类的对象
    Evaluation t_evaluation;
//    Evaluation t_evaluation2;

//    t_evaluation2 = t_evaluation;

    //从键盘输入信息到雇员数组中的每个雇员中
    t_evaluation.input();

    //Evaluation t_evaluation1(t_evaluation);

    //选择经理评分最好的雇员
    g_employee = t_evaluation.choice();

    //将该雇员的工资加50%
    g_employee.addSalary();

    //
    cout << "评分最高的雇员加工资后的信息为 : " << endl;

    //最后打印该雇员的信息
    g_employee.print();

    /*for(int i = 0; i < t_evaluation1.getNumber(); i++)
    {
        (t_evaluation1.getEmployee())[i].print();
        cout << "%%%%%%%%%%%%%" << endl;
    }*/

    cout << "Hello World!" << endl;
    return 0;
}

