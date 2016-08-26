#include <iostream>
#include "person.h"

using namespace std;

void getPersonInfo(person t_person)
{
    t_person.print();
}

void getPersonInfo(person *t_person)
{
    t_person->print();
}

int main()
{
    person t_person1;
    person t_person2("Kate","Japan",20);
    person t_person3("Bill","USA",30);

    chinese t_chinese1("Lucy","china",20,"fish1");
    chinese t_chinese2("Lily","china2",25,"fish2");
    chinese t_chinese3("Jack","china3",28,"fish3");

    cout << "11111111111111111111111" << endl;

    //前提是共有继承
    //规则1：可以将一个子类的对象赋值给父类的对象
    t_person1.print();

    t_person1 = t_chinese1;

    t_person1.print();

    //t_chinese2 = (chinese)t_person2;

    cout << "2222222222222222222222222" << endl;
    //规则2：可以用一个子类的对象去初始化一个父类的引用；
    person &t_person4 = t_chinese2;

    t_chinese2.print();

    t_person4.print();

    t_person4.m_name = "Will";

    t_chinese2.print();

//    chinese &t_chinese4 = t_person1;

    cout << "33333333333333333333333333" << endl;
    //规则3：可以用一个父类的指针指向一个子类的对象；
    person *t_person5 = &t_chinese3;

    t_person5->print();

//    chinese *t_chinese4 = (chinese *)&t_person3;

//    t_chinese4->print();

    //用子类指针指向父类对象要慎用,可能会出现内存错误
//    chinese *t_chinese5 = (chinese *)new person("Mack","USA",50);

//    //cout << "food : " << t_chinese5->getFood() << endl;

//    cout << "name : " << t_chinese5->getName() << endl;

    //三条规则的用法,函数传参

    cout << "444444444444444444444" << endl;

//    getPersonInfo(t_person1);
//    getPersonInfo(t_chinese1);

    chinese t_chinese6(t_chinese1);

    t_chinese6.print();

    cout << "555555555555555555555" << endl;

    getPersonInfo(&t_person1);
    getPersonInfo(&t_chinese1);

    cout << "Hello World!" << endl;
    return 0;
}

