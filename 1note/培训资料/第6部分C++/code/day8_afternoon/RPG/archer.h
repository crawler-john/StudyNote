#ifndef ARCHER_H
#define ARCHER_H

#include "common.h"
#include "player.h"

//弓箭手类
class Archer : public Player
{
public:
    Archer(const string &t_name = "弓箭手1",Level t_level = LOW_Level);

    ~Archer(){}

    //攻击目标
    virtual void basisAttack();

    //魔法攻击
    virtual void magicAttack(const Skill &t_skill);
};

#endif // ARCHER_H
