#include <iostream>
#include "complex.h"

using namespace std;

int main()
{
//    //测试构造函数
//    complex t_complex1;
//    complex t_complex2(5,5);
//    complex t_complex3(t_complex2);
//    complex t_complex4;

//    t_complex4 = t_complex2;

//    //测试输出操作符<<
//    cout << "complex1 : " << t_complex1 << endl;
//    cout << "complex2 : " << t_complex2 << endl;
//    cout << "complex3 : " << t_complex3 << endl;
//    cout << "complex4 : " << t_complex4 << endl;

//    //测试+=
//    cout << "+===============================" << endl;
//    complex t_complex5(3,3);

//    t_complex5 += t_complex2 += t_complex3;

//    cout << "complex2 : " << t_complex2 << endl;
//    cout << "complex5 : " << t_complex5 << endl;

//    //测试-=
//    cout << "-===============================" << endl;
//    t_complex5 -= t_complex2 -= t_complex3;

//    cout << "complex2 : " << t_complex2 << endl;
//    cout << "complex5 : " << t_complex5 << endl;

//    //测试+
//    cout << "+++++++++++++++++++++++++++++++++" << endl;
//    complex t_complex6(1,2);

//    t_complex6 = t_complex2 + t_complex3 + t_complex4;

//    cout << "complex6 : " << t_complex6 << endl;

//    //测试-
//    cout << "----------------------------------" << endl;

//    t_complex6 = t_complex6 - t_complex2 - t_complex3;

//    cout << "complex6 : " << t_complex6 << endl;

//    //测试==和!=

//    cout << "=================!!!!!!============" << endl;

//    complex t_complex7(4.00000008,3.000000009);
//    complex t_complex8(4.00000009,3.000000007);

//    if(t_complex7 == t_complex8)
//    {
//        cout << "t_complex7 == t_complex8" << endl;
//    }
//    else
//    {
//        cout << "t_complex7 != t_complex8" << endl;
//    }

//    //测试输入操作符>>
//    complex t_complex9(2,2);

//    cin >> t_complex9;

//    cout << "t_complex9 : " << t_complex9 << endl;





    complex t_complex1(1,2);
    complex t_complex2(2,5);
    complex t_complex3;

    cout << "11111111111111111111111111111" << endl;
    t_complex1.print();
    t_complex2.print();


    t_complex3 = t_complex1 + t_complex2;

    t_complex3.print();





    cout << "Hello World!" << endl;
    return 0;
}

