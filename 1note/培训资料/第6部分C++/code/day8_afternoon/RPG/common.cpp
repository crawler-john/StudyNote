#include "common.h"

string g_equipName[7] = {
    "Ĭ��װ��",
    "��",
    "����",
    "ħ����",
    "���丫",
    "���콣",
    "Դʽ��"
};

string g_skillName[6] = {
    "Ĭ�ϼ���",
    "�ؽ�ն",
    "���Ǽ�",
    "��Ѫ��",
    "�����·�",
    "������˫"
};

map<roleType,string> g_roleMap;
map<Level,string> g_levelMap;
map<EquipType,string> g_equipMap;
map<SkillType,string> g_skillMap;
map<attackSpeed,string> g_ackSpeedMap;
map<moveSpeed,string> g_moveSpeedMap;
map<magicInvalid,string> g_magicInvalidMap;


void Game::init()
{
    //��ö��ֵ���ַ�����Ӧ����
    g_roleMap.insert(pair<roleType,string>(Default_Role,"Ĭ������"));
    g_roleMap.insert(pair<roleType,string>(Sword_Man,"��ʿ"));
    g_roleMap.insert(pair<roleType,string>(ArcHer,"������"));
    g_roleMap.insert(pair<roleType,string>(MagiCian,"��ʦ"));

    g_levelMap.insert(pair<Level,string>(LOW_Level,"����"));
    g_levelMap.insert(pair<Level,string>(MIDDLE_Level,"�м�"));
    g_levelMap.insert(pair<Level,string>(HIGH_Level,"�߼�"));

    g_equipMap.insert(pair<EquipType,string>(BasicEquip,"����װ��"));
    g_equipMap.insert(pair<EquipType,string>(SpecialEquip,"����װ��"));

    g_skillMap.insert(pair<SkillType,string>(BasicSkill,"��������"));
    g_skillMap.insert(pair<SkillType,string>(SpecialSkill,"���⼼��"));

    g_ackSpeedMap.insert(pair<attackSpeed,string>(Normal_ACK,"����"));
    g_ackSpeedMap.insert(pair<attackSpeed,string>(Twice_ACK,"����"));

    g_moveSpeedMap.insert(pair<moveSpeed,string>(Normal_MV,"����"));
    g_moveSpeedMap.insert(pair<moveSpeed,string>(Twice_MV,"����"));

    g_magicInvalidMap.insert(pair<magicInvalid,string>(Invalid_true,"ħ��"));
    g_magicInvalidMap.insert(pair<magicInvalid,string>(Invalid_false,"��ħ��"));
}
