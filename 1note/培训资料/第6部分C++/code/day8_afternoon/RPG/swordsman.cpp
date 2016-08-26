#include "swordsman.h"

//���캯��
//��ʿ��Ѫ��Ϊ100,ħ����Ϊ100,������Ϊ30,������Ϊ5
Swordsman::Swordsman(const string &t_name,Level t_level)
    :Player(t_name,t_level,Sword_Man,roleData(100,100,30,5))
{
    //װ��Ϊ��,����װ��
    m_equip = Equip(g_equipName[1],BasicEquip);
    m_skill = Skill(g_skillName[1],SpecialSkill);

}

void Swordsman::basisAttack()
{
    //�����������Ŀ��Ѫ��Ϊ0
    if(m_enemy->getHP() <= 0)
    {
        cout << "Ŀ��:" << m_enemy->m_name << " Ѫ��Ϊ��,�Ѿ�����!" << endl;
        return;
    }

    //�Է�����Ѫ��
    int t_consumeHP = 0;

    //����һ��������
    if(m_ackSpeed == Normal_ACK)   //��������
    {
        //�Է�����Ѫ��
        t_consumeHP = m_AP - m_enemy->getDP();
    }
    else if(m_ackSpeed == Twice_ACK)  //��������
    {
        //�Է�����Ѫ��
        t_consumeHP = 2*(m_AP - m_enemy->getDP());
    }

    //�Է�ʣ��Ѫ��Ϊ
    m_enemy->setHP(m_enemy->getHP() - t_consumeHP);

    //��ӡ������Ϣ
    cout << m_name << " ����:" << (g_roleMap.find(m_type)->second) + ", " << "��" << m_equip.m_name << "����"
         << " " << m_enemy->m_name << " ����Ϊ:" << g_roleMap.find(m_enemy->m_type)->second << endl;


}

//ħ������
void Swordsman::magicAttack(const Skill &t_skill)
{    
    //���ħ��ֵ����,���ܷ���ħ������(����һ��ħ��������Ҫ50��ħ��ֵ)
    if(m_MP < 50)
    {
        cout << "û���㹻��ħ��ֵ����ô�ħ������!" << endl;
        return;
    }

    //����Է���ħ���,���޷���������ħ������
    if(m_enemy->getMagic() == Invalid_true)
    {
        cout << "�Է����ڴ���ħ��״̬,�޷���������ħ������" << endl;
    }

    //��ʿ����ʩչ�ؽ�ն,�����·��ȼ���
    //�ؽ�ն : ���ĶԷ�60������ֵ,�����Լ�50��ħ��ֵ,����ʱ��1��
    if(t_skill.m_name == "�ؽ�ն")
    {
        m_MP -= 50;
        m_enemy->setHP(m_enemy->getHP() - 60);
    }
    //�����·� : ������+30,����+10,ħ��(����ħ������),����ʱ��5��
    else if(t_skill.m_name == "�����·�")
    {
        m_AP += 30;
        m_DP += 10;
        m_magic = Invalid_true;
    }

    //��ӡ������Ϣ
    cout << m_name << " ����:" << g_roleMap.find(m_type)->second << "��"  << g_skillMap.find(m_skill.m_type)->second << ":" << m_skill.m_name << "����"
         << " " << m_enemy->m_name << " ����Ϊ:" << g_roleMap.find(m_enemy->m_type)->second << endl;

}




