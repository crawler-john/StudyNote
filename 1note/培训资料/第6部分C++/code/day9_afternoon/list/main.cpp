#include <iostream>
#include <list>

using namespace std;

bool fun1(int t_x)
{
    return t_x%2 == 0;
}

bool fun2(int t_x)
{
    return t_x > 5;
}

bool fun3(int t_x,int t_y)
{
    return t_x > t_y;
}

bool fun4(int t_x,int t_y)
{
    return t_x < t_y;
}

int main()
{
    int t_array1[10] = {8,2,1,10,5,9,7,3,6,4};

    list<int> t_list1;
    list<int> t_list2(5,9);
    list<int> t_list3(t_array1,t_array1+5);
    list<int> t_list4(t_list2);
    list<int> t_list5;

    t_list5 = t_list3;

    //size
    cout << "list1 size : " << t_list1.size() << endl;
    cout << "list2 size : " << t_list2.size() << endl;
    cout << "list3 size : " << t_list3.size() << endl;
    cout << "list4 size : " << t_list4.size() << endl;
    cout << "list5 size : " << t_list5.size() << endl;

    list<int>::iterator t_iter1;

    for(t_iter1 = t_list3.begin();t_iter1 != t_list3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //front,back
    cout << "list3 first : " << t_list3.front() << endl;
    cout << "list3 last : " << t_list3.back() << endl;

    //insert
    t_list3.insert(t_list3.begin(),100);


    list<int>::iterator t_iter2 = t_list3.begin();
    t_iter2++;
    t_iter2++;

    t_list3.insert(t_iter2,2,99);
    t_list3.insert(t_list3.end(),t_array1+5,t_array1+10);
    t_list3.insert(t_list3.end(),99);

    for(t_iter1 = t_list3.begin();t_iter1 != t_list3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //erase
    t_list3.erase(t_list3.begin());
    //t_list3.erase(t_list3.begin(),t_list3.end());

    for(t_iter1 = t_list3.begin();t_iter1 != t_list3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;
    cout << "88888888888888888888888888"<<endl;
    //remove  remove_if
    t_list3.remove(99);    // 移除链表中的所有99

    for(t_iter1 = t_list3.begin();t_iter1 != t_list3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

//    t_list3.remove_if(fun2);  //根据函数移除相应的数据

    for(t_iter1 = t_list3.begin();t_iter1 != t_list3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //reverse   //翻转链表
    t_list3.reverse();

    for(t_iter1 = t_list3.begin();t_iter1 != t_list3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;


    //sort
    //t_list3.sort();   //排序
    //t_list3.sort(fun3);   //根据函数排序

    for(t_iter1 = t_list3.begin();t_iter1 != t_list3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //push_front,push_back,pop_front,pop_back
    t_list1.push_back(1);
    t_list1.push_front(2);
    t_list1.push_back(3);
    t_list1.push_front(4);
    t_list1.push_back(5);
    t_list1.push_front(6);

    t_list1.pop_back();
    t_list1.pop_front();

    for(t_iter1 = t_list1.begin();t_iter1 != t_list1.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //
    t_list1.insert(t_list1.begin(),2,88);
    t_list1.insert(t_list1.end(),3,88);
    t_list1.insert(t_list1.end(),4,99);

    for(t_iter1 = t_list1.begin();t_iter1 != t_list1.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout <<endl <<  "99999999999999999999999999999999999" << endl;

    //unique    //将连续相同的数据弄成一个

    t_list1.unique();

    for(t_iter1 = t_list1.begin();t_iter1 != t_list1.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    for(t_iter1 = t_list3.begin();t_iter1 != t_list3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;
    cout << "555555555555555555555555" <<endl;

    for(t_iter1 = t_list1.begin();t_iter1 != t_list1.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;
    //splice        //链表连接
    t_list1.splice(t_list1.begin(),t_list3);
    //t_list1.splice(t_list1.begin(),t_list3,t_list3.begin());
    //t_list1.splice(t_list1.begin(),t_list3,t_list3.begin(),t_list3.end());

    for(t_iter1 = t_list1.begin();t_iter1 != t_list1.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    for(t_iter1 = t_list3.begin();t_iter1 != t_list3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //merge
    t_list1.sort(fun3);
    t_list3.sort(fun3);

    for(t_iter1 = t_list1.begin();t_iter1 != t_list1.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    for(t_iter1 = t_list3.begin();t_iter1 != t_list3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    t_list3.merge(t_list1,fun3);

    for(t_iter1 = t_list1.begin();t_iter1 != t_list1.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    for(t_iter1 = t_list3.begin();t_iter1 != t_list3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;






    cout << "Hello World!" << endl;
    return 0;
}

