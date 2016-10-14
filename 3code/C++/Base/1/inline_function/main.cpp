#include <iostream>
#include "fun1.h"

using namespace std;

//int Max(int t_x,int t_y);



int main()
{
    int t_a = 20;
    int t_b = 30;

    cout << "max : " << Max(t_a,t_b) << endl;

    Swap(t_a,t_b,true);

    cout << "t_a : " << t_a << endl;
    cout << "t_b : " << t_b << endl;

    cout << "sum : " << Add(1,2,3) << endl;

    cout << "Hello World!" << endl;
    return 0;
}

//inline int Max(int t_x,int t_y)
//{
//    return t_x > t_y ? t_x : t_y;
//}


