#include <iostream>
#include "student.h"

using namespace std;


//void getStuInfo(const student &t_student)
//{
//    t_student.print();
//}

int main()
{
    student t_student1;

    t_student1.print();
    t_student1.getName();
    t_student1.getAge();

    //类的const对象和引用只能调用类的const成员函数,不能调用类的非const成员函数
    const student t_student2;

//    t_student2.print();
    t_student2.getName();
    t_student2.getAge();

    cout << "Hello World!" << endl;
    return 0;
}

