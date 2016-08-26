#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int t_array1[10] = {8,2,1,10,5,9,7,3,6,4};


    //声明vector的方式
    vector<int> t_vec1;
    vector<int> t_vec2(5,8);
    vector<int> t_vec3(t_array1,t_array1+5);
    vector<int> t_vec4(t_vec3);         //调用拷贝构造函数
    vector<int> t_vec5;

    t_vec5 = t_vec2;

    //size  vector对象的大小
    cout << "vec1 size : " << t_vec1.size() << endl;
    cout << "vec2 size : " << t_vec2.size() << endl;
    cout << "vec3 size : " << t_vec3.size() << endl;
    cout << "vec4 size : " << t_vec4.size() << endl;
    cout << "vec5 size : " << t_vec5.size() << endl;

    //capacity  vector对象的存储大小
    cout << "vec1 capacity : " << t_vec1.capacity() << endl;
    cout << "vec2 capacity : " << t_vec2.capacity() << endl;
    cout << "vec3 capacity : " << t_vec3.capacity() << endl;
    cout << "vec4 capacity : " << t_vec4.capacity() << endl;
    cout << "vec5 capacity : " << t_vec5.capacity() << endl;

    for(int i = 0; i < t_vec3.size(); i++)
    {
        cout << t_vec3[i] << " ";
    }

    cout << endl;

    //用迭代器遍历容器
    vector<int>::iterator t_iter1;   //随机迭代器
    vector<int>::const_iterator t_iter2;  //const迭代器
    vector<int>::reverse_iterator t_iter3; //反向迭代器

    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end();t_iter1++)
    {
        //*t_iter1 = 10;
        cout << *t_iter1 << " ";
    }

    cout << endl;

//    for(t_iter2 = t_vec3.begin();t_iter2 != t_vec3.end();t_iter2++)
//    {
//        *t_iter2 = 20;
//        cout << *t_iter2 << " ";
//    }

//    cout << endl;

    for(t_iter1 = t_vec3.end() -1; t_iter1 != t_vec3.begin() - 1;t_iter1--)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    for(t_iter3 = t_vec3.rbegin();t_iter3 != t_vec3.rend();t_iter3++)
    {
        cout << *t_iter3 << " ";
    }

    cout << endl;

    //front,back
    cout << "vec3 front : " << t_vec3.front() << endl;
    cout << "vec3 back : " << t_vec3.back() << endl;

    //insert
    t_vec3.insert(t_vec3.begin(),100);
    t_vec3.insert(t_vec3.end(),2,99);
    t_vec3.insert(t_vec3.begin(),t_array1+5,t_array1+10);

    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //erase
    t_vec3.erase(t_vec3.begin());
    t_vec3.erase(t_vec3.begin(),t_vec3.begin()+5);

    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //cout << "vec3 size : " << t_vec3.size() << endl;

    //clear,empty
    //t_vec3.clear();

    if(t_vec3.empty())
    {
        cout << "vec3 is empty!" << endl;
    }
    else
    {
        cout << "vec3 is not empty!" << endl;
    }

    //push_back,pop_back
    t_vec1.push_back(1);
    t_vec1.push_back(2);
    t_vec1.push_back(3);
    t_vec1.push_back(4);
    t_vec1.push_back(5);

    t_vec1.pop_back();

    for(t_iter1 = t_vec1.begin();t_iter1 != t_vec1.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //resize
    cout << "vec1 size : " << t_vec1.size() << endl;

    //t_vec1.resize(10,8);
    t_vec1.resize(2);

    cout << "vec1 size : " << t_vec1.size() << endl;

    for(t_iter1 = t_vec1.begin();t_iter1 != t_vec1.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //reserve
    cout << "vec3 size : " << t_vec3.size() << endl;
    cout << "vec3 capacity : " << t_vec3.capacity() << endl;

    t_vec3.reserve(20);

    cout << "vec3 capacity : " << t_vec3.capacity() << endl;

    //swap

    for(t_iter1 = t_vec1.begin();t_iter1 != t_vec1.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    t_vec1.swap(t_vec3);
    t_vec3.swap(t_vec1);

    for(t_iter1 = t_vec1.begin();t_iter1 != t_vec1.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //assign
    t_vec1.assign(t_array1,t_array1+5);
    t_vec1.assign(6,9);

    for(t_iter1 = t_vec1.begin();t_iter1 != t_vec1.end();t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;




    cout << "Hello World!" << endl;
    return 0;
}

