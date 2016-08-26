#include "Common.h"


string tran_plan(Plan t_curePlan)
{
    string tmp;
    switch(t_curePlan)
    {
    case NORMAL:
        tmp = "Normal";
        break;
    case MEDICINE:
        tmp = "MEDICINE";
        break;
    case HOSPITAL:
        tmp = "HOSPITAL";
        break;
    default:
        cout << "cure plan is wrong!" << endl;
    }

    return tmp;
}
