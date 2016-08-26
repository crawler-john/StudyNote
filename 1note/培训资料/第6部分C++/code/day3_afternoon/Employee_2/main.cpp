#include <iostream>
#include "employee.h"
#include "evaluation.h"

using namespace std;

//获取评分最高的员工
Employee g_employee(DEFAULT);

int main()
{
    //声明一个评价类的对象
    Evaluation t_evaluation;

    //输入员工的信息
    t_evaluation.input();


    g_employee = t_evaluation.choice();

    //将评分最高的员工加工资
    g_employee.addSalary();



    //打印评分最高的员工的信息
    g_employee.print();

    cout << "Hello World!" << endl;
    return 0;
}

