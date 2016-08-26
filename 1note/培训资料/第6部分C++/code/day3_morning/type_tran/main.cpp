#include <iostream>
#include "car.h"

using namespace std;

void getCarInfo(const car &t_car)
{
    t_car.print();
}

int main()
{
//    int t_a = 10;
//    double t_b = 20.9;

//    double t_c = t_a + t_b;

//    cout << "t_c : " << t_c << endl;

//    double t_d = 10.8;
//    double t_e = 20.9;

//    int t_f = t_d + t_e;

//    cout << "t_f : " << t_f << endl;


//    int t_array1[3] = {1,2,3};

//    int *t_p1 = t_array1;

//    for(int i = 0; i < 3; i++)
//    {
//        cout << t_p1[i] << " ";
//    }

//    cout << endl;

//    t_f = 0;

//    char *t_p2 = NULL;

//    if(t_p2)
//    {
//        cout << "success!" << endl;
//    }
//    else
//    {
//        cout << "failed!" << endl;
//    }






//    car t_car1;
//    car t_car2("Toyota");
//    car t_car3(5);
//    car t_car4("QQ",3);

//    cout << "222222222222222222222" << endl;

    car t_car5 = "mazida";    //一个参数的构造函数的隐式转换,情况一
    car t_car6 = 100;

//    cout << "333333333333333333333" << endl;

//    t_car1.print();
//    t_car2.print();
//    t_car3.print();
//    t_car4.print();

    cout << "4444444444444444444444" << endl;
    t_car5.print();
    t_car6.print();

//    cout << "55555555555555555555555" << endl;

//    getCarInfo(t_car4);


//    cout << "666666666666666666666" << endl;

//    getCarInfo("888");       //一个参数的构造函数的隐式转换,情况二
//    getCarInfo(200);







//    int t_a = 10;
//    //double t_b = static_cast<double>(t_a);
//    double t_b = (double)t_a;
//    cout << "t_b : " << t_b << endl;

//    int t_c = 'a';
//    int *t_p1 = &t_c;
//    //char *t_p2 = reinterpret_cast<char *>(t_p1);
//    char *t_p2 = (char*)t_p1;

//    cout << "*t_p1 : " << *t_p1 << endl;
//    cout << "*t_p2 : " << *t_p2 << endl;


    cout << "Hello World!" << endl;
    return 0;
}

