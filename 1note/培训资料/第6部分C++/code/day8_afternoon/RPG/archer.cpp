#include "archer.h"


//���캯��
//�����ֵ�Ѫ��Ϊ80,ħ����Ϊ120,������Ϊ25,������Ϊ3
Archer::Archer(const string &t_name, Level t_level)
    :Player(t_name,t_level,ArcHer,roleData(80,120,25,3))
{
    //װ��Ϊ����,����װ��
    m_equip = Equip(g_equipName[2],BasicEquip);
    m_skill = Skill(g_skillName[2],SpecialSkill);
}

//�����ֻ�������
void Archer::basisAttack()
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

//������ħ������
void Archer::magicAttack(const Skill &t_skill)
{
    //���ħ��ֵ����,���ܷ���ħ������(����һ��ħ��������Ҫ40��ħ��ֵ)
    if(m_MP < 40)
    {
        cout << "û���㹻��ħ��ֵ����ô�ħ������!" << endl;
        return;
    }

    //����Է���ħ���,���޷���������ħ������
    if(m_enemy->getMagic() == Invalid_true)
    {
        cout << "�Է����ڴ���ħ��״̬,�޷���������ħ������" << endl;
    }

    //�����ֿ���ʩչ���Ǽ�,��Ѫ���ȼ���
    //���Ǽ� : ���ĶԷ�45������ֵ,�����Լ�40��ħ��ֵ,����ʱ��2��
    if(t_skill.m_name == "���Ǽ�")
    {
        m_MP -= 40;
        m_enemy->setHP(m_enemy->getHP() - 45);
    }
    //��Ѫ�� : ����������30,���Է�����Ѫ����15%ת��Ϊ�Լ���Ѫ��,����ʱ��3��
    else if(t_skill.m_name == "��Ѫ��")
    {
        m_AP += 30;
        m_HP += (m_AP - m_enemy->getDP())*0.15;
    }

    //��ӡ������Ϣ
    cout << m_name << " ����:" << g_roleMap.find(m_type)->second << "��"  << g_skillMap.find(m_skill.m_type)->second << ":" << m_skill.m_name << "����"
         << " " << m_enemy->m_name << " ����Ϊ:" << g_roleMap.find(m_enemy->m_type)->second << endl;
}




