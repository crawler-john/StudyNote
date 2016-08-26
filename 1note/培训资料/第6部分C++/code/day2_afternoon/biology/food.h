#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <string>

using namespace std;


class food
{
public:

    food()
    {
        cout << "food()" << endl;
        m_name = "meat";
        m_validTime = 1;
    }

    food(const string &t_name,int t_validTime)
        :m_name(t_name),m_validTime(t_validTime)
    {
        cout << "food(...)" << endl;
    }

    ~food()
    {
        cout << "~food()" << endl;
    }

    void print()
    {
        cout << "food name : " << m_name << endl;
        cout << "food valid time : " << m_validTime << endl;
    }

private:

    string m_name;
    int m_validTime;
};

class game
{
public:

    game()
    {
        cout << "game()" << endl;
        m_name = "LOL";
        m_level = 1;
    }

    game(const string &t_name,int t_level)
        :m_name(t_name),m_level(t_level)
    {
        cout << "game(...)" << endl;
    }

    ~game()
    {
        cout << "~game()" << endl;
    }

    void print()
    {
        cout << "game name : " << m_name << endl;
        cout << "game level : " << m_level << endl;
    }

private:

    string m_name;
    int m_level;
};








#endif // FOOD_H
