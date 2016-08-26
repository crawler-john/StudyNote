#include <iostream>
#include "biology.h"

using namespace std;

int main()
{
    biology t_biology1;

    t_biology1.setName("tiger");

    cout << "biology name : " << t_biology1.getName() << endl;

    t_biology1.move();

    t_biology1.eat();


    cout << "Hello World!" << endl;
    return 0;
}

