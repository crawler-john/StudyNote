#include <iostream>
#include "classmate.h"

using namespace std;

int main()
{
    //声明一个同学的对象
//    classmate t_classmate1;

//    //设置同学1的信息
//    t_classmate1.setInfo("Will","001","1992-10-5");

//    //输出同学1的信息
//    t_classmate1.print();

//    //再次设置同学1的信息(从键盘输入修改信息)
//    t_classmate1.setInfo();

//    //打印同学1的信息
//    t_classmate1.print();

    //测试构造函数
    classmate t_classmate2;
    classmate t_classmate3("Mack","002","2000-1-1");
    classmate t_classmate4(t_classmate3);

    t_classmate2 = t_classmate3;

    t_classmate2.print();
    t_classmate3.print();
    t_classmate4.print();


    cout << "Hello World!" << endl;
    return 0;
}

