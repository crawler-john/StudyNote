#ifndef SOFA_H
#define SOFA_H

#include "furniture.h"

//沙发类(继承家具类)
class Sofa : virtual public Furniture
{
public:
    Sofa()
    {
        cout << "Sofa()" << endl;
        m_name = "Sofa";
    }

    ~Sofa()
    {
        cout << "~Sofa()" << endl;
    }

    //可以看电视
    void watchTV()
    {
        cout << m_name << " can watch TV!" << endl;
    }

protected:

private:
};

#endif // SOFA_H
