#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <vector>
#include "myitem.h"

using namespace std;

class myScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit myScene(QObject *parent = 0);

    vector< vector<myItem*> > m_itemVec;
    
signals:
    
public slots:
    
};

#endif // MYSCENE_H
