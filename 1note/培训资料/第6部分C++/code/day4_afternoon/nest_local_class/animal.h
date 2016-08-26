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

        m_number++;
    }

    ~animal()
    {
        cout << "~animal()" << endl;
        m_number--;
    }

    void print()
    {
        cout << "animal name : " << m_name << endl;
        cout << "animal age : " << m_age << endl;
        cout << "animal weight : " << m_weight << endl;

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

            m_number++;
        }

        ~bird()
        {
            cout << "~bird()" << endl;
            m_number--;
        }

        void print();

        static int getNumber()
        {
            return m_number;
        }

    private:

        string m_name;
        string m_color;

        static int m_number;
    };

    static int getNumber()
    {
        return m_number;
    }

private:

    string m_name;
    int m_age;
    int m_weight;

    static int m_number;

    bird m_bird;

};

#endif // ANIMAL_H
