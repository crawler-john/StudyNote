#include <iostream>
#include "biology.h"

using namespace std;


//void readFoodInfo(const food &t_food)
//{
//    t_food.print();
//}

void fun1()
{
    biology t_biology1;
}

//全局类的对象是在main函数之前就构造好
food g_food;
game g_game;




int main()
{
    cout << "enter main function!" << endl;

    //当声明一个类的对象时,该类的构造函数会自动调用
//    biology t_biology1;
//    biology t_biology3;

//    t_biology1.print();
//    t_biology3.print();

//    cout << "2222222222222222222" << endl;

//    biology t_biology2("cat",2,3,10);

//    t_biology2.print();

//    t_biology1.setName("tiger");

//    cout << "biology name : " << t_biology1.getName() << endl;

//    t_biology1.move();

//    t_biology1.eat();


//    int t_count = 200;

//    biology t_biology1(t_count);

//    t_biology1.print();

//    t_biology1.setName("dog2");

//    t_biology1.print();

//    t_count = 300;

//    cout << "3333333333333333333" << endl;

//    t_biology1.print();

//    t_biology1.m_count = 88;

//    cout << "t_count : " << t_count << endl;


//    biology t_biology1;

//    t_biology1.print();

//    biology t_biology2("cat",20,20,2,88,"fish",2,"Dota2",2);

//    t_biology2.print();

    //t_biology2.m_biology2.print();

    //food t_food1("fish2",10);


//    readFoodInfo(food("fish2",10));

    //fun1();


//    food t_array1[5] = {food("fish1",1),food("fish2",2),food("fish3",3)};

//    for(int i = 0; i < 5; i++)
//    {
//        t_array1[i].print();

//        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
//    }

//    cout << "22222222222222222222222222" << endl;

//    food *t_array2[5];

//    for(int i = 0; i < 5; i++)
//    {
//        t_array2[i] = &t_array1[i];
//    }

//    for(int i = 0; i < 5; i++)
//    {
//        t_array2[i]->print();

//        cout << "%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
//    }






    cout << "Hello World!" << endl;
    return 0;
}

