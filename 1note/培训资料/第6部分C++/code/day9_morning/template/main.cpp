#include <iostream>
#include <string>
#include "student.h"
//#include "student.cpp"

using namespace std;

//函数模板
template<class T>
const T& Max(const T& t_x,const T& t_y)
{
    return t_x > t_y ? t_x : t_y;
}

template<typename T1,typename T2>
void Swap(T1 &t_x, T1 &t_y,T2 t_b)
{
    if(t_b)
    {
        T1 temp = t_x;
        t_x = t_y;
        t_y = temp;
    }
}

int main()
{
//    int t_a = 100;
//    int t_b = 200;

//    double t_c = 10.7;
//    double t_d = 15.1;

//    char t_e = 'e';
//    char t_f = 'h';

//    //1.C++编译器根据传入实参的类型去实例化一个具体的模板函数
//    //2.调用该具体的模板函数
//    cout << "Max(const int &,const int &) : " << Max(t_a ,t_b) << endl;
//    cout << "Max(const double&,const double&) : " << Max(t_c,t_d) << endl;
//    cout << "Max(const char&,const char&) : " << Max(t_e,t_f) << endl;
////    cout << "max : " << Max(t_a,t_c) << endl;

//    char *t_p1;

//    //Swap(t_a,t_b,false);   //Swap(int&,int&,bool)
//    //Swap(t_a,t_b,t_c);     //Swap(int&,int&,double)
//    Swap(t_a,t_b,t_p1);      //Swap(int&,int&,char*)

//    cout << "t_a : " << t_a << " t_b : " << t_b << endl;

    //1.用具体类型替换模板参数,生成一个具体的模板类
    //2.用具体的模板类声明一个对象
    student<string,int> t_student1("Kate","001",20,80);
    student<char,int> t_student2;

    t_student1.getName();
    t_student1.getID();

    t_student1.getAge();
    t_student1.getWeight();

    t_student1.print();

    student<char,int>::middleStudent t_middleStudent1('3',2);

    t_middleStudent1.getGrade();
    t_middleStudent1.getClass();

    t_middleStudent1.print();





    cout << "Hello World!" << endl;
    return 0;
}

