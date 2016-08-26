#include "animal.h"

int animal::m_number = 0;
int animal::bird::m_number = 0;



void animal::bird::print()
{
    cout << "bird name : " << m_name << endl;
    cout << "bird color : " << m_color << endl;
}
