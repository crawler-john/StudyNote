#include "archer.h"


//构造函数
//弓箭手的血量为80,魔法量为120,攻击力为25,防御力为3
Archer::Archer(const string &t_name, Level t_level)
    :Player(t_name,t_level,ArcHer,roleData(80,120,25,3))
{
    //装备为弓箭,基础装备
    m_equip = Equip(g_equipName[2],BasicEquip);
    m_skill = Skill(g_skillName[2],SpecialSkill);
}

//弓箭手基本攻击
void Archer::basisAttack()
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

//弓箭手魔法攻击
void Archer::magicAttack(const Skill &t_skill)
{
    //如果魔法值不够,则不能发起魔法攻击(发起一次魔法攻击需要40点魔法值)
    if(m_MP < 40)
    {
        cout << "没有足够的魔法值发起该次魔法攻击!" << endl;
        return;
    }

    //如果对方是魔免的,则无法对它进行魔法攻击
    if(m_enemy->getMagic() == Invalid_true)
    {
        cout << "对方现在处于魔免状态,无法对它进行魔法攻击" << endl;
    }

    //弓箭手可以施展流星箭,吸血术等技能
    //流星箭 : 消耗对方45点生命值,消耗自己40点魔法值,持续时间2秒
    if(t_skill.m_name == "流星箭")
    {
        m_MP -= 40;
        m_enemy->setHP(m_enemy->getHP() - 45);
    }
    //吸血术 : 攻击力增加30,将对方消耗血量的15%转变为自己的血量,持续时间3秒
    else if(t_skill.m_name == "吸血术")
    {
        m_AP += 30;
        m_HP += (m_AP - m_enemy->getDP())*0.15;
    }

    //打印攻击信息
    cout << m_name << " 类型:" << g_roleMap.find(m_type)->second << "用"  << g_skillMap.find(m_skill.m_type)->second << ":" << m_skill.m_name << "攻击"
         << " " << m_enemy->m_name << " 类型为:" << g_roleMap.find(m_enemy->m_type)->second << endl;
}




