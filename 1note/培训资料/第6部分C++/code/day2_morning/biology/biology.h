#ifndef BIOLOGY_H
#define BIOLOGY_H

#include <iostream>
#include <string>

using namespace std;

class biology
{
public:

    void move();    //生物在移动

    void eat();     //生物在吃饭

    void setName(const string &t_name);  //设置生物的名字

    string getName();  //获取生物的名字

private:

    string m_name;

};

#endif // BIOLOGY_H
