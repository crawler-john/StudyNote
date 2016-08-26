#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

class person
{
public:
    person()
    {
        m_name = "Jim";
        m_age = 20;
    }

    ~person(){}

    void setAge(int t_age){m_age = t_age;}

    int getAge(){return m_age;}

    void print()
    {
        cout << "person name : " << m_name << endl;
        cout << "person age : " << m_age << endl;
    }

private:

    string m_name;
    int m_age;
};

typedef enum errorType
{
    DEFAULT_TYPE = 1,          //默认类型
    CALLER_DISCONNECT = 2,     //主叫断开
    CALLED_DISCONNECT = 3,     //被叫断开
    TIME_OUT = 4               //超时
}errType;

//共有继承,抛子类对象,可以用父类对象捕获
class Chinese : public person{};
class Japanese : public person{};
class American : public person{};
class English : protected person{};










#endif // PERSON_H
