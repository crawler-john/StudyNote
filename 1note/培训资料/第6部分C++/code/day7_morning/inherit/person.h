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

protected:

    string m_nation;
    string getNation()
    {
        return m_nation;
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

    ~chinese(){cout << "~chinese()" << endl;}

    //子类的成员函数可以直接访问父类的public,protected区的成员(成员变量和成员函数),不能访问父类私有区的成员
    void test_fun1()
    {
        m_name;
        getName();

        m_nation;
        getNation();

//        m_age;
//        getAge();
    }

protected:

    string m_food;
    string getFood()
    {
        return m_food;
    }

private:

};

//一级继承 保护继承
class Japanese : protected person
{
public:

    Japanese()
    {
        cout << "Japanese()" << endl;
        m_car = "Toyota";

    }

    ~Japanese()
    {
        cout << "~Japanese()" << endl;
    }

    //子类的成员函数可以直接访问父类的public,protected区的成员(成员变量和成员函数),不能访问父类私有区的成员
    void test_fun1()
    {
        m_name;
        getName();

        m_nation;
        getNation();

//        m_age;
//        getAge();
    }

protected:

    string m_car;
    string getCar()
    {
        return m_car;
    }

private:
};

//一级继承 私有继承
class American : private person
{
public:

    American()
    {
        cout << "American()" << endl;
        m_soft = "Apple";
    }

    ~American()
    {
        cout << "~Amercian()" << endl;
    }

    //子类的成员函数可以直接访问父类的public,protected区的成员(成员变量和成员函数),不能访问父类私有区的成员
    void test_fun1()
    {
        m_name;
        getName();

        m_nation;
        getNation();

//        m_age;
//        getAge();
    }

protected:

    string m_soft;
    string getSoft()
    {
        return m_soft;
    }

private:

};

//二级继承,一级共有继承,二级共有继承
class chineseMan : public chinese
{
public:
    chineseMan()
    {
        cout << "chineseMan()" << endl;
    }

    ~chineseMan()
    {
        cout << "~chineseMan()" << endl;
    }

    //子类的子类的成员函数可以直接访问基类的public,protected区的成员(成员变量和成员函数),不能访问父类私有区的成员
    void test_fun1()
    {
        m_name;
        getName();

        m_nation;
        getNation();

//        m_age;
//        getAge();
    }


protected:

private:

};

//二级继承,一级保护继承,二级共有继承
class JapaneseMan : public Japanese
{
public:

    JapaneseMan()
    {
        cout << "JapaneseMan()" << endl;
    }

    ~JapaneseMan()
    {
        cout << "~JapaneseMan()" << endl;
    }

    //子类的子类的成员函数可以直接访问基类的public,protected区的成员(成员变量和成员函数),不能访问父类私有区的成员
    void test_fun1()
    {
        m_name;
        getName();

        m_nation;
        getNation();

//        m_age;
//        getAge();
    }


protected:
private:
};

//二级继承,一级私有继承,二级共有继承
class AmericanMan : public American
{
public:

    AmericanMan()
    {
        cout << "AmericanMan()" << endl;
    }

    ~AmericanMan()
    {
        cout << "~AmericanMan()" << endl;
    }

    //子类的子类的成员函数不能访问基类的所有区间的成员
    void test_fun1()
    {
//        m_name;
//        getName();

//        m_nation;
//        getNation();

//        m_age;
//        getAge();
    }

protected:


private:


};







#endif // PERSON_H
