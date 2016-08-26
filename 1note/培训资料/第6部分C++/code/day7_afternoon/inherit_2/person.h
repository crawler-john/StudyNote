#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

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

//基类(父类)
class person
{
public:

    person()
    {
        cout << "person()" << endl;
        m_name = "rose";
        m_nation = "USA";
        m_age = 20;
    }

    person(const string &t_name,const string &t_nation,int t_age)
        :m_name(t_name),m_nation(t_nation),m_age(t_age)
    {
        cout << "person(...)" << endl;
    }

    ~person(){cout << "~person()" << endl;}

    void print()
    {
        cout << "person name : " << m_name << endl;
        cout << "person nation : " << m_nation << endl;
        cout << "person age : " << m_age << endl;
    }

    string m_name;
    string getName()
    {
        return m_name;
    }

protected:

    string m_nation;
    string getNation()
    {
        return m_nation;
    }

    int getAge2()
    {
        return m_age;
    }

private:

    int m_age;
    int getAge()
    {
        return m_age;
    }
};

//一级继承 共有继承
class chinese : public person
{
public:

    //先调用父类的构造函数构造父类部分的数据,再调用子类构造函数构造子类部分的数据
    chinese()
    {
        cout << "chinese()" << endl;
        m_food = "fish";
    }

    chinese(const string &t_name,const string &t_nation,int t_age,const string &t_food,const string &t_gameName,int t_level);

    //析构函数调用的顺序与构造函数调用的顺序相反
    ~chinese(){cout << "~chinese()" << endl;}

    void print()
    {
        cout << "chinese name : " << m_name << endl;
        cout << "chinese nation : " << m_nation << endl;
        cout << "chinese age : " << getAge2() << endl;

        //显示调用父类的print()函数
        //person::print();
        cout << "chinese food : " << m_food << endl;

        m_game.print();
    }

protected:

    string m_food;
    string getFood()
    {
        return m_food;
    }

private:


    //先调用父类的构造函数构造父类部分的数据,在调用组合类game的构造函数,最后调用子类构造函数构造子类部分的数据
    game m_game;

};


#endif // PERSON_H
