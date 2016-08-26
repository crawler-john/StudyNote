#include <iostream>
#include <fstream>
#include "student.h"

using namespace std;

#define NUM 10

int main()
{
    //�������ļ���
    string t_binFileName = "student.data";

    //�ı��ļ���
    string t_txtFileName = "student.txt";

    //д���ļ�������
    student t_array[NUM] =
    {student("�ŷ�"),student("����"),student("����"),student("����"),student("����"),
     student("�ܲ�"),student("����"),student("��Τ"),student("˾��"),student("����")};

    //װ���ļ�������ѧ������
    student t_outArray[NUM];

    cout << "11111111111111111111111111111" << endl;

    //��ӡд���ļ�ǰ��������Ϣ
    for(int i = 0; i < NUM ; i++)
    {
        t_array[i].print();

        cout << "***********************" << endl;
    }

    cout << "222222222222222222222222222222" << endl;

    #if 0     //д���������ļ�

    //д�������ļ�
    /*ofstream t_writeBinFile(t_binFileName.c_str(),ios_base::out|ios_base::binary);

    //�ж��ļ����Ƿ�ɹ�
    if(!t_writeBinFile.is_open())
    {
        cout << "open file : " << t_binFileName << " failed!" << endl;
        return -1;
    }

    for(int i = 0; i < NUM; i++)
    {
        t_writeBinFile.write((char*)&t_array[i],sizeof(student));
    }

    //�ر��ļ�
    t_writeBinFile.close();*/

    //���������ļ�
    ifstream t_readBinFile(t_binFileName.c_str(),ios_base::in|ios_base::binary);

    //�ж��ļ����Ƿ�ɹ�
    if(!t_readBinFile.is_open())
    {
        cout << "open file : " << t_binFileName << " failed!" << endl;
        return -1;
    }

    for(int i = 0; i < NUM; i++)
    {
        t_readBinFile.read((char *)&t_outArray[i],sizeof(student));
    }

    //�ر��ļ�
    t_readBinFile.close();

//    cout << endl << endl;

    #endif

    #if 1   //д���ı��ļ�
    /*ofstream t_writeFile(t_txtFileName.c_str(),ios_base::out);

    //�ж��ļ����Ƿ�ɹ�
    if(!t_writeFile.is_open())
    {
        cout << "open file : " << t_txtFileName << " failed!";
        return -1;
    }

    //��t_array������д���ļ�
    for(int i = 0; i < NUM; i++)
    {
        t_writeFile << t_array[i].m_name << "#" << t_array[i].m_ID << "#" << t_array[i].m_sex << "#"
                    << t_array[i].m_chinese << "#" << t_array[i].m_maths << "#" << t_array[i].m_english << endl;
    }

    //�ر��ļ�
    t_writeFile.close();*/

    ifstream t_readFile(t_txtFileName.c_str(),ios_base::in);

    //�ж��ļ��Ƿ�򿪳ɹ�
    if(!t_readFile.is_open())
    {
        cout << "open file : " << t_txtFileName << " failed!" << endl;
        return -1;
    }

    //���ļ���������ÿ�еķ�ʽ������,�ٽ��зָ��
    char t_lineContext[1024];
    string t_lineData;

    int t_lineNum = 0;  //�к�(�ǿ��е�)

    while(!t_readFile.eof())
    {
        t_readFile.getline(t_lineContext,1024);
        t_lineData = string(t_lineContext);

        //����ǿ��о͹��˵�
        if(t_lineData.empty())
        {
            continue;
        }

        t_lineNum++;

        cout << "line " << t_lineNum << " : " << t_lineData << endl;

        //���ڴ��ÿ�е�ѧ��������(6��)
        string t_studentData[6];

        for(int i = 0; i < 6; i++)
        {
            //���ҵ���һ��"#"��λ��
            int t_pos = t_lineData.find_first_of("#");

            //��ȡ��һ��"#"֮ǰ�����ݲ����浽t_studentData������
            t_studentData[i] = t_lineData.substr(0,t_pos);

            //��ԭt_lineData�еĵ�һ��"#"ǰ�沿�ֵ����ݽص�
            t_lineData = t_lineData.substr(t_pos+1);

            //����ʱ�򿪸�ע��
            //cout << "t_studentData[" << i << "] : " << t_studentData[i] << " ";
        }

        //cout << endl;

        //���ļ������ݸ�ֵ��t_outArray������
        strcpy(t_outArray[t_lineNum-1].m_name,t_studentData[0].c_str());
        t_outArray[t_lineNum-1].m_ID = atoi(t_studentData[1].c_str());
        strcpy(t_outArray[t_lineNum-1].m_sex,t_studentData[2].c_str());
        t_outArray[t_lineNum-1].m_chinese = atof(t_studentData[3].c_str());
        t_outArray[t_lineNum-1].m_maths = atof(t_studentData[4].c_str());
        t_outArray[t_lineNum-1].m_english = atof(t_studentData[5].c_str());


    }

    //�ر��ļ�
    t_readFile.close();

    #endif

    //��ӡ��Ϣ

    for(int i = 0; i < NUM; i++)
    {
        t_outArray[i].print();

        cout << "%%%%%%%%%%%%%%%%%%%%" << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}

