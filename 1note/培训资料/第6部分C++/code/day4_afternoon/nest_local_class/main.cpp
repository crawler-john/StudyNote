#include <iostream>
#include "animal.h"

using namespace std;

void fun1()
{
    //局部类
    class Car
    {
    public:

        Car()
        {
            cout << "Car()" << endl;
            m_name = "BMW";
            m_age = 1;
        }

        ~Car()
        {
            cout << "~Car()" << endl;
        }

        //局部类的成员函数必须是内联函数
        void print()
        {
            cout << "car name : " << m_name << endl;
            cout << "car age : " << m_age << endl;
        }

        //局部类可以有静态成员函数,通过传参可以间接访问类的非静态成员
        static string getName(Car &t_car)
        {
            t_car.print();

            return t_car.m_name;
        }

    private:
        string m_name;
        int m_age;

        //局部类不能有静态成员变量
        //static int m_number;
    };



    Car t_car1;

    //t_car1.print();

    cout << "car1 name : " << Car::getName(t_car1) << endl;

}

int main()
{
//    animal t_animal1;
//    animal::bird t_bird1;

//    cout << "animal number : " << animal::getNumber() << endl;
//    cout << "bird number : " << animal::bird::getNumber() << endl;


    fun1();


    cout << "Hello World!" << endl;
    return 0;
}

