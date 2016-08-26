#include "player.h"

//�ϳ�װ��,����ɫ�����Ե�
void Equip::addPoint(Player &t_player)
{
    //��ȡ��ɫ��װ����
    string t_equipName = t_player.getEquip().m_name;
    EquipType t_equipType = t_player.getEquip().m_type;

    //����ǻ���װ��,�򲻼ӵ�
    if(t_equipType == BasicEquip)
    {
        cout << "��װ��Ϊ����װ��,���ӵ�!" << endl;
        return;
    }

    //���丫:������+15,Ѫ��+50,ħ��
    if(t_equipName == "���丫")
    {
        t_player.m_AP += 15;
        t_player.m_HP += 50;
        t_player.m_magic = Invalid_true;
    }
    //���콣:������+30��ÿ����һ�ν������Լ��Ĺ�����15%ת�ӵ��Լ�������ֵ��
    else if(t_equipName == "���콣")
    {
        t_player.m_AP += 30;
    }
    //Դʽ��:������+10����15%�ļ��ʶ������ֵĹ���60��
    else if(t_equipName == "Դʽ��")
    {
        t_player.m_DP += 10;
    }
}

//ʩչ����,����ɫ�����Ե�
void Skill::addPoint(Player &t_player)
{
    //��ȡ��ɫ���ܵ����ֺ�����
    string t_skillName = t_player.getSkill().m_name;

    //�ؽ�ն:����������60��,����5��
    if(t_skillName == "�ؽ�ն")
    {
        t_player.m_AP += 60;
    }
    //���Ǽ�:����������40��,�����ٶȼӱ�,����3��
    else if(t_skillName == "���Ǽ�")
    {
        t_player.m_AP += 40;
        t_player.m_ackSpeed = Twice_ACK;
    }
    //��Ѫ��:����������50��,���Եз��������˺�ֵ��20%ת��Ϊ�Լ���Ѫ��
    else if(t_skillName == "��Ѫ��")
    {
        t_player.m_AP += 50;

    }
    //�����·�:������+30,����+10,ħ��(����ħ������)
    else if(t_skillName == "�����·�")
    {
        t_player.m_AP += 30;
        t_player.m_DP += 10;
        t_player.m_magic = Invalid_true;
    }
    //������˫:�����ٶ�+100%���ƶ��ٶ�+100%
    else if(t_skillName == "������˫")
    {
        t_player.m_ackSpeed = Twice_ACK;
        t_player.m_moveSpeed = Twice_MV;
    }

}

//��ʼ������
Player::Player(const string &t_name,Level t_level,Type t_type,const roleData &t_data):m_enemy(0)
{
    m_name = t_name;
    m_level = t_level;            //Ĭ��Ϊ����
    m_type = t_type;              //Ĭ������

    m_HP = t_data.m_HP;                   //Ĭ��Ϊ100��
    m_MP = t_data.m_MP;                    //Ĭ��Ϊ50��
    m_AP = t_data.m_AP;                    //Ĭ��Ϊ50��
    m_DP = t_data.m_DP;                    //Ĭ��Ϊ30��
    m_EXP = 0;                    //Ĭ��Ϊ0
    //m_equip =
    m_ackSpeed = Normal_ACK;      //Ĭ��Ϊ��������
    m_moveSpeed = Normal_MV;      //Ĭ��Ϊ�����ƶ��ٶ�
    m_magic = Invalid_false;      //Ĭ��Ϊ��ħ��
}

//�вεĹ��캯��
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

//����Ŀ��
bool Player::lockTarget(Player *t_enemy)
{
    //�Լ�Ѫ��Ϊ��
    if(m_HP <= 0)
    {
        cout << "���:" << m_name << "Ѫ��Ϊ��,��������Ŀ��ʧ��!" << endl;
        return false;
    }

    //���Ŀ�겻����
    if(t_enemy == NULL)
    {
        cout << "��������Ŀ�겻����!" << endl;
        return false;
    }

    //���������Ŀ�����Լ�
    if(t_enemy == this)
    {
        cout << "�����Լ������Լ�!" << endl;
        return false;
    }

    //���������Ŀ��Ѫ��Ϊ��
    if(t_enemy->getHP() <= 0)
    {
        cout << "������Ŀ��:" << t_enemy->m_name  << " �Ѿ�����!" << endl;
        return false;
    }

    m_enemy = t_enemy;

    return true;
}

//��ӡ��Ϣ
void Player::print()
{
    cout << "--------------------------------------------------------------------------------";
    cout << "��ɫ��:" << m_name << "  �ȼ�:" << g_levelMap.find(m_level)->second << "  ����:" << g_roleMap.find(m_type)->second << "  ����ֵ:" << m_EXP << "  Ѫ��:" << m_HP << "  ħ��ֵ:" << m_MP << "  ������:" << m_AP << endl;
    cout << "������:" << m_DP << "  װ��:" << m_equip.m_name << "  װ������:" << g_equipMap.find(m_equip.m_type)->second << "  �����ٶ�:" << g_ackSpeedMap.find(m_ackSpeed)->second << "  �ƶ��ٶ�:" << g_moveSpeedMap.find(m_moveSpeed)->second
         << "  ����:" << m_skill.m_name << "  ��������:" << g_skillMap.find(m_skill.m_type)->second << "  " << g_magicInvalidMap.find(m_magic)->second << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
}





