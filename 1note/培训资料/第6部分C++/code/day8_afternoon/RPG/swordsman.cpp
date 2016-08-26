#include "swordsman.h"

//构造函数
//剑士的血量为100,魔法量为100,攻击力为30,防御力为5
Swordsman::Swordsman(const string &t_name,Level t_level)
    :Player(t_name,t_level,Sword_Man,roleData(100,100,30,5))
{
    //装备为剑,基础装备
    m_equip = Equip(g_equipName[1],BasicEquip);
    m_skill = Skill(g_skillName[1],SpecialSkill);

}

void Swordsman::basisAttack()
{
    //如果被攻击的目标血量为0
    if(m_enemy->getHP() <= 0)
    {
        cout << "目标:" << m_enemy->m_name << " 血量为零,已经死亡!" << endl;
        return;
    }

    //对方消耗血量
    int t_consumeHP = 0;

    //进行一次物理攻击
    if(m_ackSpeed == Normal_ACK)   //正常攻速
    {
        //对方消耗血量
        t_consumeHP = m_AP - m_enemy->getDP();
    }
    else if(m_ackSpeed == Twice_ACK)  //二倍攻速
    {
        //对方消耗血量
        t_consumeHP = 2*(m_AP - m_enemy->getDP());
    }

    //对方剩余血量为
    m_enemy->setHP(m_enemy->getHP() - t_consumeHP);

    //打印攻击信息
    cout << m_name << " 类型:" << (g_roleMap.find(m_type)->second) + ", " << "用" << m_equip.m_name << "攻击"
         << " " << m_enemy->m_name << " 类型为:" << g_roleMap.find(m_enemy->m_type)->second << endl;


}

//魔法攻击
void Swordsman::magicAttack(const Skill &t_skill)
{    
    //如果魔法值不够,则不能发起魔法攻击(发起一次魔法攻击需要50点魔法值)
    if(m_MP < 50)
    {
        cout << "没有足够的魔法值发起该次魔法攻击!" << endl;
        return;
    }

    //如果对方是魔免的,则无法对它进行魔法攻击
    if(m_enemy->getMagic() == Invalid_true)
    {
        cout << "对方现在处于魔免状态,无法对它进行魔法攻击" << endl;
    }

    //剑士可以施展重剑斩,天神下凡等技能
    //重剑斩 : 消耗对方60点生命值,消耗自己50点魔法值,持续时间1秒
    if(t_skill.m_name == "重剑斩")
    {
        m_MP -= 50;
        m_enemy->setHP(m_enemy->getHP() - 60);
    }
    //天神下凡 : 攻击力+30,防御+10,魔免(不受魔法攻击),持续时间5秒
    else if(t_skill.m_name == "天神下凡")
    {
        m_AP += 30;
        m_DP += 10;
        m_magic = Invalid_true;
    }

    //打印攻击信息
    cout << m_name << " 类型:" << g_roleMap.find(m_type)->second << "用"  << g_skillMap.find(m_skill.m_type)->second << ":" << m_skill.m_name << "攻击"
         << " " << m_enemy->m_name << " 类型为:" << g_roleMap.find(m_enemy->m_type)->second << endl;

}




