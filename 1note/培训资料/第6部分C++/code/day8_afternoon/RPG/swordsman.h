#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "player.h"

//��ʿ��
class Swordsman : public Player
{
public:
    Swordsman(const string &t_name = "��ʿ1",Level t_level = LOW_Level);

    //����Ŀ��
    virtual void basisAttack();

    //ħ������
    virtual void magicAttack(const Skill &t_skill);

protected:

private:

};

#endif // SWORDSMAN_H
