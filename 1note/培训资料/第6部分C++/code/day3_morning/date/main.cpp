#include <iostream>
#include "date.h"

using namespace std;

int main()
{
    date t_date1;
    date t_date2(2000,10,10);
    date t_date3(t_date2);

    t_date1 = t_date2;

    t_date1.print();
    t_date2.print();
    t_date3.print();

    t_date1.setDate(1999,1,1);
    t_date1.print();

    cout << "Hello World!" << endl;
    return 0;
}

