#ifndef FUN1_H
#define FUN1_H

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int Max(int t_x,int t_y);

inline int Max(int t_x,int t_y)
{
    return t_x > t_y ? t_x : t_y;
}

//函数重载 1.函数名一样 2.函数的形参列表不一样 3.与函数的返回值无关
void Swap(int *t_p1,int *t_p2);

//Swap_int*_int*

void Swap(int &t_x,int &t_y);

//Swap_int&_int&

//int Swap(int &t_x,int &t_y);

//默认函数与函数重载一起使用时需要注意下
void Swap(int &t_x,int &t_y,bool t_b);

//增加默认参数的顺序：必须从右往左增加
//匹配实参的顺序是从左往右的
int Add(int t_a=10,int t_b=20,int t_c=30,int t_d=40);

#endif // FUN1_H

