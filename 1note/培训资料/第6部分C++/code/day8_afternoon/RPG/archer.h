#ifndef ARCHER_H
#define ARCHER_H

#include "common.h"
#include "player.h"

//��������
class Archer : public Player
{
public:
    Archer(const string &t_name = "������1",Level t_level = LOW_Level);

    ~Archer(){}

    //����Ŀ��
    virtual void basisAttack();

    //ħ������
    virtual void magicAttack(const Skill &t_skill);
};

#endif // ARCHER_H
