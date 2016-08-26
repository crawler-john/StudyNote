#include "clock.h"

clock::clock(QWidget *parent)
    : QWidget(parent)
{
    //增加一个定时器
    QTimer *t_timer = new QTimer;
    t_timer->setInterval(1000);

    //启动定时器
    t_timer->start();

    //建立连接
    connect(t_timer,SIGNAL(timeout()),this,SLOT(update()));

    //增加一个按钮
    myButton *t_moveBtn = new myButton("move",this);

    //resize主窗体
    this->resize(500,400);

}

clock::~clock()
{
    
}

void clock::paintEvent(QPaintEvent *event)
{
    //qDebug() << "11111111111111";

    //声明一个画家的对象
    QPainter t_painter(this);

    //清除线条的锯齿
    t_painter.setRenderHint(QPainter::Antialiasing);

    //确定圆心
    QPoint t_point(0,0);

    //确定圆的半径
    int t_r = qMin(this->width()/2,this->height()/2);

    //平移坐标系
    t_painter.translate(this->width()/2,this->height()/2);

    //画时钟的边框
    t_painter.drawEllipse(t_point,t_r,t_r);

    //画时钟的刻度
    for(int i = 0; i < 60; i++)
    {

        if(i%5 == 0)
        {
            t_painter.drawLine(QPoint(0,-t_r),QPoint(0,-t_r+15));
        }
        else
        {
            t_painter.drawLine(QPoint(0,-t_r),QPoint(0,-t_r+6));
        }

        //旋转坐标系
        t_painter.rotate(6.0);
    }

    //画时钟整点的数字
    for(int i = 1; i < 13; i++)
    {
        t_painter.rotate(30.0);

        t_painter.drawText(-5,-t_r+30,QString::number(i));

//        t_painter.drawText((t_r-30)*qSin(pi*i/6),(-t_r+30)*qCos(pi*i/6),QString::number(i));

//        t_painter.save();

//        t_painter.rotate(i*30.0);
//        t_painter.translate(0,-t_r+30);
//        t_painter.rotate(-i*30.0);
//        t_painter.drawText(-5,0,QString::number(i));

//        t_painter.restore();
    }

    //获取当前的时间
    QTime t_currentTime = QTime::currentTime();

    qreal t_hourAngle = (t_currentTime.hour() + t_currentTime.minute()/60.0 + t_currentTime.second()/3600.0)*30.0;
    qreal t_minuteAngle = (t_currentTime.minute() + t_currentTime.second()/60.0)*6.0;
    qreal t_secondAngle = t_currentTime.second()*6.0;

    QPoint t_hourArray[3] = {QPoint(-5,5),QPoint(5,5),QPoint(0,-t_r/2)};
    QPoint t_minuteArray[3] = {QPoint(-5,5),QPoint(5,5),QPoint(0,-t_r*4/5)};
    QPoint t_secondArray[4] = {QPoint(-5,5),QPoint(0,30),QPoint(5,5),QPoint(0,-t_r+30)};


    //声明一个画笔
    QPen t_pen;
    t_pen.setWidth(3);
    //t_pen.setColor(QColor(Qt::red));

    //画时针
    t_painter.setPen(t_pen);
    t_painter.save();

    t_painter.rotate(t_hourAngle);
    //t_painter.drawLine(QPoint(0,0),QPoint(0,-t_r/2));
    t_painter.drawPolygon(t_hourArray,3);
    t_painter.restore();

    //画分针
    t_pen.setWidth(2);
    //t_pen.setColor(QColor(0,255,0));
    t_painter.setPen(t_pen);
    t_painter.save();

    t_painter.rotate(t_minuteAngle);
    //t_painter.drawLine(QPoint(0,0),QPoint(0,-t_r*4/5));
    t_painter.drawPolygon(t_minuteArray,3);
    t_painter.restore();

    //画秒针
    t_pen.setWidth(1);
    //t_pen.setColor(QColor(Qt::blue));
    t_painter.setPen(t_pen);
    t_painter.save();

    t_painter.rotate(t_secondAngle);
    //t_painter.drawLine(QPoint(0,30),QPoint(0,-t_r + 20));
    t_painter.drawPolygon(t_secondArray,4);
    t_painter.restore();



}
