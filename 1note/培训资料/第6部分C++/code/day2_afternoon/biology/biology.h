#ifndef BIOLOGY_H
#define BIOLOGY_H

#include <iostream>
#include <string>
#include "food.h"

using namespace std;

class biology
{
public:

    //当没有自定义自己的构造函数时,C++编译器会自动生成一个默认的public,无参的构造函数

    //构造函数没有返回值
    //构造函数名与类名一样
    //构造函数可以有参数
    //构造函数可以重载，可以有N个
    //当自定义构造函数后,C++编译器就不会再生成默认的构造函数
    biology(const int &t_count = 100);

    biology(const string &t_name,int t_height,int t_weight,int t_age,const int &t_count,const string &t_foodName,int t_time,const string &t_gameName,int t_level);

    //析构函数没有返回值,没有参数,不能重载,只能有一个
    //当对象被销毁时,自动调用
    //不管是否自定义一个析构函数,C++编译器都会生成一个默认的析构函数；
    //析构函数调用的顺序与构造函数调用的顺序相反
    ~biology()
    {
        cout << "~biology()" << endl;
    }

    void move();    //生物在移动

    void eat();     //生物在吃饭

    void setName(const string &t_name);  //设置生物的名字

    string getName();  //获取生物的名字

    void print();

private:

    string m_name;
    int m_height;
    int m_weight;
    int m_age;


    const int m_number = 2000;  //c++2011标准支持

    int &m_height2;
    const int &m_count;

private:


    //类的组合:一个类的对象是另外一个类的成员
    //构造函数调用的顺序,先调用组合类的构造函数构造对象,再调用自己的构造函数
    food m_food;
    game m_game;

    //biology m_biology;      //类的成员变量不能有该类的对象,会造成死循环
    biology *m_biology1;

public:

    biology &m_biology2;

};

#endif // BIOLOGY_H
