#include <iostream>
#include <vector>
#include <list>
#include "student.h"

using namespace std;

int main()
{
    vector<student> t_vec1(3,student("Rose","001",25)); //会自动调用类的copy构造函数

    cout << "vec1 size : " << t_vec1.size() << endl;

    for(int i = 0; i < 3; i++)
    {
        t_vec1[i].print();

        cout << endl;
    }

    cout << "1111111111111111111111111111" << endl;

    vector<student> t_vec2;

    for(int i = 0; i < 5; i++)
    {
        student t_student1("Kate","002",30);
        t_vec2.push_back(t_student1);        //会自动调用类的copy构造函数
    }

    for(int i = 0; i < 5; i++)
    {
        t_vec2[i].print();

        cout << endl;
    }

    cout << "2222222222222222222222222222222" << endl;

    list<student> t_list1;

    for(int i = 0; i < 5; i++)
    {
        student t_student1("Bill","003",50);
        t_list1.push_back(t_student1);       //会自动调用类的copy构造函数
    }

    cout << "33333333333333333333333333333333" << endl;

    vector<student> t_vec3(t_vec2);          //会自动调用类的copy构造函数

    for(int i = 0; i < t_vec3.size(); i++)
    {
        t_vec3[i].print();

        cout << endl;
    }

    cout << "444444444444444444444444444444444" << endl;

    vector<student*> t_vec4;

//    t_vec4.resize(t_vec2.size());

    for(int i = 0; i < t_vec2.size(); i++)
    {
        t_vec4.push_back(&t_vec2[i]);
//        t_vec4[i] = &t_vec2[i];
    }

//    for(int i = 0; i < t_vec4.size(); i++)
//    {
//        t_vec4[i]->print();
//        cout << endl;
//    }

    vector<student*>::iterator t_iter1;

    for(t_iter1 = t_vec4.begin();t_iter1 != t_vec4.end();t_iter1++)
    {
        (*t_iter1)->print();

        cout << endl;
    }

    cout << "5555555555555555555555555555555555" << endl;

    vector<student*> t_vec5(t_vec4);

    cout << "6666666666666666666666666666666666" << endl;

    vector<student*> t_vec6;

    for(int i = 0; i < 3; i++)
    {
        student *t_student = new student("Will","008",30);
        t_vec6.push_back(t_student);
    }


    for(int i = 0; i < 3; i++)
    {
        t_vec6[i]->print();

        cout << endl;
    }

    //释放资源
    for(int i = 0; i < 3; i++)
    {
        delete t_vec6[i];
        t_vec6[i] = NULL;
    }

    t_vec6.clear();

    cout << "Hello World!" << endl;
    return 0;
}

