#include "myitem.h"

myItem::myItem(int t_x,int t_y,const QPixmap &pixmap, QGraphicsItem *parent)
    :QGraphicsPixmapItem(pixmap,parent),m_X(t_x),m_Y(t_y),m_mineNum(0)
{
}

void myItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "X : " << m_X << " Y : " << m_Y;

    switch(m_mineNum)
    {
    case -1:
        {
            this->setPixmap(QPixmap(":/images/mine.jpg"));
        }
        break;

    case 0:
        {
            this->setPixmap(QPixmap(":/images/question.jpg"));
        }
        break;


    case 1:
        {
            this->setPixmap(QPixmap(":/images/question.jpg"));
        }
        break;
    case 2:
        {
            this->setPixmap(QPixmap(":/images/question.jpg"));
        }
        break;
    case 3:
        {
            this->setPixmap(QPixmap(":/images/question.jpg"));
        }
        break;
    case 4:
        {
            this->setPixmap(QPixmap(":/images/question.jpg"));
        }
        break;
    case 5:
        {
            this->setPixmap(QPixmap(":/images/question.jpg"));
        }
        break;
    case 6:
        {
            this->setPixmap(QPixmap(":/images/question.jpg"));
        }
        break;
    case 7:
        {
            this->setPixmap(QPixmap(":/images/question.jpg"));
        }
        break;
    case 8:
        {
            this->setPixmap(QPixmap(":/images/question.jpg"));
        }
        break;

    }
}

void myItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}

void myItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
}



