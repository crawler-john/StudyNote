#ifndef SLEEPERSOFA_H
#define SLEEPERSOFA_H

#include "bed.h"
#include "sofa.h"

//沙发床类(多重继承床类和沙发类)
class SleeperSofa : public Bed,public Sofa
{
public:
    SleeperSofa()
    {
        cout << "SleeperSofa()" << endl;
        m_name = "SleeperSofa";
    }

    ~SleeperSofa()
    {
        cout << "~SleeperSofa()" << endl;
    }

    //沙发床可以折叠
    void foldOut()
    {
        cout << m_name << " can fold out!" << endl;
    }

protected:

private:
};

#endif // SLEEPERSOFA_H
