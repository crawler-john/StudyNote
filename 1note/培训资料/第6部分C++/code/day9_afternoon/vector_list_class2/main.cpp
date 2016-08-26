#include <iostream>
#include <vector>
#include <list>
#include "student.h"

using namespace std;

int main()
{
    vector< vector<student> > t_vec1(3,vector<student>(3,student("Jack","001",30)));

    vector< vector<student> >::iterator t_iter1;

    for(t_iter1 = t_vec1.begin();t_iter1 != t_vec1.end();t_iter1++)
    {
        vector<student>::iterator tmp;

        for(tmp = t_iter1->begin();tmp != t_iter1->end();tmp++)
        {
            tmp->print();
        }

        cout << endl;
    }

    cout << "22222222222222222222222222222" << endl;

    vector< vector<student> > t_vec2;

    t_vec2.resize(3);

    for(int i = 0; i < 3; i++)
    {
        t_vec2[i].resize(3,student("Lucy","007",50));
    }

    for(t_iter1 = t_vec2.begin();t_iter1 != t_vec2.end();t_iter1++)
    {
        vector<student>::iterator tmp;

        for(tmp = t_iter1->begin();tmp != t_iter1->end();tmp++)
        {
            tmp->print();
        }

        cout << endl;
    }

    cout << "333333333333333333333333333333333" << endl;

    vector< vector<student> > t_vec3;

    for(int i = 0; i < 3; i++)
    {
        vector<student> tmp;

        for(int j = 0; j < 3; j++)
        {
            tmp.push_back(student("Lily","005",60));
        }

        t_vec3.push_back(tmp);
    }

    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end();t_iter1++)
    {
        vector<student>::iterator tmp;

        for(tmp = t_iter1->begin();tmp != t_iter1->end();tmp++)
        {
            tmp->print();
        }

        cout << endl;
    }

    cout << "444444444444444444444444444444444444" << endl;

    vector< vector<student *> > t_vec4;
    vector< vector<student *> >::iterator t_iter2;

    for(t_iter1 = t_vec3.begin(); t_iter1 != t_vec3.end(); t_iter1++)
    {
        vector<student>::iterator tmp;
        vector<student*> tmp2;

        for(tmp = t_iter1->begin(); tmp != t_iter1->end();tmp++)
        {
            tmp2.push_back(&(*tmp));
        }

        t_vec4.push_back(tmp2);
    }

    cout << "5555555555555555555555555555555555555" << endl;

    for(t_iter2 = t_vec4.begin(); t_iter2 != t_vec4.end(); t_iter2++)
    {
        vector<student*>::iterator tmp;

        for(tmp = t_iter2->begin(); tmp != t_iter2->end(); tmp++)
        {
            (*tmp)->print();
        }

        cout << endl;
    }

    cout << "66666666666666666666666666666666666666" << endl;

    vector< vector<student*> > t_vec5;

    for(int i = 0; i < 3; i++)
    {
        vector<student*> tmp;

        for(int j = 0; j < 3; j++)
        {
            student *t_student = new student("Mack","001",5);
            tmp.push_back(t_student);
        }

        t_vec5.push_back(tmp);
    }

    for(t_iter2 = t_vec5.begin(); t_iter2 != t_vec5.end(); t_iter2++)
    {
        vector<student*>::iterator tmp;

        for(tmp = t_iter2->begin(); tmp != t_iter2->end(); tmp++)
        {
            (*tmp)->print();
        }

        cout << endl;
    }

    //释放资源
    for(t_iter2 = t_vec5.begin(); t_iter2 != t_vec5.end(); t_iter2++)
    {
        vector<student*>::iterator tmp;

        for(tmp = t_iter2->begin(); tmp != t_iter2->end(); tmp++)
        {
            delete *tmp;
            *tmp = NULL;
        }

        t_iter2->clear();

    }

    t_vec5.clear();


    //vector< list<student*> > t_vec6;

    cout << "Hello World!" << endl;
    return 0;
}

