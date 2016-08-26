#ifndef MAGE_H
#define MAGE_H

#include "common.h"
#include "player.h"

//法师类
class Mage : public Player
{
public:
    Mage(const string &t_name = "法师1",Level t_level = LOW_Level);

    ~Mage(){}

    //攻击目标
    virtual void basisAttack();

    //魔法攻击
    virtual void magicAttack(const Skill &t_skill);
};

#endif // MAGE_H
