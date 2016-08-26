#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include "person.h"

using namespace std;


//try语句块中放将可能发生异常的代码
//throw抛出异常
//catch捕获异常

void inputChoice()
{
    while(1)
    {
        cout << "请输入用户的选择(1~5):" << endl;
        int t_choice;
        cin >> t_choice;
        switch(t_choice)
        {
        case 1:
            throw Chinese();
            break;
        case 2:
            throw Japanese();
            break;
        case 3:
            throw American();
            break;
        case 4:
            throw English();
            break;
        case 5:
            throw person();
            break;
        default:
            cout << "没有该用户选项,请重新输入!" << endl;
            break;
        }
    }
}

int fun1(int t_x,int t_y)
{
    if(t_y == 0)
    {
        throw t_y;
    }
    else
    {
        return t_x/t_y;
    }
}

char fun2(char t_char)
{
    if(t_char == '\0')
    {
        throw t_char;
    }
    else
    {
        return t_char;
    }
}

char* fun3(char *t_p1)
{
    if(t_p1 == NULL)
    {
        throw t_p1;
    }
    else
    {
        return t_p1;
    }
}

person fun4(person &t_person)
{
    if(t_person.getAge() < 0)
    {
        throw t_person;
    }
    else
    {
        return t_person;
    }
}


int main()
{
    string t_fileName = "test123.txt";

//    try
//    {
//        FILE *fp = fopen(t_fileName.c_str(),"r");

//        if(!fp)
//        {
//            throw t_fileName;
//        }
//        else
//        {
//            //将文件指针移动到文件尾
//            fseek(fp,0,SEEK_END);

//            //获取文件的大小
//            int t_fileSize = ftell(fp);

//            //申请一个数组
//            char t_fileData[t_fileSize + 1];

//            memset(t_fileData,0,t_fileSize+1);

//            //将文件指针移动到文件头
//            fseek(fp,0,SEEK_SET);

//            fread(t_fileData,1,t_fileSize,fp);

//            fclose(fp);

//            cout << "file data : " << t_fileData << endl;

//        }

//        cout << "1111111111111111111111111" << endl;
//    }
//    //catch中的形参只能有一个
////    catch(string t_fileName)
////    {
////        cout << "open file : " << t_fileName << " failed!" << endl;
////    }
////    catch(string &t_fileName)
////    {
////        cout << "2open file : " << t_fileName << " failed!" << endl;
////    }
//    //当没有catch捕获到异常时,系统自动调用abort()函数结束该进程
//    catch(int t_a)
//    {
//        cout << "222222222222222222" << endl;
//    }
//    //捕获所有的异常
//    catch(...)
//    {
//        cout << "捕获所有的异常!" << endl;
//    }
//    try
//    {
////        cout << "fun1(8,4) : " << fun1(8,4) << endl;
////        cout << "fun1(5,0) : " << fun1(5,0) << endl;
////        cout << "fun1(3,1) : " << fun1(3,1) << endl;

////        cout << fun2('a') << endl;
////        cout << fun2('\0') << endl;

////        char *t_p1 = "123";
////        cout << fun3(t_p1) << endl;
////        t_p1 = 0;
////        cout << fun3(t_p1) << endl;

//        person t_person1;

//        fun4(t_person1).print();

//        t_person1.setAge(-100);

//        fun4(t_person1).print();
//    }
//    catch(int t_a)
//    {
//        cout << "除数不能为 : " << t_a << endl;
//    }
//    catch(char t_a)
//    {
//        cout << "字符不能为空!" << endl;
//    }
//    catch(char *t_p1)
//    {
//        cout << "指针不能为NULL!" << endl;
//    }
//    catch(person &t_person)
//    {
//        cout << "人的年龄不能为 : " << t_person.getAge() << endl;
//    }

//    map<errType,string> t_map1;
//    map<errType,string>::iterator t_iter1;

//    t_map1.insert(pair<errType,string>(DEFAULT_TYPE,"默认类型"));
//    t_map1.insert(pair<errType,string>(CALLER_DISCONNECT,"主叫断开"));
//    t_map1.insert(pair<errType,string>(CALLED_DISCONNECT,"被叫断开"));
//    t_map1.insert(pair<errType,string>(TIME_OUT,"超时"));

//    for(t_iter1 = t_map1.begin();t_iter1 != t_map1.end();t_iter1++)
//    {
//        cout << "map1 key : " << t_iter1->first << " and value : " << t_iter1->second << endl;
//    }

//    try
//    {
//        int t_input;

//        cout << "请输入呼叫断开的原因码(1~4):" << endl;

//        cin >> t_input;

//        switch((errType)t_input)
//        {
//        case DEFAULT_TYPE:
//            throw DEFAULT_TYPE;
//            break;
//        case CALLER_DISCONNECT:
//            throw CALLER_DISCONNECT;
//            break;
//        case CALLED_DISCONNECT:
//            throw CALLED_DISCONNECT;
//            break;
//        case TIME_OUT:
//            throw TIME_OUT;
//            break;
//        default:
//            throw (errType)t_input;
//            break;
//        }
//    }
//    catch(errorType t_errType)
//    {
//        t_iter1 = t_map1.find(t_errType);

//        if(t_iter1 != t_map1.end())
//        {
//            cout << "断开原因 : " << t_iter1->second << endl;
//        }
//        else
//        {
//            cout << "没有该呼叫断开的原因码!" << endl;
//        }
//    }

    try
    {
        inputChoice();
    }
//    catch(Chinese t_chinese)
//    {
//        cout << "该工作不能为中国人!" << endl;

//    }
//    catch(Japanese t_Japanese)
//    {
//        cout << "该工作不能为日本人!" << endl;

//    }
//    catch(American t_American)
//    {
//        cout << "该工作不能为美国人!" << endl;
//    }
//    catch(English t_English)
//    {
//        cout << "该工作不能为英国人!" << endl;
//    }
    catch(person t_person)
    {
        cout << "该工作不能为人!" << endl;
    }
    catch(...)
    {
        cout << "捕获所有的异常!" << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}

