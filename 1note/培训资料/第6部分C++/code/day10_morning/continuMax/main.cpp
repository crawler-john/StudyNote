#include <iostream>
#include <string>
#include <string.h>
#include <map>

using namespace std;


int continuMax(char *&t_outputStr,char *t_inputStr)
{
    //获取字符串的长度
    int t_strLength = strlen(t_inputStr);

    //key值是数字串的长度,value值是该数字串距离开始位置的长度
    multimap<int,int> t_map1;
    //multimap<int,string> t_map2;

    //遍历字符串
    for(int i = 0; i < t_strLength; i++)
    {
        //数字串的长度(开始默认为0)
        int t_length = 0;
        //string t_str;

        while(t_inputStr[i] >= '0' && t_inputStr[i] <= '9')
        {
            //t_str += t_inputStr[i];
            t_length++;
            i++;

        }

        //如果连续的数字串的长度大于0,则将信息插入到map中
        if(t_length > 0)
        {
            t_map1.insert(pair<int,int>(t_length,i - t_length));
            //t_map2.insert(pair<int,string>(t_length,t_str));
        }
    }

    //打印map容器中的信息
    //multimap<int,int>::iterator t_iter1;
    //multimap<int,string>::iterator t_iter2;

//    for(t_iter1 = t_map1.begin();t_iter1 != t_map1.end();t_iter1++)
//    {
//        cout << "map1 key : " << t_iter1->first << " and value : " << t_iter1->second << endl;
//    }

//    for(t_iter2 = t_map2.begin();t_iter2 != t_map2.end();t_iter2++)
//    {
//        cout << "map2 key : " << t_iter2->first << " and value : " << t_iter2->second << endl;
//    }

    //获取最长数字串的位置
    t_outputStr = t_inputStr + t_map1.rbegin()->second;

    //返回最长数字串的长度
    return t_map1.rbegin()->first;
}


int main()
{
    char *t_inStr = "1abc12345678901234d123459777777777777efg98778988888888888888811111111112222222222222,&&7645645888$#!12345675645648991111111111111  ";

    char *t_outStr;

    int t_lenght = continuMax(t_outStr,t_inStr);

    for(int i = 0; i < t_lenght;i++)
    {
        cout << t_outStr[i];
    }

    cout << endl;


    cout << "Hello World!" << endl;
    return 0;
}

