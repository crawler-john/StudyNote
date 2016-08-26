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

//    //���1�������2, 3��

    for(int i = 0; i < 3; i++)
    {
        if(t_player1->lockTarget(t_player2))
        {
            t_player1->basisAttack();
        }

        if(t_player2->lockTarget(t_player1))
        {
            t_player2->magicAttack(Skill("�ؽ�ն",SpecialSkill,3));
        }
    }

//    t_player1->print();
//    t_player2->print();

    //��Һϳ�װ��
//    t_player1->setEquip(Equip("���丫",SpecialEquip));
//    Equip::addPoint(*t_player1);

//    cout << "��� : " << t_player1->m_name << " �ϳ�װ��(���丫)��,���ܵ�ӳ���ϢΪ : " << endl;

//    t_player1->print();

//    //���ʩչ����
//    t_player2->setSkill(Skill("������˫",SpecialSkill,5));
//    Skill::addPoint(*t_player2);

//    cout << "��� : " << t_player2->m_name << " ʩչ����(������˫)��,���ܵ�ӳ���ϢΪ : " << endl;
//    cout << "����(������˫)����ʱ��Ϊ : " << t_player2->getSkill().m_continuedTime  << "��! " << endl;

//    t_player2->print();

//    Player *t_player3 = new Archer("����",MIDDLE_Level);
//    Player *t_player4 = new Mage("˾��ܲ",HIGH_Level);

//    t_player1->print();
//    t_player3->print();
//    t_player4->print();

    cout << "Hello World!" << endl;
    return 0;
}

