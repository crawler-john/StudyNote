#include <iostream>
#include "furniture.h"
#include "bed.h"
#include "sofa.h"
#include "SleeperSofa.h"

using namespace std;

int main()
{
    cout << "00000000000000" << endl;

    Bed t_bed1;

    t_bed1.setWeight(100);
    cout << "bed1 weight : " << t_bed1.getWeight() << endl;
    t_bed1.Sleep();

    cout << "1111111111111111" << endl;

    Sofa t_sofa1;

    t_sofa1.setWeight(200);
    cout << "sofa1 weight : " << t_sofa1.getWeight() << endl;
    t_sofa1.watchTV();

    cout << "2222222222222222" << endl;

    SleeperSofa t_sleeperSofa1;

    t_sleeperSofa1.setWeight(300);

    cout << "sleeperSofa1 weight : " << t_sleeperSofa1.getWeight() << endl;

    t_sleeperSofa1.Sleep();
    t_sleeperSofa1.watchTV();
    t_sleeperSofa1.foldOut();

//    cout << "333333333" << endl;

//    cout << "1 : " << t_bed1.getName() << endl;
//    cout << "2 : " << t_sofa1.getName() << endl;
//    cout << "3 : " << t_sleeperSofa1.getName() << endl;

    cout << "Hello World!" << endl;
    return 0;
}

