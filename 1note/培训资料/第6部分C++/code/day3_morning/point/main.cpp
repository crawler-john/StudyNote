#include <iostream>
#include "point.h"

using namespace std;

int main()
{
    //测试构造函数
    point t_point1;
    point t_point2(2,3);
    point t_point3(t_point2);

    t_point1 = t_point2;

    //打印信息
    t_point1.print();
    t_point2.print();
    t_point3.print();

    //移动点
    t_point1.move(-1.5,-2.5);
    t_point2.move(1,3);

    //打印信息
    t_point1.print();
    t_point2.print();

    cout << "Hello World!" << endl;
    return 0;
}

