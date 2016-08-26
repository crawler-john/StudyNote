#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main()
{
    //map容器存放的数据是一对数据(key,value)
    //map容器是有序的,并且是以key值的升序排列
    //map容器的key值是唯一的
    map<int,string> t_map1;

    cout << "map1 size : " << t_map1.size() << endl;

    pair<map<int,string>::iterator,bool> t_result;

    //第一种插入map数据的方法

    t_result = t_map1.insert(pair<int,string>(2,"hello"));

    if(t_result.second)
    {
        cout << "insert data into map1 success!" << endl;
        cout << "map1 size : " << t_map1.size() << endl;
        cout << "key : " << t_result.first->first << " and value : " << t_result.first->second << endl;
    }
    else
    {
        cout << "insert data into map1 failed!" << endl;
    }

    //第二种插入map数据的方法

    t_result = t_map1.insert(map<int,string>::value_type(1,"world"));

    if(t_result.second)
    {
        cout << "insert data into map1 success!" << endl;
        cout << "map1 size : " << t_map1.size() << endl;
        cout << "key : " << t_result.first->first << " and value : " << t_result.first->second << endl;
    }
    else
    {
        cout << "insert data into map1 failed!" << endl;
    }

    cout << "1111111111111111111111111111111" << endl;

    map<int,string>::iterator t_iter1;

    for(t_iter1 = t_map1.begin();t_iter1 != t_map1.end();t_iter1++)
    {
        cout << "map1 key : " << t_iter1->first << " and value : " << t_iter1->second << endl;
    }

    //第三种插入map数据的方法
    t_map1[-1] = "how are you!";
    t_map1[9] = "what is your name?";
    t_map1[3] = "good";
    t_map1[7] = "nice to meet you!";
    t_map1[5] = "Yes!";
    t_map1[6] = "Fine,thank you!";
    t_map1[4] = "OK";
    t_map1[-1] = "Yeah!";

    cout << "222222222222222222222222222222222" << endl;

    for(t_iter1 = t_map1.begin();t_iter1 != t_map1.end();t_iter1++)
    {
        cout << "map1 key : " << t_iter1->first << " and value : " << t_iter1->second << endl;
    }

    map<int,string> t_map2(t_map1);
    map<int,string> t_map3(t_map1.begin(),t_map1.end());
    map<int,string> t_map4;
    t_map4 = t_map1;

//    cout << "333333333333333333333333333333333" << endl;

//    for(t_iter1 = t_map2.begin();t_iter1 != t_map2.end();t_iter1++)
//    {
//        cout << "map2 key : " << t_iter1->first << " and value : " << t_iter1->second << endl;
//    }

//    for(t_iter1 = t_map3.begin();t_iter1 != t_map3.end();t_iter1++)
//    {
//        cout << "map3 key : " << t_iter1->first << " and value : " << t_iter1->second << endl;
//    }

//    for(t_iter1 = t_map4.begin();t_iter1 != t_map4.end();t_iter1++)
//    {
//        cout << "map4 key : " << t_iter1->first << " and value : " << t_iter1->second << endl;
//    }

    //count
    if(t_map1.count(6) == 1)
    {
        cout << "key 6 is in map1 " << endl;
    }
    else
    {
        cout << "key 6 is not in map1 " << endl;
    }

    //find
    map<int,string>::iterator t_iter2;

    t_iter2 = t_map1.find(6);

    if(t_iter2 != t_map1.end())
    {
        cout << "key : " << t_iter2->first << " and value : " << t_iter2->second << endl;
    }
    else
    {
        cout << "key is not in map1 " << endl;
    }

    //lower_bound

    cout << "test lower_bound" << endl;

    t_iter2 = t_map1.lower_bound(8);

    if(t_iter2 != t_map1.end())
    {
        cout << "lower_bound key : " << t_iter2->first << " and value : " << t_iter2->second << endl;
    }
    else
    {
        cout << "map1 end!" << endl;
    }

    //upper_bound
    cout << "test upper_bound" << endl;


    t_iter2 = t_map1.upper_bound(9);

    if(t_iter2 != t_map1.end())
    {
        cout << "upper_bound key : " << t_iter2->first << " and value : " << t_iter2->second << endl;
    }
    else
    {
        cout << "map1 end!" << endl;
    }
    cout << "test equal_range"  << endl;
    //equal_range
    pair<map<int,string>::iterator,map<int,string>::iterator> t_result2;

    t_result2 = t_map1.equal_range(10);

    if(t_result2.second != t_map1.end())
    {
        cout << "pos1 key : " << t_result2.first->first << " and value : " << t_result2.first->second << endl;
        cout << "pos2 key : " << t_result2.second->first << " and value : " << t_result2.second->second << endl;
    }
    else
    {
        if(t_result2.first != t_map1.end())
        {
            cout << "11111111111111111" << endl;
        }
        else
        {
            cout << "pos2 is end!" << endl;
        }

    }

    cout << "555555555555555555555555555555" << endl;

    //多重map,key值可以相同
    multimap<int,string> t_map5;

    t_map5.insert(pair<int,string>(10,"Lucy"));
    t_map5.insert(pair<int,string>(1,"Jim"));
    t_map5.insert(pair<int,string>(9,"Rose"));
    t_map5.insert(pair<int,string>(1,"Kate"));
    t_map5.insert(pair<int,string>(8,"John"));
    t_map5.insert(pair<int,string>(2,"Jack"));
    t_map5.insert(pair<int,string>(7,"Mack"));
    t_map5.insert(pair<int,string>(2,"Jack"));
    t_map5.insert(pair<int,string>(6,"Will"));
    t_map5.insert(pair<int,string>(5,"Lily"));

    multimap<int,string>::iterator t_iter3;

    for(t_iter3 = t_map5.begin();t_iter3 != t_map5.end();t_iter3++)
    {
        cout << "map5 key : " << t_iter3->first << " and value : " << t_iter3->second << endl;
    }

    cout << "66666666666666666666666666666666" << endl;

    //set容器是有序的,并且是以升序排列,里面存放的数据是唯一的
    set<int> t_set1;
    set<int>::iterator t_iter4;

    t_set1.insert(10);
    t_set1.insert(5);
    t_set1.insert(2);
    t_set1.insert(5);
    t_set1.insert(7);
    t_set1.insert(2);
    t_set1.insert(1);
    t_set1.insert(3);
    t_set1.insert(5);
    t_set1.insert(1);

    cout << "set1 size : " << t_set1.size() << endl;

    for(t_iter4 = t_set1.begin();t_iter4 != t_set1.end();t_iter4++)
    {
        cout << *t_iter4 << " ";
    }

    cout << endl;


    cout << "Hello World!" << endl;
    return 0;
}

