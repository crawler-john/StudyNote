#include "fun1.h"

void Swap(int *t_p1,int *t_p2)
{
    int temp = *t_p1;
    *t_p1 = *t_p2;
    *t_p2 = temp;
}

void Swap(int &t_x,int &t_y)
{
    int temp = t_x;
    t_x = t_y;
    t_y = temp;
}

void Swap(int &t_x,int &t_y,bool t_b)
{
    if(t_b)
    {
        int temp = t_x;
        t_x = t_y;
        t_y = temp;
    }
}

//int Swap(int &t_x,int &t_y)
//{
//    int temp = t_x;
//    t_x = t_y;
//    t_y = temp;

//    return 0;
//}

int Add(int t_a,int t_b,int t_c,int t_d)
{
    return t_a  + t_b + t_c + t_d;
}
