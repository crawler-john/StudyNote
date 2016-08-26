#include <iostream>
#include "student.h"

using namespace std;

int main()
{
//    student t_student1("Bill","001",23,"man2");
//    student t_student2("Rose","005",25,"woman1");
//    student t_student3;

//    t_student1.print();
//    t_student2.print();

//    cout << "111111111111111111111111" << endl;

//    //没有自定义赋值操作符,C++编译器会生成一个默认的赋值操作符
//    t_student3 = t_student2 = t_student1;

//    //t_student3.operator =(t_student2.operator =(t_student1));

//    t_student1.print();
//    t_student2.print();
//    t_student3.print();

    student *t_student1 = new student("Bill","001",23,"man2");
    student *t_student2 = new student("Rose","005",25,"woman1");

    t_student1->print();
    t_student2->print();

    cout << "1111111111111111111111111111" << endl;

    *t_student2 = *t_student1;

    t_student1->print();
    t_student2->print();

    delete t_student1;
    t_student1 = NULL;

    cout << "22222222222222222222222222" << endl;

    t_student2->print();




    cout << "Hello World!" << endl;
    return 0;
}

