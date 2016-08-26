#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <map>

using namespace std;

extern string g_equipName[7];
extern string g_skillName[6];

//角色类型
typedef enum roleType
{
    Default_Role = 1,  //默认类型
    Sword_Man = 2,     //剑士
    ArcHer = 3,        //弓箭手
    MagiCian = 4       //魔法师

}Type;

//玩家级别
typedef enum playerLevel
{
    LOW_Level = 1,      //初级玩家
    MIDDLE_Level = 2,   //中级玩家
    HIGH_Level = 3      //高级玩家
}Level;

//装备类型
enum EquipType
{
    BasicEquip = 1,     //基础装备
    SpecialEquip = 2    //特殊装备
};

//技能类型
enum SkillType
{
    BasicSkill = 1,     //基础技能
    SpecialSkill = 2    //特殊技能
};

//攻击速度
enum attackSpeed
{
    Normal_ACK = 1,     //正常攻速
    Twice_ACK = 2       //二倍攻速
};

//移动速度
enum moveSpeed
{
    Normal_MV = 1,       //正常移动速度
    Twice_MV = 2         //二倍移动速度
};

//是否魔免
enum magicInvalid
{
    Invalid_true = 1,    //魔免
    Invalid_false = 2    //非魔免
};

//用于存放信息的容器
extern map<roleType,string> g_roleMap;
extern map<Level,string> g_levelMap;
extern map<EquipType,string> g_equipMap;
extern map<SkillType,string> g_skillMap;
extern map<attackSpeed,string> g_ackSpeedMap;
extern map<moveSpeed,string> g_moveSpeedMap;
extern map<magicInvalid,string> g_magicInvalidMap;

class Game
{
public:

    //初始化游戏的数据
    static void init();

private:
};


#endif // COMMON_H
