#include "person.h"

chinese::chinese(const string &t_name, const string &t_nation, int t_age, const string &t_food, const string &t_gameName, int t_level)
    :person(t_name,t_nation,t_age),m_game(t_gameName,t_level),m_food(t_food)
{
    cout << "chinese(...)" << endl;

}



