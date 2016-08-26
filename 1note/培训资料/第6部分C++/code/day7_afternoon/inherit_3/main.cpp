#include <iostream>
#include "biology.h"

using namespace std;

int main()
{
    biology t_biology1;

    t_biology1.print();

//    t_biology1.animal::print();
//    t_biology1.plant::print();

    cout << "biology age : " << t_biology1.getAge() << endl;

    cout << "Hello World!" << endl;
    return 0;
}

