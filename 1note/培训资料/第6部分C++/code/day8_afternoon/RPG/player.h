#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "common.h"

using namespace std;

class Player;

//装备类
class Equip
{
public:

    Equip()
    {
        m_name = g_equipName[0];
        m_type = BasicEquip;     //默认为基本装备
    }

    Equip(const string &t_name,EquipType t_type)
        :m_name(t_name),m_type(t_type)
    {

    }

    void print()
    {
        cout << "装备的名字为 : " << m_name << endl;
        cout << "装备的类型为 : " << g_equipMap.find(m_type)->second << endl;
    }

    static void addPoint(Player &t_player);

    string m_name;     //装备的名字
    EquipType m_type;  //装备的类型 1.基础 2 特殊

protected:

private:
};

//技能类
class Skill
{
public:

    Skill()
    {
        m_name = g_skillName[0];
        m_type = BasicSkill;     //默认为基本技能
        m_continuedTime = 0;

    }

    Skill(const string &t_name,SkillType t_type,int t_continuedTime = 0)
        :m_name(t_name),m_type(t_type),m_continuedTime(t_continuedTime)
    {

    }

    void print()
    {
        cout << "技能的名字为 : " << m_name << endl;
        cout << "技能的类型为 : " << g_skillMap.find(m_type)->second << endl;
        cout << "技能的持续时间为 : " << m_continuedTime  << "秒 "<< endl;
    }

    static void addPoint(Player &t_player);

    string m_name;        //技能的名字
    SkillType m_type;     //技能的类型 1.基本技能 2.特殊技能
    int m_continuedTime;  //技能持续时间

protected:


private:
};

struct roleInfo
{
    string m_name;           //玩家的名字
    Level m_level;           //玩家的级别
    Type m_type;             //角色类型
    int m_HP;                //血量
    int m_MP;                //魔法量
    int m_AP;                //攻击力
    int m_DP;                //防御力
    int m_EXP;               //经验值
    Equip m_equip;           //角色使用的装备
    Skill m_skill;           //角色使用的技能
    attackSpeed m_ackSpeed;  //攻击速度
    moveSpeed m_moveSpeed;   //移动速度
    magicInvalid m_magic;    //是否魔免
    Player *m_enemy;         //攻击目标
};

struct roleData
{
    int m_HP;                //血量
    int m_MP;                //魔法量
    int m_AP;                //攻击力
    int m_DP;                //防御力

    roleData(int t_HP = 0,int t_MP = 0,int t_AP = 0,int t_DP = 0)
    {
        m_HP = t_HP;
        m_MP = t_MP;
        m_AP = t_AP;
        m_DP = t_DP;
    }
};

//玩家类
class Player
{
public:

    Player(const string &t_name = "玩家1",Level t_level = LOW_Level,Type t_type = Default_Role,const roleData &t_data = roleData());

    string m_name;      //玩家的名字
    Level m_level;      //玩家的级别
    Type m_type;        //角色类型

    //锁定目标
    bool lockTarget(Player *t_enemy);

    //打印信息
    void print();

    //攻击目标
    virtual void basisAttack() = 0;

    //魔法攻击
    virtual void magicAttack(const Skill &t_skill) = 0;

    //获取游戏的数据
    int getHP(){return m_HP;}
    int getMP(){return m_MP;}
    int getAP(){return m_AP;}
    int getDP(){return m_DP;}
    int getEXP(){return m_EXP;}
    magicInvalid getMagic(){return m_magic;}
    Equip& getEquip(){return m_equip;}
    Skill& getSkill(){return m_skill;}

    //设置游戏的数据
    void setHP(int t_HP){m_HP = t_HP;}
    void setMP(int t_MP){m_MP = t_MP;}
    void setAP(int t_AP){m_AP = t_AP;}
    void setDP(int t_DP){m_DP = t_DP;}
    void setEXP(int t_EXP){m_EXP = t_EXP;}
    void setMagic(magicInvalid t_magic){m_magic = t_magic;}
    void setEquip(Equip t_equip){m_equip = t_equip;}
    void setSkill(Skill t_skill){m_skill = t_skill;}

    //设置友元函数
    friend void Equip::addPoint(Player &t_player);
    friend void Skill::addPoint(Player &t_player);


protected:

    int m_HP;        //血量
    int m_MP;        //魔法量
    int m_AP;        //攻击力
    int m_DP;        //防御力
    int m_EXP;       //经验值

    Equip m_equip;           //角色使用的装备
    Skill m_skill;           //角色使用的技能
    attackSpeed m_ackSpeed;  //攻击速度
    moveSpeed m_moveSpeed;   //移动速度
    magicInvalid m_magic;    //是否魔免
    Player *m_enemy;         //攻击目标

private:

};

#endif // PLAYER_H
