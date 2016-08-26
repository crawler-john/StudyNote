#include "player.h"

//合成装备,给角色加属性点
void Equip::addPoint(Player &t_player)
{
    //获取角色的装备名
    string t_equipName = t_player.getEquip().m_name;
    EquipType t_equipType = t_player.getEquip().m_type;

    //如果是基础装备,则不加点
    if(t_equipType == BasicEquip)
    {
        cout << "该装备为基础装备,不加点!" << endl;
        return;
    }

    //玄武斧:攻击力+15,血量+50,魔免
    if(t_equipName == "玄武斧")
    {
        t_player.m_AP += 15;
        t_player.m_HP += 50;
        t_player.m_magic = Invalid_true;
    }
    //倚天剑:攻击力+30，每攻击一次将攻击自己的攻击的15%转加到自己的生命值上
    else if(t_equipName == "倚天剑")
    {
        t_player.m_AP += 30;
    }
    //源式铠:防御力+10，有15%的几率躲闪对手的攻击60点
    else if(t_equipName == "源式铠")
    {
        t_player.m_DP += 10;
    }
}

//施展技能,给角色加属性点
void Skill::addPoint(Player &t_player)
{
    //获取角色技能的名字和类型
    string t_skillName = t_player.getSkill().m_name;

    //重剑斩:攻击力增加60点,持续5秒
    if(t_skillName == "重剑斩")
    {
        t_player.m_AP += 60;
    }
    //流星箭:攻击力增加40点,攻击速度加倍,持续3秒
    else if(t_skillName == "流星箭")
    {
        t_player.m_AP += 40;
        t_player.m_ackSpeed = Twice_ACK;
    }
    //吸血术:攻击力增加50点,将对敌方攻击的伤害值的20%转化为自己的血量
    else if(t_skillName == "吸血术")
    {
        t_player.m_AP += 50;

    }
    //天神下凡:攻击力+30,防御+10,魔免(不受魔法攻击)
    else if(t_skillName == "天神下凡")
    {
        t_player.m_AP += 30;
        t_player.m_DP += 10;
        t_player.m_magic = Invalid_true;
    }
    //天下无双:攻击速度+100%，移动速度+100%
    else if(t_skillName == "天下无双")
    {
        t_player.m_ackSpeed = Twice_ACK;
        t_player.m_moveSpeed = Twice_MV;
    }

}

//初始化数据
Player::Player(const string &t_name,Level t_level,Type t_type,const roleData &t_data):m_enemy(0)
{
    m_name = t_name;
    m_level = t_level;            //默认为初级
    m_type = t_type;              //默认类型

    m_HP = t_data.m_HP;                   //默认为100点
    m_MP = t_data.m_MP;                    //默认为50点
    m_AP = t_data.m_AP;                    //默认为50点
    m_DP = t_data.m_DP;                    //默认为30点
    m_EXP = 0;                    //默认为0
    //m_equip =
    m_ackSpeed = Normal_ACK;      //默认为正常攻速
    m_moveSpeed = Normal_MV;      //默认为正常移动速度
    m_magic = Invalid_false;      //默认为非魔免
}

//有参的构造函数
//Player::Player(const roleInfo &t_roleInfo)
//{
//    m_name = t_roleInfo.m_name;
//    m_level = t_roleInfo.m_level;
//    m_type = t_roleInfo.m_type;
//    m_HP = t_roleInfo.m_HP;
//    m_MP = t_roleInfo.m_MP;
//    m_AP = t_roleInfo.m_AP;
//    m_DP = t_roleInfo.m_DP;
//    m_EXP = t_roleInfo.m_EXP;
//    m_equip = t_roleInfo.m_equip;
//    m_ackSpeed = t_roleInfo.m_ackSpeed;
//    m_moveSpeed = t_roleInfo.m_moveSpeed;
//    m_magic = t_roleInfo.m_magic;
//}

//锁定目标
bool Player::lockTarget(Player *t_enemy)
{
    //自己血量为零
    if(m_HP <= 0)
    {
        cout << "玩家:" << m_name << "血量为零,锁定攻击目标失败!" << endl;
        return false;
    }

    //如果目标不存在
    if(t_enemy == NULL)
    {
        cout << "被攻击的目标不存在!" << endl;
        return false;
    }

    //如果攻击的目标是自己
    if(t_enemy == this)
    {
        cout << "不能自己攻击自己!" << endl;
        return false;
    }

    //如果攻击的目标血量为零
    if(t_enemy->getHP() <= 0)
    {
        cout << "被攻击目标:" << t_enemy->m_name  << " 已经死亡!" << endl;
        return false;
    }

    m_enemy = t_enemy;

    return true;
}

//打印信息
void Player::print()
{
    cout << "--------------------------------------------------------------------------------";
    cout << "角色名:" << m_name << "  等级:" << g_levelMap.find(m_level)->second << "  类型:" << g_roleMap.find(m_type)->second << "  经验值:" << m_EXP << "  血量:" << m_HP << "  魔法值:" << m_MP << "  攻击力:" << m_AP << endl;
    cout << "防御力:" << m_DP << "  装备:" << m_equip.m_name << "  装备类型:" << g_equipMap.find(m_equip.m_type)->second << "  攻击速度:" << g_ackSpeedMap.find(m_ackSpeed)->second << "  移动速度:" << g_moveSpeedMap.find(m_moveSpeed)->second
         << "  技能:" << m_skill.m_name << "  技能类型:" << g_skillMap.find(m_skill.m_type)->second << "  " << g_magicInvalidMap.find(m_magic)->second << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
}





