#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QPainter>    //画家类
#include <QTime>       //时间类
#include <QTimer>      //定时器类
#include <QColor>
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
};

#endif // CLOCK_H
