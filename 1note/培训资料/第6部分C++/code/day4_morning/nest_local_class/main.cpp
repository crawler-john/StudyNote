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

    private:
        string m_name;
        int m_age;
    };

    Car t_car1;

    t_car1.print();

}

int main()
{
//    animal t_animal1;

//    t_animal1.print();

//    cout << "11111111111111111111" << endl;

//    animal::bird t_bird1;

//    t_bird1.print();

//    fun1()::Car t_car1;

    fun1();


    cout << "Hello World!" << endl;
    return 0;
}

