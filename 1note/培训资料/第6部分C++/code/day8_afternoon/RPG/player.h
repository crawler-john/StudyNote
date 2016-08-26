#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "common.h"

using namespace std;

class Player;

//װ����
class Equip
{
public:

    Equip()
    {
        m_name = g_equipName[0];
        m_type = BasicEquip;     //Ĭ��Ϊ����װ��
    }

    Equip(const string &t_name,EquipType t_type)
        :m_name(t_name),m_type(t_type)
    {

    }

    void print()
    {
        cout << "װ��������Ϊ : " << m_name << endl;
        cout << "װ��������Ϊ : " << g_equipMap.find(m_type)->second << endl;
    }

    static void addPoint(Player &t_player);

    string m_name;     //װ��������
    EquipType m_type;  //װ�������� 1.���� 2 ����

protected:

private:
};

//������
class Skill
{
public:

    Skill()
    {
        m_name = g_skillName[0];
        m_type = BasicSkill;     //Ĭ��Ϊ��������
        m_continuedTime = 0;

    }

    Skill(const string &t_name,SkillType t_type,int t_continuedTime = 0)
        :m_name(t_name),m_type(t_type),m_continuedTime(t_continuedTime)
    {

    }

    void print()
    {
        cout << "���ܵ�����Ϊ : " << m_name << endl;
        cout << "���ܵ�����Ϊ : " << g_skillMap.find(m_type)->second << endl;
        cout << "���ܵĳ���ʱ��Ϊ : " << m_continuedTime  << "�� "<< endl;
    }

    static void addPoint(Player &t_player);

    string m_name;        //���ܵ�����
    SkillType m_type;     //���ܵ����� 1.�������� 2.���⼼��
    int m_continuedTime;  //���ܳ���ʱ��

protected:


private:
};

struct roleInfo
{
    string m_name;           //��ҵ�����
    Level m_level;           //��ҵļ���
    Type m_type;             //��ɫ����
    int m_HP;                //Ѫ��
    int m_MP;                //ħ����
    int m_AP;                //������
    int m_DP;                //������
    int m_EXP;               //����ֵ
    Equip m_equip;           //��ɫʹ�õ�װ��
    Skill m_skill;           //��ɫʹ�õļ���
    attackSpeed m_ackSpeed;  //�����ٶ�
    moveSpeed m_moveSpeed;   //�ƶ��ٶ�
    magicInvalid m_magic;    //�Ƿ�ħ��
    Player *m_enemy;         //����Ŀ��
};

struct roleData
{
    int m_HP;                //Ѫ��
    int m_MP;                //ħ����
    int m_AP;                //������
    int m_DP;                //������

    roleData(int t_HP = 0,int t_MP = 0,int t_AP = 0,int t_DP = 0)
    {
        m_HP = t_HP;
        m_MP = t_MP;
        m_AP = t_AP;
        m_DP = t_DP;
    }
};

//�����
class Player
{
public:

    Player(const string &t_name = "���1",Level t_level = LOW_Level,Type t_type = Default_Role,const roleData &t_data = roleData());

    string m_name;      //��ҵ�����
    Level m_level;      //��ҵļ���
    Type m_type;        //��ɫ����

    //����Ŀ��
    bool lockTarget(Player *t_enemy);

    //��ӡ��Ϣ
    void print();

    //����Ŀ��
    virtual void basisAttack() = 0;

    //ħ������
    virtual void magicAttack(const Skill &t_skill) = 0;

    //��ȡ��Ϸ������
    int getHP(){return m_HP;}
    int getMP(){return m_MP;}
    int getAP(){return m_AP;}
    int getDP(){return m_DP;}
    int getEXP(){return m_EXP;}
    magicInvalid getMagic(){return m_magic;}
    Equip& getEquip(){return m_equip;}
    Skill& getSkill(){return m_skill;}

    //������Ϸ������
    void setHP(int t_HP){m_HP = t_HP;}
    void setMP(int t_MP){m_MP = t_MP;}
    void setAP(int t_AP){m_AP = t_AP;}
    void setDP(int t_DP){m_DP = t_DP;}
    void setEXP(int t_EXP){m_EXP = t_EXP;}
    void setMagic(magicInvalid t_magic){m_magic = t_magic;}
    void setEquip(Equip t_equip){m_equip = t_equip;}
    void setSkill(Skill t_skill){m_skill = t_skill;}

    //������Ԫ����
    friend void Equip::addPoint(Player &t_player);
    friend void Skill::addPoint(Player &t_player);


protected:

    int m_HP;        //Ѫ��
    int m_MP;        //ħ����
    int m_AP;        //������
    int m_DP;        //������
    int m_EXP;       //����ֵ

    Equip m_equip;           //��ɫʹ�õ�װ��
    Skill m_skill;           //��ɫʹ�õļ���
    attackSpeed m_ackSpeed;  //�����ٶ�
    moveSpeed m_moveSpeed;   //�ƶ��ٶ�
    magicInvalid m_magic;    //�Ƿ�ħ��
    Player *m_enemy;         //����Ŀ��

private:

};

#endif // PLAYER_H
