#include <iostream>
#include "fun1.h"

using namespace std;


#define pi 3.14159

double g_area = 0;

//引用作为函数的返回值,好处:减少一次拷贝,提高效率
//注意当函数的返回值为引用类型时，不要将一个临时变量返回出去；
double& getRoundArea(double t_r)
{
    //double t_area = pi * t_r * t_r;

    g_area = pi * t_r * t_r;
    return g_area;
}

void fun1()
{
    double temp1 = 10.111;
}

void fun2()
{
    double temp2 = 22.222;
}


int main()
{
//    int t_a = 100;
//    int t_b = 200;

//    double t_e = 20.9;

//    //引用必须初始化,一个变量可以有多个引用
//    //一个引用不能同时绑定多个变量
//    //引用必须和变量是同一个类型
//    int &t_c = t_a;

//    cout << "&t_a : " << &t_a << " t_a : " << t_a << endl;
//    cout << "&t_c : " << &t_c << " t_c : " << t_c << endl;
//    cout << "&t_b : " << &t_b << " t_b : " << t_b << endl;

//    t_c = 300;

//    cout << "&t_a : " << &t_a << " t_a : " << t_a << endl;
//    cout << "&t_c : " << &t_c << " t_c : " << t_c << endl;

//    t_a = 500;
//    cout << "&t_a : " << &t_a << " t_a : " << t_a << endl;
//    cout << "&t_c : " << &t_c << " t_c : " << t_c << endl;

//    int &t_d = t_a;

//    cout << "1111111111111111111111111111" << endl;

//    cout << "&t_a : " << &t_a << " t_a : " << t_a << endl;
//    cout << "&t_c : " << &t_c << " t_c : " << t_c << endl;
//    cout << "&t_d : " << &t_d << " t_d : " << t_d << endl;

//    t_c = t_b;

//    cout << "22222222222222222222222222222222" << endl;


//    cout << "&t_a : " << &t_a << " t_a : " << t_a << endl;
//    cout << "&t_c : " << &t_c << " t_c : " << t_c << endl;
//    cout << "&t_d : " << &t_d << " t_d : " << t_d << endl;
//    cout << "&t_b : " << &t_b << " t_b : " << t_b << endl;

//    //int &t_f = t_e;

//    int t_h = 400;
//    int t_k = 500;

//    //指针的引用
//    int *t_p1 = &t_h;

//    int *&t_p2 = t_p1;

//    cout << "&t_p1 : " << &t_p1 << " t_p1 : " << t_p1 << " *t_p1 : " << *t_p1 << endl;
//    cout << "&t_p2 : " << &t_p2 << " t_p2 : " << t_p2 << " *t_p2 : " << *t_p2 << endl;

//    //没有数组的引用
////    int t_array1[3] = {1,2,3};
////    int &t_array2[3] = t_array1[3];

//    cout << "33333333333333333333333333333333" << endl;


//    const int &t_j = t_k;

//    cout << "&t_k : " << &t_k << " t_k : " << t_k << endl;
//    cout << "&t_j : " << &t_j << " t_j : " << t_j << endl;

////    t_j = 600;

//    t_k = 600;

//    cout << "&t_k : " << &t_k << " t_k : " << t_k << endl;
//    cout << "&t_j : " << &t_j << " t_j : " << t_j << endl;


//    int t_a = 200;
//    int t_b = 300;

//    cout << "before t_a : " << t_a << endl;
//    cout << "before t_b : " << t_b << endl;

//    //Swap(&t_a,&t_b);
//    Swap2(t_a,t_b);

//    cout << "after t_a : " << t_a << endl;
//    cout << "after t_b : " << t_b << endl;

//    Animal t_animal1 = {"tiger",5,200};

//    readAnimalInfo(t_animal1);

//    writeAnimalInfo(t_animal1);

//    readAnimalInfo(t_animal1);

//    double t_r = 10.0;

//    double &t_area = getRoundArea(t_r);

//    cout << "area : " << t_area << endl;

//    fun1();

//    cout << "area : " << t_area << endl;

//    fun2();

//    cout << "area : " << t_area << endl;

    string t_str1("123");
    string t_str2 = "12";

    cout << "t_str1 : " << t_str1 << endl;
    cout << "t_str2 : " << t_str2 << endl;

    cout << "str1 length : " << t_str1.length() << endl;
    cout << "str2 length : " << strlen(t_str2.c_str()) << endl;

    cout << "max string : " << Max_string(t_str1,t_str2) << endl;
    cout << "max string1 : " << Max_string(t_str1,"23456") << endl;

    cout << "Hello World!" << endl;
    return 0;
}

