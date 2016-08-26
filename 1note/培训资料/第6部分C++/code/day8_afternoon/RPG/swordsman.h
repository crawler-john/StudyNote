#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "player.h"

//剑士类
class Swordsman : public Player
{
public:
    Swordsman(const string &t_name = "剑士1",Level t_level = LOW_Level);

    //攻击目标
    virtual void basisAttack();

    //魔法攻击
    virtual void magicAttack(const Skill &t_skill);

protected:

private:

};

#endif // SWORDSMAN_H
