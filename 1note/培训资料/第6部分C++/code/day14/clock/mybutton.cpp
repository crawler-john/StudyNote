#include "mybutton.h"

myButton::myButton(const QString &text, QWidget *parent)
    :QPushButton(text,parent),m_mouseType(0)
{
}

void myButton::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "key Press!";
}

void myButton::keyReleaseEvent(QKeyEvent *e)
{
    qDebug() << "key Release!";
}

void myButton::mouseMoveEvent(QMouseEvent *e)
{
    //qDebug() << "mouse Move!";

    if(m_mouseType == 1)
    {
        qDebug() << "鼠标左键点击按钮并移动!";

        m_lastPos = e->pos();

        int t_xDistance = m_lastPos.x() - m_beginPos.x();
        int t_yDistance = m_lastPos.y() - m_beginPos.y();

        this->move(this->x() + t_xDistance,this->y() + t_yDistance);
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




