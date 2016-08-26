#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

int main()
{
    const string t_fileName = "test123.txt";

    //写文本文件
//    ofstream t_writeFile(t_fileName.c_str(),ios_base::out);

//    //t_writeFile.open(t_fileName.c_str(),ios_base::out);

//    //判断文件打开是否成功
//    if(!t_writeFile.is_open())
//    {
//        cout << "open file : " << t_fileName << " failed!" << endl;
//        return -1;
//    }

//    //将常字符串写入文件中
//    t_writeFile << "123456789\n";

//    //将指针指向的字符串写入到文件中
//    char *t_p1 = "hello world! 123789\n";

//    t_writeFile << t_p1;

//    //将数组中的数据写入文件中
//    char t_data[100] = "abcdefgsfjlkds\n";

//    //t_writeFile << t_data;

//    t_writeFile.write(t_data,strlen(t_data));

//    //从键盘中以单个字符形式写入到文件中,以tab键结束
////    char t_ch;

////    while(cin.get(t_ch))
////    {
////        if(t_ch == '\t')
////        {
////            break;
////        }

////        t_writeFile << t_ch;
////    }

//    //从键盘中将一行字符写入到文件中
//    char t_lineData[1024];

//    cin.getline(t_lineData,1024);

//    t_writeFile << t_lineData;

//    //关闭文件
//    t_writeFile.close();

    //读文本文件
    ifstream t_readFile(t_fileName.c_str(),ios_base::in);

    if(!t_readFile.is_open())
    {
        cout << "open file : " << t_fileName << " failed!" << endl;
        return -1;
    }

    //将文件的数据直接打印到屏幕上,以单个字符形式
//    char t_ch;

//    while(t_readFile.get(t_ch))
//    {
//        cout << t_ch;
//    }

//    cout << endl;

    //将文件的数据全部读入一个数组中

//    t_readFile.seekg(0,ios_base::end);

//    int t_fileSize = t_readFile.tellg();

//    char t_fileData[t_fileSize+1];
//    memset(t_fileData,0,t_fileSize+1);

//    t_readFile.seekg(0,ios_base::beg);

//    t_readFile.read(t_fileData,t_fileSize);

//    cout << "t_fileData : " << t_fileData << endl;

    //将文件的数据以每行的形式读出来
    char t_lineData[1024];
    string t_lineData2;

    int t_lineNum = 0;

    while(!t_readFile.eof())
    {
        t_readFile.getline(t_lineData,1024);
        t_lineData2 = string(t_lineData);

        if(t_lineData2.empty())
        {
            continue;
        }

        t_lineNum++;

        cout << "line " << t_lineNum << " : " << t_lineData2 << endl;

    }

    t_readFile.close();


    cout << "Hello World!" << endl;
    return 0;
}

