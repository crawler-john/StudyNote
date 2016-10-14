#include "fun1.h"


void readAnimalInfo(const Animal &t_animal)
{
    //t_animal.m_name = "cat";


    cout << "animal name : " << t_animal.m_name << endl;
    cout << "animal age : " << t_animal.m_age << endl;
    cout << "animal weight : " << t_animal.m_weight << endl;
}

void writeAnimalInfo(Animal &t_animal)
{
//    t_animal.m_name = "dog";
//    t_animal.m_age = 1;
//    t_animal.m_weight = 20;

    cout << "请输入修改后的动物的名字 : " << endl;
    cin >> t_animal.m_name;
    cout << "请输入修改后的动物的年龄 : " << endl;
    cin >> t_animal.m_age;
    cout << "请输入修改后的动物的体重 : " << endl;
    cin >> t_animal.m_weight;
}

void Swap(int *t_p1,int *t_p2)
{
    int temp = *t_p1;
    *t_p1 = *t_p2;
    *t_p2 = temp;
}

void Swap2(int &t_x,int &t_y)
{
    int temp = t_x;
    t_x = t_y;
    t_y = temp;
}

const string& Max_string(const string &t_str1,const string &t_str2)
{
    //return strlen(t_str1.c_str()) > strlen(t_str2.c_str()) ? t_str1 : t_str2;

    return t_str1.length() > t_str2.length() ? t_str1 : t_str2;
}

