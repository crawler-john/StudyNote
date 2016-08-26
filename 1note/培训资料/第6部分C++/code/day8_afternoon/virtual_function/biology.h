#ifndef BIOLOGY_H
#define BIOLOGY_H

#include <iostream>
#include <string>

using namespace std;

//动物类
class animal
{
public:

    animal()
    {
        cout << "animal()" << endl;
        m_animalName = "tiger";
        m_weight = 100;
    }

    ~animal()
    {
        cout << "~animal()" << endl;
    }

    void print()
    {
        cout << "animal name : " << m_animalName << endl;
        cout << "animal weight : " << m_weight << endl;
    }

    virtual void sleep()
    {
        cout << "animal sleep!" << endl;
    }

protected:

    string m_animalName;
    int m_weight;

private:
};

//植物类
class plant
{
public:

    plant()
    {
        cout << "plant()" << endl;
        m_plantName = "flower";
        m_height = 80;
    }

    ~plant()
    {
        cout << "~plant()" << endl;
    }

    void print()
    {
        cout << "plant name : " << m_plantName << endl;
        cout << "plant height : " << m_height << endl;     
    }

    virtual void grow()
    {
        cout << "plant grow!" << endl;
    }

protected:

    string m_plantName;
    int m_height;

private:
};

//多重继承,子类的虚函数表存放在第一个继承父类的部分
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

    virtual void play()
    {
        cout << "biology play!" << endl;
    }

protected:

    string m_color;

private:


};

#endif // BIOLOGY_H
