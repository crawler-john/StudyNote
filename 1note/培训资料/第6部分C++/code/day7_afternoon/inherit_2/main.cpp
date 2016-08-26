#include <iostream>
#include "person.h"

using namespace std;

int main()
{
    chinese t_chinese1;

    //函数的继承/覆盖
    t_chinese1.print();


    cout << "11111111111111111111" << endl;

    chinese t_chinese2("Jack","china",30,"meat","dota2",2);
    t_chinese2.print();

//    t_chinese1.person::print();
//    t_chinese1.chinese::print();



    cout << "Hello World!" << endl;
    return 0;
}

