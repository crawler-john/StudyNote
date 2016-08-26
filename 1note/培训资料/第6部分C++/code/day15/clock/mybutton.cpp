#include "mybutton.h"
#include "clock.h"

myButton::myButton(const QString &text, QWidget *parent)
    :QPushButton(text,parent),m_mouseType(0)
{
    //m_parent = parent;

    m_parent = this->parentWidget();

    m_parentWidth = m_parent->width();
    m_parentHeight = m_parent->height();

    qDebug() << "parent Width" << m_parentWidth << " height : " << m_parentHeight;

}

void myButton::keyPressEvent(QKeyEvent *e)
{
    //qDebug() << "key Press!";

    m_parentWidth = m_parent->width();
    m_parentHeight = m_parent->height();

    if(e->key() == Qt::Key_Left)
    {
        qDebug() << "按压方向左键!";

        if(this->x() < 0)
        {
            this->move(this->x()+2,this->y());
        }
        else
        {
            this->move(this->x()-4,this->y());
        }

    }
    else if(e->key() == Qt::Key_Right)
    {
        qDebug() << "按压方向右键!";

        if(this->x() > m_parentWidth - this->width())
        {
            this->move(this->x()-2,this->y());
        }
        else
        {
            this->move(this->x()+4,this->y());
        }
    }
    else if(e->key() == Qt::Key_Up)
    {
        qDebug() << "按压方向上键!";

        if(this->y() < 0)
        {
            this->move(this->x(),this->y()+2);
        }
        else
        {
            this->move(this->x(),this->y()-4);
        }
    }
    else if(e->key() == Qt::Key_Down)
    {
        qDebug() << "按压方向下键!";

        if(this->y() > m_parentHeight - this->height())
        {
            this->move(this->x(),this->y()-2);
        }
        else
        {
            this->move(this->x(),this->y()+4);
        }
    }

}

void myButton::keyReleaseEvent(QKeyEvent *e)
{
    //qDebug() << "key Release!";

    if(e->key() == Qt::Key_Left)
    {
        qDebug() << "释放方向左键!";
    }
    else if(e->key() == Qt::Key_Right)
    {
        qDebug() << "释放方向右键!";
    }
    else if(e->key() == Qt::Key_Up)
    {
        qDebug() << "释放方向上键!";
    }
    else if(e->key() == Qt::Key_Down)
    {
        qDebug() << "释放方向下键!";
    }
}

void myButton::mouseMoveEvent(QMouseEvent *e)
{
    //qDebug() << "mouse Move!";

    m_parentWidth = m_parent->width();
    m_parentHeight = m_parent->height();

    if(m_mouseType == 1)
    {
        qDebug() << "鼠标左键点击按钮并移动!";

        m_lastPos = e->pos();

        int t_xDistance = m_lastPos.x() - m_beginPos.x();
        int t_yDistance = m_lastPos.y() - m_beginPos.y();

        this->move(this->x() + t_xDistance,this->y() + t_yDistance);

        if(this->x() < 0)
        {
            this->move(0,this->y());
        }

        if(this->x() > m_parentWidth - this->width())
        {
            this->move(m_parentWidth - this->width(),this->y());
        }

        if(this->y() < 0)
        {
            this->move(this->x(),0);
        }

        if(this->y() > m_parentHeight - this->height())
        {
            this->move(this->x(),m_parentHeight - this->height());
        }
    }
    else if(m_mouseType == 2)
    {
        qDebug() << "鼠标中键点击按钮并移动!";
    }
    else if(m_mouseType == 3)
    {
        qDebug() << "鼠标右键点击按钮并移动!";
    }
}

void myButton::mousePressEvent(QMouseEvent *e)
{
    //qDebug() << "mouse Press!";

    if(e->button() == Qt::LeftButton)
    {
        qDebug() << "鼠标左键点击按钮按压!";
        m_mouseType = 1;

        m_beginPos = e->pos();

        //qDebug() << "begin pos x : " << m_beginPos.x() << " y : " << m_beginPos.y();

    }
    else if(e->button() == Qt::MiddleButton)
    {
        qDebug() << "鼠标中键点击按钮按压!";
        m_mouseType = 2;
    }
    else if(e->button() == Qt::RightButton)
    {
        qDebug() << "鼠标右键点击按钮按压!";
        m_mouseType = 3;
    }
}

void myButton::mouseReleaseEvent(QMouseEvent *e)
{
    //qDebug() << "mouse Release!";

    if(e->button() == Qt::LeftButton)
    {
        qDebug() << "鼠标左键点击按钮释放!";
    }
    else if(e->button() == Qt::MiddleButton)
    {
        qDebug() << "鼠标中键点击按钮释放!";
    }
    else if(e->button() == Qt::RightButton)
    {
        qDebug() << "鼠标右键点击按钮释放!";
    }
}


void myButton::recvInfo(qreal t_widthScale, qreal t_heightScale)
{
    qDebug() << "888888888888888888888888";

    this->move(this->x()*t_widthScale,this->y()*t_heightScale);

//    this->setFixedSize(this->width()*t_widthScale,this->height()*t_heightScale);
}





