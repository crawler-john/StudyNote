#ifndef BED_H
#define BED_H

#include "furniture.h"

//床类(继承家具类)
class Bed : virtual public Furniture
{
public:
    Bed()
    {
        cout << "Bed()" << endl;
        m_name = "Bed";
    }

    ~Bed()
    {
        cout << "~Bed()" << endl;
    }

    //床可以睡觉
    void Sleep()
    {
        cout << m_name << " can sleep!" << endl;
    }

protected:

private:
};

#endif // BED_H
