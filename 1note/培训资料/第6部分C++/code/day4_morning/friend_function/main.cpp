#include <iostream>
#include "student.h"

using namespace std;

int main()
{
    student t_student1;

    getStuScore(t_student1);

    teacher t_teacher1;

    t_teacher1.setStuScore(t_student1);

    getStuScore(t_student1);

    Count t_count1;

    cout << "all score : " << t_count1.getStuAllScore(t_student1) << endl;
    cout << "aver score : " << t_count1.getStuAverScore(t_student1) << endl;

    cout << "count name : " << t_student1.getCountName(t_count1) << endl;

    cout << "11111111111111111111" << endl;

    cout << t_student1 << endl;

    cin >> t_student1;

    cout << t_student1 << endl;

    cout << "Hello World!" << endl;
    return 0;
}

