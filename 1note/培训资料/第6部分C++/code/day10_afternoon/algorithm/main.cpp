#include <iostream>
#include <algorithm>   //算法的头文件
#include <numeric>
#include <vector>

using namespace std;

bool fun1(int t_x)
{
    return t_x%2 == 0;
}

bool fun2(int t_x,int t_y)
{
    return t_x > t_y;
}

bool fun3(int t_x)
{
    return t_x < 5;
}

void fun4(int &t_x)
{
    t_x += 100;
}

int main()
{
    int t_array1[10] = {2,3,11,4,9,10,8,6,7,1};
    int t_array2[10] = {6,9,7,8,8,8,4,5,10,9};
    int t_array3[10] = {10,30,20,1,3,2,9,30,20,1};
    int t_array4[3] = {30,20,1};

    vector<int> t_vec1(t_array1,t_array1+10);
    vector<int> t_vec2(t_array2,t_array2+10);
    vector<int> t_vec3(t_array3,t_array3+10);
    vector<int> t_vec4;
    vector<int> t_vec5;


    vector<int>::iterator t_iter1;

    //accumulate 求和
    cout << "vec1 sum : " << accumulate(t_vec1.begin(),t_vec1.end(),10) << endl;

    //count count_if
    cout << "8 numbers in vec2 : " << count(t_vec2.begin(),t_vec2.end(),8) << endl;
    cout << " numbers : " << count_if(t_vec2.begin(),t_vec2.end(),fun1) << endl;

    //sort
    sort(t_vec1.begin(),t_vec1.begin()+5);
    sort(t_vec1.begin()+5,t_vec1.end(),fun2);

    for(t_iter1 = t_vec1.begin();t_iter1 != t_vec1.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //find  find_if find_first_of find_end
    // {6,9,7,8,8,8,4,5,10,9};
    cout << "distance vec2 begin : " << find(t_vec2.begin(),t_vec2.end(),9) - t_vec2.begin() << endl;
    cout << "<5 distance vec2 begin : " << find_if(t_vec2.begin(),t_vec2.end(),fun3) - t_vec2.begin() << endl;
    cout << "3distance vec2 begin : " << find_first_of(t_vec3.begin(),t_vec3.end(),t_array4,t_array4+3) - t_vec3.begin() << endl;
    cout << "4distance vec2 begin : " << find_end(t_vec3.begin(),t_vec3.end(),t_array4,t_array4+3) - t_vec3.begin() << endl;

    //search search_n
    cout << "5distance vec2 begin : " << search(t_vec3.begin(),t_vec3.end(),t_array4,t_array4+3) - t_vec3.begin() << endl;
    cout << "6distance vec2 begin : " << search_n(t_vec2.begin(),t_vec2.end(),2,8) - t_vec2.begin() << endl;

    //copy copy_backward
    cout << "copy111111111111111111111111111" <<endl;
    t_vec4.resize(5);

//   copy(t_vec1.begin(),t_vec1.begin()+5,t_vec4.begin());
   copy_backward(t_vec1.begin(),t_vec1.begin()+5,t_vec4.end()/*-1*/);

    for(t_iter1 = t_vec4.begin();t_iter1 != t_vec4.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //replace replace_if replace_copy
    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    replace(t_vec3.begin(),t_vec3.end(),30,300);

    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    replace_if(t_vec3.begin(),t_vec3.end(),fun1,2);

    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    cout << "replace_copy22222222222222222222222222222222222222" << endl;

    t_vec5.resize(10);
    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    for(t_iter1 = t_vec5.begin();t_iter1 != t_vec5.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    cout << endl;

    replace_copy(t_vec3.begin(),t_vec3.end(),t_vec5.begin(),2,99);

    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    for(t_iter1 = t_vec5.begin();t_iter1 != t_vec5.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    replace_copy_if(t_vec3.begin(),t_vec3.end(),t_vec5.begin(),fun3,0);

    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    for(t_iter1 = t_vec5.begin();t_iter1 != t_vec5.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;

    //for_each
    cout << "test for_each" << endl;
    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;
    for_each(t_vec3.begin(),t_vec3.end(),fun4);

    for(t_iter1 = t_vec3.begin();t_iter1 != t_vec3.end(); t_iter1++)
    {
        cout << *t_iter1 << " ";
    }

    cout << endl;


    cout << "Hello World!" << endl;
    return 0;
}

