#include <iostream>
#include "person.h"

using namespace std;

int main()
{
    chinese t_chinese1;
    Japanese t_Japanese1;
    American t_American1;

    chineseMan t_chineseMan1;
    JapaneseMan t_JapaneseMan1;

    //共有继承,子类的对象可以访问父类的public区的成员(成员变量和成员函数),不能访问父类的非public区的成员
    t_chinese1.m_name;
    t_chinese1.getName();

//    t_chinese1.m_nation;
//    t_chinese1.getNation();

//    t_chinese1.m_age;
//    t_chinese1.getAge();

    //保护继承和私有继承,子类对象不能访问父类所有区间的成员
//    t_Japanese1.m_name;
//    t_Japanese1.getName();

//    t_Japanese1.m_nation;
//    t_Japanese1.getNation();

//    t_Japanese1.m_age;
//    t_Japanese1.getAge();

//    t_American1.m_name;
//    t_American1.getName();

//    t_American1.m_nation;
//    t_American1.getNation();

//    t_American1.m_age;
//    t_American1.getAge();


    //二级继承,都是共有继承,子类的子类的对象可以访问基类的public区的成员
//    t_chineseMan1.m_name;
//    t_chineseMan1.getName();

//    t_chineseMan1.m_nation;
//    t_chineseMan1.getNation();

//    t_chineseMan1.m_age;
//    t_chineseMan1.getAge();


//    t_JapaneseMan1.m_name;
//    t_JapaneseMan1.getName();

//    t_JapaneseMan1.m_nation;
//    t_JapaneseMan1.getNation();

//    t_JapaneseMan1.m_age;
//    t_JapaneseMan1.getAge();

    cout << "Hello World!" << endl;
    return 0;
}

