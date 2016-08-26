#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

//类模板
template<typename T1,typename T2>
class student
{
public:

    student()
    {

    }

    student(const T1 &t_name,const T1 &t_ID,T2 t_age,T2 t_weight)
        :m_name(t_name),m_ID(t_ID),m_age(t_age),m_weight(t_weight)
    {

    }

    ~student(){}

    T1 getName()
    {
        return m_name;
    }

    T1 getID()
    {
        return m_ID;
    }

    T2 getAge();

    T2 getWeight();

    void print();

    class middleStudent
    {
    public:

        middleStudent(){}
        middleStudent(T1 t_grade,T2 t_class):m_grade(t_grade),m_class(t_class){}

        T1 getGrade()
        {
            return m_grade;
        }

        T2 getClass();

        void print();

    private:
        T1 m_grade;
        T2 m_class;
    };

private:

    T1 m_name;
    T1 m_ID;
    T2 m_age;
    T2 m_weight;
};

template<typename T1,typename T2>
T2 student<T1,T2>::getAge()
{
    return m_age;
}

template<typename T1,typename T2>
T2 student<T1,T2>::getWeight()
{
    return m_weight;
}

template<typename T1,typename T2>
void student<T1,T2>::print()
{
    cout << "student name : " << m_name << endl;
    cout << "student ID : " << m_ID << endl;
    cout << "student age : " << m_age << endl;
    cout << "student weight : " << m_weight << endl;
}

template<typename T1,typename T2>
T2 student<T1,T2>::middleStudent::getClass()
{
    return m_class;
}

template<typename T1,typename T2>
void student<T1,T2>::middleStudent::print()
{
    cout << "middle student grade : " << m_grade << endl;
    cout << "middle student class : " << m_class << endl;
}

#endif // STUDENT_H
