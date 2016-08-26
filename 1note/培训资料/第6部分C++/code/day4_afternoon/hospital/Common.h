#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <iostream>

using namespace std;

typedef enum curePlan
{
    NORMAL = 1,   //正常
    MEDICINE = 2, //吃药
    HOSPITAL = 3  //住院
}Plan;

string tran_plan(Plan t_curePlan);

#endif // COMMON_H



