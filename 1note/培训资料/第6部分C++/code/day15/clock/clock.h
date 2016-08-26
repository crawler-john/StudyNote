#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QPainter>    //画家类
#include <QTime>       //时间类
#include <QTimer>      //定时器类
#include <QColor>
#include <QEvent>
#include <QDebug>
#include <qmath.h>
#include "mybutton.h"

#define pi 3.1415926

class clock : public QWidget
{
    Q_OBJECT
    
public:
    clock(QWidget *parent = 0);
    ~clock();

    //窗体重绘的响应函数
    virtual void paintEvent(QPaintEvent * event);

    virtual void changeEvent(QEvent * event);

private:

    myButton *m_moveBtn;

    qreal m_widthScale;    //窗体宽度的比例
    qreal m_heightScale;   //窗体高度的比例

    qreal m_normalWidth;
    qreal m_normalHeight;

    qreal m_maxWidth;
    qreal m_maxHeight;

signals:     //自定义信号

    //主窗体发生变化的信号
    void sendInfo(qreal t_widthScale,qreal t_heightScale);

};

#endif // CLOCK_H
