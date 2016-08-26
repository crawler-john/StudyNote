#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>

using namespace std;

class animal
{
public:

    animal()
    {
        cout << "animal()" << endl;
        m_name = "cat";
        m_age = 1;
        m_weight = 20;
    }

    ~animal()
    {
        cout << "~animal()" << endl;
    }

    void print()
    {
        cout << "animal name : " << m_name << endl;
        cout << "animal age : " << m_age << endl;
        cout << "animal weight : " << m_weight << endl;
        m_bird.print();
    }

    //类的嵌套
    class bird
    {
    public:

        bird()
        {
            cout << "bird()" << endl;
            m_name = "bird person";
            m_color = "black";
        }

        ~bird()
        {
            cout << "~bird()" << endl;
        }

        void print();

    private:

        string m_name;
        string m_color;
    };

private:

    string m_name;
    int m_age;
    int m_weight;

    bird m_bird;

};

#endif // ANIMAL_H
