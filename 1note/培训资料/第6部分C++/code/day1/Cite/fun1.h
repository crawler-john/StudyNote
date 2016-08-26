#ifndef FUN1_H
#define FUN1_H

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

struct Animal
{
    string m_name;
    int m_age;
    int m_weight;
};


void readAnimalInfo(const Animal &t_animal);

void writeAnimalInfo(Animal &t_animal);

void Swap(int *t_p1,int *t_p2);

//引用作为函数参数的好处:减少拷贝,提高效率
void Swap2(int &t_x,int &t_y);


const string& Max_string(const string &t_str1, const string &t_str2);


#endif // FUN1_H
