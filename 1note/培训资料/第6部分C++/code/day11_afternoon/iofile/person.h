#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class person
{
public:

    person()
    {
        strcpy(m_name,"Jim");
        m_age = 20;
    }

    person(const string &t_name,int t_age)
    {
        strcpy(m_name,t_name.c_str());
        m_age = t_age;
    }

    ~person(){}

    void print()
    {
        cout << "person name : " << m_name << " age : " << m_age << endl;
    }

private:

    char m_name[20];
    int m_age;
};

#endif // PERSON_H
