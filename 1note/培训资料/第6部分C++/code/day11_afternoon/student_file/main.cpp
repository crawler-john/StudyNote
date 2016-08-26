#include <iostream>
#include <fstream>
#include "student.h"

using namespace std;

#define NUM 10

int main()
{
    //二进制文件名
    string t_binFileName = "student.data";

    //文本文件名
    string t_txtFileName = "student.txt";

    //写入文件的数据
    student t_array[NUM] =
    {student("张飞"),student("关羽"),student("刘备"),student("貂蝉"),student("孔明"),
     student("曹操"),student("郭嘉"),student("典韦"),student("司马"),student("曹仁")};

    //装从文件读出的学生数据
    student t_outArray[NUM];

    cout << "11111111111111111111111111111" << endl;

    //打印写入文件前的数据信息
    for(int i = 0; i < NUM ; i++)
    {
        t_array[i].print();

        cout << "***********************" << endl;
    }

    cout << "222222222222222222222222222222" << endl;

    #if 0     //写读二进制文件

    //写二进制文件
    /*ofstream t_writeBinFile(t_binFileName.c_str(),ios_base::out|ios_base::binary);

    //判断文件打开是否成功
    if(!t_writeBinFile.is_open())
    {
        cout << "open file : " << t_binFileName << " failed!" << endl;
        return -1;
    }

    for(int i = 0; i < NUM; i++)
    {
        t_writeBinFile.write((char*)&t_array[i],sizeof(student));
    }

    //关闭文件
    t_writeBinFile.close();*/

    //读二进制文件
    ifstream t_readBinFile(t_binFileName.c_str(),ios_base::in|ios_base::binary);

    //判断文件打开是否成功
    if(!t_readBinFile.is_open())
    {
        cout << "open file : " << t_binFileName << " failed!" << endl;
        return -1;
    }

    for(int i = 0; i < NUM; i++)
    {
        t_readBinFile.read((char *)&t_outArray[i],sizeof(student));
    }

    //关闭文件
    t_readBinFile.close();

//    cout << endl << endl;

    #endif

    #if 1   //写读文本文件
    /*ofstream t_writeFile(t_txtFileName.c_str(),ios_base::out);

    //判断文件打开是否成功
    if(!t_writeFile.is_open())
    {
        cout << "open file : " << t_txtFileName << " failed!";
        return -1;
    }

    //将t_array的数据写入文件
    for(int i = 0; i < NUM; i++)
    {
        t_writeFile << t_array[i].m_name << "#" << t_array[i].m_ID << "#" << t_array[i].m_sex << "#"
                    << t_array[i].m_chinese << "#" << t_array[i].m_maths << "#" << t_array[i].m_english << endl;
    }

    //关闭文件
    t_writeFile.close();*/

    ifstream t_readFile(t_txtFileName.c_str(),ios_base::in);

    //判断文件是否打开成功
    if(!t_readFile.is_open())
    {
        cout << "open file : " << t_txtFileName << " failed!" << endl;
        return -1;
    }

    //将文件的数据以每行的方式读出来,再进行分割处理
    char t_lineContext[1024];
    string t_lineData;

    int t_lineNum = 0;  //行号(非空行的)

    while(!t_readFile.eof())
    {
        t_readFile.getline(t_lineContext,1024);
        t_lineData = string(t_lineContext);

        //如果是空行就过滤掉
        if(t_lineData.empty())
        {
            continue;
        }

        t_lineNum++;

        cout << "line " << t_lineNum << " : " << t_lineData << endl;

        //用于存放每行的学生的数据(6个)
        string t_studentData[6];

        for(int i = 0; i < 6; i++)
        {
            //查找到第一个"#"的位置
            int t_pos = t_lineData.find_first_of("#");

            //截取第一个"#"之前的数据并保存到t_studentData数组中
            t_studentData[i] = t_lineData.substr(0,t_pos);

            //将原t_lineData行的第一个"#"前面部分的数据截掉
            t_lineData = t_lineData.substr(t_pos+1);

            //测试时打开该注释
            //cout << "t_studentData[" << i << "] : " << t_studentData[i] << " ";
        }

        //cout << endl;

        //将文件的数据赋值给t_outArray数组中
        strcpy(t_outArray[t_lineNum-1].m_name,t_studentData[0].c_str());
        t_outArray[t_lineNum-1].m_ID = atoi(t_studentData[1].c_str());
        strcpy(t_outArray[t_lineNum-1].m_sex,t_studentData[2].c_str());
        t_outArray[t_lineNum-1].m_chinese = atof(t_studentData[3].c_str());
        t_outArray[t_lineNum-1].m_maths = atof(t_studentData[4].c_str());
        t_outArray[t_lineNum-1].m_english = atof(t_studentData[5].c_str());


    }

    //关闭文件
    t_readFile.close();

    #endif

    //打印信息

    for(int i = 0; i < NUM; i++)
    {
        t_outArray[i].print();

        cout << "%%%%%%%%%%%%%%%%%%%%" << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}

