#include <iostream>
#include "common.h"
#include "player.h"
#include "swordsman.h"
#include "archer.h"
#include "mage.h"

using namespace std;

int main()
{
    Game::init();

    Player *t_player1 = new Swordsman("Mick");

    Player *t_player2 = new Swordsman("Rose");

    t_player1->print();
    t_player2->print();

//    //玩家1攻击玩家2, 3次

    for(int i = 0; i < 3; i++)
    {
        if(t_player1->lockTarget(t_player2))
        {
            t_player1->basisAttack();
        }

        if(t_player2->lockTarget(t_player1))
        {
            t_player2->magicAttack(Skill("重剑斩",SpecialSkill,3));
        }
    }

//    t_player1->print();
//    t_player2->print();

    //玩家合成装备
//    t_player1->setEquip(Equip("玄武斧",SpecialEquip));
//    Equip::addPoint(*t_player1);

//    cout << "玩家 : " << t_player1->m_name << " 合成装备(玄武斧)后,技能点加成信息为 : " << endl;

//    t_player1->print();

//    //玩家施展技能
//    t_player2->setSkill(Skill("天下无双",SpecialSkill,5));
//    Skill::addPoint(*t_player2);

//    cout << "玩家 : " << t_player2->m_name << " 施展技能(天下无双)后,技能点加成信息为 : " << endl;
//    cout << "技能(天下无双)持续时间为 : " << t_player2->getSkill().m_continuedTime  << "秒! " << endl;

//    t_player2->print();

//    Player *t_player3 = new Archer("黄忠",MIDDLE_Level);
//    Player *t_player4 = new Mage("司马懿",HIGH_Level);

//    t_player1->print();
//    t_player3->print();
//    t_player4->print();

    cout << "Hello World!" << endl;
    return 0;
}

