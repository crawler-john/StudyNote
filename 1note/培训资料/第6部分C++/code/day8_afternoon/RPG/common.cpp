#include "common.h"

string g_equipName[7] = {
    "默认装备",
    "剑",
    "弓箭",
    "魔法杖",
    "玄武斧",
    "倚天剑",
    "源式铠"
};

string g_skillName[6] = {
    "默认技能",
    "重剑斩",
    "流星箭",
    "吸血术",
    "天神下凡",
    "天下无双"
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
    //将枚举值与字符串对应起来
    g_roleMap.insert(pair<roleType,string>(Default_Role,"默认类型"));
    g_roleMap.insert(pair<roleType,string>(Sword_Man,"剑士"));
    g_roleMap.insert(pair<roleType,string>(ArcHer,"弓箭手"));
    g_roleMap.insert(pair<roleType,string>(MagiCian,"法师"));

    g_levelMap.insert(pair<Level,string>(LOW_Level,"初级"));
    g_levelMap.insert(pair<Level,string>(MIDDLE_Level,"中级"));
    g_levelMap.insert(pair<Level,string>(HIGH_Level,"高级"));

    g_equipMap.insert(pair<EquipType,string>(BasicEquip,"基础装备"));
    g_equipMap.insert(pair<EquipType,string>(SpecialEquip,"特殊装备"));

    g_skillMap.insert(pair<SkillType,string>(BasicSkill,"基础技能"));
    g_skillMap.insert(pair<SkillType,string>(SpecialSkill,"特殊技能"));

    g_ackSpeedMap.insert(pair<attackSpeed,string>(Normal_ACK,"正常"));
    g_ackSpeedMap.insert(pair<attackSpeed,string>(Twice_ACK,"二倍"));

    g_moveSpeedMap.insert(pair<moveSpeed,string>(Normal_MV,"正常"));
    g_moveSpeedMap.insert(pair<moveSpeed,string>(Twice_MV,"二倍"));

    g_magicInvalidMap.insert(pair<magicInvalid,string>(Invalid_true,"魔免"));
    g_magicInvalidMap.insert(pair<magicInvalid,string>(Invalid_false,"非魔免"));
}
