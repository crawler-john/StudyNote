#include <iostream>
#include "student.h"

using namespace std;

int main()
{
    student t_student1;



    //在类外,类的对象只能访问类的public区的成员(成员变量和成员函数),不能访问类的非public区的成员
    t_student1.m_name;
    t_student1.getName();

//    t_student1.m_ID;
//    t_student1.getID();

//    t_student1.m_age;
//    t_student1.getAge();

    //用类的引用调用类的成员
    student &t_student2 = t_student1;

    t_student2.m_name;
    t_student2.getName();

    //用类的指针调用类的成员
    student *t_student3 = &t_student1;

    t_student3->m_name;
    t_student3->getName();

    cout << "t_student1 address : " << &t_student1 << endl;


    cout << "student name : " << t_student3->getName() << endl;

    t_student1.setName("Jack");


    cout << "student name : " << t_student3->getName() << endl;


    t_student1.setInfo("Will");

    t_student1.print();

    t_student1.setInfo("Kate","001");

    t_student1.print();

    string t_name = "Bill";

    t_student1.setInfo(t_name,"002",20);

    t_student1.print();


    cout << "Hello World!" << endl;

	cout << __DATE__ << endl;
	cout << __TIME__ << endl;
    return 0;
}


