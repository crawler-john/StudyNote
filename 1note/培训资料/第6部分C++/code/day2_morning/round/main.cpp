#include <iostream>
#include "round.h"

using namespace std;

int main()
{
    round t_round1;

    t_round1.setR(10.0);

    cout << "round1 r : " << t_round1.getR() << endl;
    cout << "round1 area : " << t_round1.getArea() << endl;
    cout << "round1 girth : " << t_round1.getGirth() << endl;


    cout << "Hello World!" << endl;
    return 0;
}

