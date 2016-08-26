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

    person(const person &t_person)
        :m_name(t_person.m_name),m_nation(t_person.m_nation),m_age(t_person.m_age)
    {
        cout << "copy person(...)" << endl;
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

    chinese(const chinese &t_chinese)
        :person(t_chinese),m_food(t_chinese.m_food)
    {
        cout << "copy chinese(...)" << endl;

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

protected:

    string m_food;


private:


};


#endif // PERSON_H
