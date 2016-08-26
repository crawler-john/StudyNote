#include <iostream>
#include "round.h"

using namespace std;

int main()
{
    //声明一个圆的对象
//    round t_round1;

//    //设置该圆的半径
//    t_round1.setR(10.0);

//    //获取该圆的半径
//    cout << "round1 r : " << t_round1.getR() << endl;

//    //圆的周长
//    cout << "round1 girth : " << t_round1.getGirth() << endl;

//    //圆的面积
//    cout << "round1 area : " << t_round1.getArea() << endl;

    //测试构造函数
    round t_round2;
    round t_round3(20.0);
    round t_round4(t_round3);

    t_round2 = t_round3;

    cout << "round2 r : " << t_round2.getR() << endl;
    cout << "round3 r : " << t_round3.getR() << endl;
    cout << "round4 r : " << t_round4.getR() << endl;






    cout << "Hello World!" << endl;
    return 0;
}

