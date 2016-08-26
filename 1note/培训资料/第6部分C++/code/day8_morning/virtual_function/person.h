#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

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

    //虚函数
    virtual void play()
    {
        cout << "person play!" << endl;
    }

    virtual void eat()
    {
        cout << "person eat!" << endl;
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

    chinese()
    {
        cout << "chinese()" << endl;
        m_food = "fish";
    }

    chinese(const string &t_name,const string &t_nation,int t_age,const string &t_food)
        :person(t_name,t_nation,t_age),m_food(t_food)
    {
        cout << "chinese(...)" << endl;

    }

    ~chinese(){cout << "~chinese()" << endl;}

    void print()
    {
        cout << "chinese name : " << m_name << endl;
        cout << "chinese nation : " << m_nation << endl;
        cout << "chinese age : " << getAge2() << endl;
        cout << "chinese food : " << m_food << endl;
    }

    string getFood()
    {
        return m_food;
    }


    virtual void play()
    {
        cout << "chinese play!" << endl;
    }

    //override条件: 1.函数的返回值一样 2.函数名一样 3.函数的形参列表一样
    void eat()
    {
        cout << "chinese eat!" << endl;
    }

protected:

    string m_food;




private:


};

class chineseMan : public chinese
{
public:

    chineseMan()
    {
        cout << "chineseMan()" << endl;
        m_mailBox = "zhangsan@qq.com";
    }

    ~chineseMan()
    {
        cout << "~chineseMan()" << endl;
    }

    virtual void play()
    {
        cout << "chineseMan play!" << endl;
    }

    void eat()
    {
        cout << "chineseMan eat!" << endl;
    }

protected:

    string m_mailBox;

private:


};












#endif // PERSON_H
