#ifndef FURNITURE_H
#define FURNITURE_H

#include <iostream>
#include <string>

using namespace std;

//家具类
class Furniture
{
public:
    Furniture()
    {
        cout << "Furniture()" << endl;
        m_name = "Furniture";
        m_weight = 50;
    }

    ~Furniture()
    {
        cout << "~Furniture()" << endl;
    }

    //设置家具的重量
    void setWeight(int t_weight)
    {
        m_weight = t_weight;
    }

    //获取家具的重量
    int getWeight()
    {
        return m_weight;
    }

    string getName()
    {
        return m_name;
    }

protected:

    string m_name;   //家具的名字
    int m_weight;    //家具的重量
};

#endif // FURNITURE_H
