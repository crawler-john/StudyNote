#include <iostream>
#include "person.h"

using namespace std;

void getInfo(person *t_person)
{
    //动态联翩:1.用父类的指针或引用调用函数 2.被调用函数是虚函数
    t_person->play();
}

void getInfo(person &t_person)
{
    t_person.play();
}

int main()
{
    //如果一个类有虚函数,该类就只有一张虚函数表,该类的所有对象共享该类的虚函数表
    person t_person1;
    person t_person2;
    chinese t_chinese1;
    chineseMan t_chineseMan1;

    cout << "11111111111111111111111" << endl;

    getInfo(&t_person1);
    getInfo(&t_chinese1);
    getInfo(&t_chineseMan1);

    //动态联翩:编译器在运行阶段才确定使用哪个函数；
    //静态联翩:编译器在编译阶段就确定使用哪个函数；

    cout << "22222222222222222222222" << endl;

    getInfo(t_person1);
    getInfo(t_chinese1);
    getInfo(t_chineseMan1);

    cout << "33333333333333333333333" << endl;

    person *t_person3 = &t_person1;

    t_person3->eat();

    t_person3 = &t_chinese1;

    t_person3->eat();

    t_person3 = &t_chineseMan1;

    t_person3->eat();

//    chinese *t_chinese2 = &t_chineseMan1;

//    t_chinese2->eat();

    cout << "Hello World!" << endl;
    return 0;
}

