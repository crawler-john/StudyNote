#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPoint>
#include <QWidget>
#include <QDebug>

class myButton : public QPushButton
{
    Q_OBJECT
public:

    myButton(const QString & text, QWidget * parent = 0);

    virtual void keyPressEvent(QKeyEvent * e);

    virtual void keyReleaseEvent(QKeyEvent * e);

    virtual void mouseMoveEvent(QMouseEvent * e);

    virtual void mousePressEvent(QMouseEvent * e);

    virtual void mouseReleaseEvent(QMouseEvent * e);

private:

    int m_mouseType;    //1.鼠标左键 2.鼠标中键 3.鼠标右键
    QPoint m_beginPos;  //鼠标点击按钮开始的位置
    QPoint m_lastPos;   //按钮移动后,鼠标点击按钮的位置
    QWidget *m_parent;  //父窗体的指针
    qreal m_parentWidth;  //父窗体的宽度
    qreal m_parentHeight; //父窗体的高度
    
signals:
    
public slots:

    void recvInfo(qreal t_widthScale,qreal t_heightScale);
    
};

#endif // MYBUTTON_H
