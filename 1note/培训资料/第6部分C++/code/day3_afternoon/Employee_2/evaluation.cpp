#include "evaluation.h"

Evaluation::Evaluation():m_employee(0)
{
    cout << "请输入雇员的数量 : " << endl;
    cin >> m_employeeNum;

    while(m_employeeNum > 10 || m_employeeNum < 0)
    {
        cout << "输入的雇员的数量不正确，请输入1-10" << endl;

        cout << "请重新输入雇员的数量 : (1 ~ 10)" << endl;
        cin >> m_employeeNum;
    }

}

//copy构造函数
Evaluation::Evaluation(const Evaluation &t_evaluation):m_employee(0)
{
    m_employeeNum = t_evaluation.m_employeeNum;

    m_employee = new Employee[m_employeeNum];

    for(int i = 0; i < m_employeeNum; i++)
    {
        m_employee[i] = t_evaluation.m_employee[i];
    }
}

//赋值操作符
Evaluation& Evaluation::operator = (const Evaluation &t_evaluation)
{
    cout << "Evaluation operator ========" << endl;

    if(this != &t_evaluation)
    {
        m_employeeNum = t_evaluation.m_employeeNum;

        delete [] m_employee;

        m_employee = new Employee[m_employeeNum];

        for(int i = 0; i < m_employeeNum; i++)
        {
            m_employee[i] = t_evaluation.m_employee[i];
        }
    }

    return *this;
}

//析构函数
Evaluation::~Evaluation()
{
    delete [] m_employee;
    m_employee = NULL;
}

//输入雇员的函数
void Evaluation::input()
{

    m_employee = new Employee[m_employeeNum];

    cout << "输入雇员信息完成后，打印所有雇员的信息" << endl;

    for(int i = 0; i < m_employeeNum; i++)
    {
        m_employee[i].print();
    }

    cout << "打印所有雇员信息完成！" << endl;

}

//选择雇员得分最高的函数
Employee& Evaluation::choice()
{
    if(m_employee == NULL || m_employeeNum < 0 || m_employeeNum > 10)
    {
        cout << "雇员的数量不正确或是不存在！" << endl;
        return *m_employee;
    }

    //声明一个局部的雇员对象用于交换
    Employee t_employee(DEFAULT);

    //使用冒泡排序，将存放雇员的数组进行排序
    for(int j = 0; j < m_employeeNum - 1; j++)
    {
        for(int i = 0; i < m_employeeNum - 1 -j; i++)
        {
            if(m_employee[i].getScore() > m_employee[i+1].getScore())
            {
                t_employee = m_employee[i];
                m_employee[i] = m_employee[i+1];
                m_employee[i+1] = t_employee;
            }
        }
    }

    //返回经理评分最高的雇员信息
    return m_employee[m_employeeNum-1];
}
