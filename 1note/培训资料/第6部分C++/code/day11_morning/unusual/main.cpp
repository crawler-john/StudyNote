#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include "person.h"

using namespace std;


//try�����зŽ����ܷ����쳣�Ĵ���
//throw�׳��쳣
//catch�����쳣

void inputChoice()
{
    while(1)
    {
        cout << "�������û���ѡ��(1~5):" << endl;
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
            cout << "û�и��û�ѡ��,����������!" << endl;
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
//            //���ļ�ָ���ƶ����ļ�β
//            fseek(fp,0,SEEK_END);

//            //��ȡ�ļ��Ĵ�С
//            int t_fileSize = ftell(fp);

//            //����һ������
//            char t_fileData[t_fileSize + 1];

//            memset(t_fileData,0,t_fileSize+1);

//            //���ļ�ָ���ƶ����ļ�ͷ
//            fseek(fp,0,SEEK_SET);

//            fread(t_fileData,1,t_fileSize,fp);

//            fclose(fp);

//            cout << "file data : " << t_fileData << endl;

//        }

//        cout << "1111111111111111111111111" << endl;
//    }
//    //catch�е��β�ֻ����һ��
////    catch(string t_fileName)
////    {
////        cout << "open file : " << t_fileName << " failed!" << endl;
////    }
////    catch(string &t_fileName)
////    {
////        cout << "2open file : " << t_fileName << " failed!" << endl;
////    }
//    //��û��catch�����쳣ʱ,ϵͳ�Զ�����abort()���������ý���
//    catch(int t_a)
//    {
//        cout << "222222222222222222" << endl;
//    }
//    //�������е��쳣
//    catch(...)
//    {
//        cout << "�������е��쳣!" << endl;
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
//        cout << "��������Ϊ : " << t_a << endl;
//    }
//    catch(char t_a)
//    {
//        cout << "�ַ�����Ϊ��!" << endl;
//    }
//    catch(char *t_p1)
//    {
//        cout << "ָ�벻��ΪNULL!" << endl;
//    }
//    catch(person &t_person)
//    {
//        cout << "�˵����䲻��Ϊ : " << t_person.getAge() << endl;
//    }

//    map<errType,string> t_map1;
//    map<errType,string>::iterator t_iter1;

//    t_map1.insert(pair<errType,string>(DEFAULT_TYPE,"Ĭ������"));
//    t_map1.insert(pair<errType,string>(CALLER_DISCONNECT,"���жϿ�"));
//    t_map1.insert(pair<errType,string>(CALLED_DISCONNECT,"���жϿ�"));
//    t_map1.insert(pair<errType,string>(TIME_OUT,"��ʱ"));

//    for(t_iter1 = t_map1.begin();t_iter1 != t_map1.end();t_iter1++)
//    {
//        cout << "map1 key : " << t_iter1->first << " and value : " << t_iter1->second << endl;
//    }

//    try
//    {
//        int t_input;

//        cout << "��������жϿ���ԭ����(1~4):" << endl;

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
//            cout << "�Ͽ�ԭ�� : " << t_iter1->second << endl;
//        }
//        else
//        {
//            cout << "û�иú��жϿ���ԭ����!" << endl;
//        }
//    }

    try
    {
        inputChoice();
    }
//    catch(Chinese t_chinese)
//    {
//        cout << "�ù�������Ϊ�й���!" << endl;

//    }
//    catch(Japanese t_Japanese)
//    {
//        cout << "�ù�������Ϊ�ձ���!" << endl;

//    }
//    catch(American t_American)
//    {
//        cout << "�ù�������Ϊ������!" << endl;
//    }
//    catch(English t_English)
//    {
//        cout << "�ù�������ΪӢ����!" << endl;
//    }
    catch(person t_person)
    {
        cout << "�ù�������Ϊ��!" << endl;
    }
    catch(...)
    {
        cout << "�������е��쳣!" << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}

