#ifndef BIOLOGY_H
#define BIOLOGY_H

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

//虚基类:被虚拟继承的基类
class Base
{
public:

    Base()
    {
        cout << "Base()" << endl;
        m_age = 8;
    }

    ~Base()
    {
        cout << "~Base()" << endl;
    }

    int getAge()
    {
        return m_age;
    }

protected:

    int m_age;
private:

};

//动物类
class animal : virtual public Base
{
public:

    animal()
    {
        cout << "animal()" << endl;
        m_animalName = "tiger";
        m_weight = 100;
        //m_age = 5;
    }

    ~animal()
    {
        cout << "~animal()" << endl;
    }

    void print()
    {
        cout << "animal name : " << m_animalName << endl;
        cout << "animal weight : " << m_weight << endl;
        cout << "animal age : " << m_age << endl;
    }


protected:

    string m_animalName;
    int m_weight;

private:
};

//植物类
class plant : virtual public Base
{
public:

    plant()
    {
        cout << "plant()" << endl;
        m_plantName = "flower";
        m_height = 80;
        //m_age = 10;
    }

    ~plant()
    {
        cout << "~plant()" << endl;
    }

    void print()
    {
        cout << "plant name : " << m_plantName << endl;
        cout << "plant height : " << m_height << endl;
        cout << "plant age : " << m_age << endl;
    }

protected:

    string m_plantName;
    int m_height;

private:
};

//生物类(多重继承动物类和植物类)
//父类构造函数调用的顺序以继承顺序为准
class biology : public animal, public plant
{
public:

    biology()
    {
        cout << "biology()" << endl;
        m_color = "white";
    }

    ~biology()
    {
        cout << "~biology()" << endl;
    }

    void print()
    {
        animal::print();
        plant::print();

        cout << "biology color : " << m_color << endl;
    }

protected:

    string m_color;

private:

    //game m_game;

};

#endif // BIOLOGY_H
