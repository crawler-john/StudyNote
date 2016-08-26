#include <iostream>
#include "student.h"

using namespace std;


//函数参数是类对象
void getStuInfo(student t_student) //第二情况,调用copy构造函数
{
    t_student.print();
}

int main()
{
    student t_student1("Kate","006",20,"woman");
    student t_student2(t_student1);      //第一情况,调用copy构造函数

    t_student1.print();
    t_student2.print();

//    student *t_student1 = new student("Kate","006",20,"woman");
//    student *t_student2 = new student(*t_student1);

//    t_student1->print();
//    t_student2->print();

//    cout << "222222222222222222222222" << endl;

//    delete t_student1;
//    t_student1 = NULL;

//    t_student2->print();

    cout << "333333333333333333333" << endl;

    getStuInfo(t_student1);

    cout << "Hello World!" << endl;
    return 0;
}

