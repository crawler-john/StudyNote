#include <iostream>
#include <malloc.h>
#include "student.h"

using namespace std;

int main()
{
//    int *t_p1 = (int*)malloc(sizeof(int));

//    *t_p1 = 100;

//    cout << "*t_p1 : " << *t_p1 << endl;

//    free(t_p1);

//    t_p1 = NULL;

//    int *t_p2 = new int;

//    *t_p2 = 200;

//    cout << "*t_p2 : " << *t_p2 << endl;

//    delete t_p2;
//    t_p2 = NULL;

//    int *t_p3 = new int(5);

//    cout << *t_p3 << endl;

//    delete t_p3;
//    t_p3 = NULL;

//    int *t_p4 = new int[10];

//    for(int i = 0 ; i < 10; i++)
//    {
//        t_p4[i] = i + 1;
//        cout << t_p4[i] << " ";
//    }

//    cout << endl;

//    //释放空间
//    delete [] t_p4;
//    t_p4 = NULL;

//    int *t_array1[3];
//    //int (*t_array2)[3];

//    for(int i = 0; i < 3; i++)
//    {
//        t_array1[i] = new int[2];

//        for(int j = 0; j < 2; j++)
//        {
//            t_array1[i][j] = i + j + 1;
//        }
//    }

//    for(int i = 0; i < 3; i++)
//    {
//        for(int j = 0; j < 2; j++)
//        {
//            cout << t_array1[i][j] << " ";
//        }

//        cout << endl;
//    }

//    //释放空间
//    for(int i = 0; i < 3; i++)
//    {
//        delete [] t_array1[i];
//        t_array1[i] = NULL;
//    }

//    cout << "22222222222222222222222222222222" << endl;

//    int (*t_array2)[3] = new int[2][3];

//    for(int i = 0; i < 2; i++)
//    {
//        for(int j = 0; j < 3; j++)
//        {
//            t_array2[i][j] = i + j + 1;
//        }
//    }

//    for(int i = 0; i < 2; i++)
//    {
//        for(int j = 0; j < 3; j++)
//        {
//            cout << t_array2[i][j] << " ";
//        }

//        cout << endl;
//    }

//    //释放空间
//    delete [] t_array2;
//    t_array2 = NULL;

//    //new一个类的对象,会自动调用该类相应的构造函数
//    student *t_student1 = new student;
//    student *t_student2 = new student("Rose","003",30);

//    t_student1->print();
//    t_student2->print();

//    //释放资源,delete一个类对象,会自动调用该类的析构函数
//    delete t_student1;
//    t_student1 = NULL;

//    delete t_student2;
//    t_student2 = NULL;

//    student *t_student3 = new student[3];

//    for(int i = 0; i < 3; i++)
//    {
//        t_student3[i].print();

//        cout << "~~~~~~~~~~~~~~~~~~~~~" << endl;
//    }

//    cout << "2222222222222222222222" << endl;

//    //释放资源
//    delete [] t_student3;
//    t_student3 = NULL;

//    cout << "333333333333333333333333" << endl;

//    student *t_array1[3];

//    for(int i = 0 ; i < 3; i++)
//    {
//        t_array1[i] = new student[2]{student(),student("Kate","002",20)};
//    }

//    cout << "444444444444444444444" << endl;

//    for(int i = 0; i < 3; i++)
//    {
//        for(int j = 0; j < 2; j++)
//        {
//            t_array1[i][j].print();
//        }

//        cout << endl;
//    }

//    //释放资源
//    for(int i = 0; i < 3; i++)
//    {
//        delete [] t_array1[i];
//        t_array1[i] = NULL;
//    }

//    cout << "5555555555555555555555555" << endl;

    student (*t_array2)[3] = new student[2][3];

    //释放资源
    delete [] t_array2;
    t_array2 = NULL;

//    cout << "Hello World!" << endl;
//    return 0;
}

