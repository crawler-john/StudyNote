#include "biology.h"

//构造函数初始化类的成员变量
 biology::biology(const int &t_count):m_number(1000),m_height2(m_height),m_count(t_count),m_biology1(0),m_biology2(*this)
{
    cout << "biology()" << endl;

    m_name = "dog";
    m_height = 20;
    m_weight = 30;
    m_age = 3;



    //m_number = 1000;

}

//类的初始化列表初始化类的成员变量是在构造函数调用之前就初始化好了
//类的成员变量初始化的顺序与初始化列表中的顺序无关,与成员变量在类中声明的顺序相关
biology::biology(const string &t_name, int t_height, int t_weight, int t_age,const int &t_count,const string &t_foodName,int t_time,const string &t_gameName,int t_level)
    :m_height(t_height),m_name(t_name),m_weight(t_weight),m_age(t_age),m_number(1000),
      m_height2(m_height),m_count(t_count),m_food(t_foodName,t_time),m_game(t_gameName,t_level),m_biology1(0),m_biology2(*this)
{
    cout << "biology(...)" << endl;

//    m_name = t_name;
//    m_weight = t_weight;
//    m_height = t_height;
//    m_age = t_age;

    //m_number = 1000;

    m_height2 = m_height;

    //显示调用类的构造函数,会产生一个无名对象
    //无名对象的生存周期很短,会马上销毁
//    m_food = food(t_foodName,t_time);
//    m_game = game(t_gameName,t_level);
}

void biology::move()
{
    cout << "biology : " << m_name << " move! " << endl;
}

void biology::eat()
{
    cout << "biology : " << m_name << " eat! " << endl;
}

void biology::setName(const string &t_name)
{
    m_name = t_name;
}

string biology::getName()
{
    return m_name;
}

void biology::print()
{
    cout << "biology name : " << m_name << endl;
    cout << "biology height : " << m_height << endl;
    cout << "biology weight : " << m_weight << endl;
    cout << "biology age : " << m_age << endl;
    cout << "biology number : " << m_number << endl;
    cout << "biology height2 : " << m_height2 << endl;
    cout << "biology count : " << m_count << endl;

    m_food.print();
    m_game.print();
}




