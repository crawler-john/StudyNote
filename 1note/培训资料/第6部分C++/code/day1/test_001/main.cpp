#include <iostream>    //标准输入输出流

using namespace std;

//using std::cout;
//using std::endl;

//int g_studentNum;

//void getStudentInfo(int t_studentAge)
//{

//}

//struct Person
//{
//    int m_age;
//    int m_weight;
//};

int main(int argc,char *argv[])
{
//    int t_studentNumber;

    for(int i = 0; i < argc; i++)
    {
        cout << argv[i] << endl;
    }


    cout << "Hello World!" << endl;


    return 0;
}

