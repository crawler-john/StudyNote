#ifndef MAGE_H
#define MAGE_H

#include "common.h"
#include "player.h"

//��ʦ��
class Mage : public Player
{
public:
    Mage(const string &t_name = "��ʦ1",Level t_level = LOW_Level);

    ~Mage(){}

    //����Ŀ��
    virtual void basisAttack();

    //ħ������
    virtual void magicAttack(const Skill &t_skill);
};

#endif // MAGE_H
