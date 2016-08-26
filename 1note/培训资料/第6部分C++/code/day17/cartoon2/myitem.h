#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsPixmapItem>
#include <QDebug>

class myItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    myItem(int t_x,int t_y,const QPixmap & pixmap, QGraphicsItem * parent = 0);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

    int m_mineNum; // -1:为雷,0~8();

private:

    int m_X;     //行数
    int m_Y;     //列数


    
signals:
    
public slots:
    
};

#endif // MYITEM_H
