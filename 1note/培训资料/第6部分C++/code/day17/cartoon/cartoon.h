#ifndef CARTOON_H
#define CARTOON_H

#include <QMainWindow>
#include <QGraphicsView>        //镜头类
#include <QGraphicsScene>       //舞台类
#include <QGraphicsPixmapItem>  //道具类
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>

class cartoon : public QMainWindow
{
    Q_OBJECT
    
public:
    cartoon(QWidget *parent = 0);
    ~cartoon();

private:

    QMenu *m_gameMenu;
    QMenu *m_helpMenu;

    QAction *m_rorateImgAct1;     //旋转图片一
    QAction *m_rorateImgAct2;     //旋转图片二
    QAction *m_aboutAct;

    QWidget *m_centreWidget;      //中心窗体
    QVBoxLayout *m_vLayout;       //垂直布局
    QGraphicsView *m_view;        //镜头
    QGraphicsScene *m_scene;      //舞台

    QGraphicsPixmapItem *m_ImgItem1;
    QGraphicsPixmapItem *m_ImgItem2;

    QTimer *m_timer1;
    QTimer *m_timer2;

    qreal m_angle1;
    qreal m_angle2;

    bool m_key1;

private:

    //创建菜单
    void createMenu();

    //创建中心窗体
    void createWidget();

public slots:

    void rorateImg1();

    void rorateImg2();

    void setKey1();

    void setTimer();

};

#endif // CARTOON_H
