#include "cartoon.h"

cartoon::cartoon(QWidget *parent)
    : QMainWindow(parent),m_gameMenu(0),m_helpMenu(0),m_rorateImgAct1(0),m_rorateImgAct2(0),
      m_aboutAct(0),m_centreWidget(0),m_vLayout(0),m_view(0),m_scene(0),m_ImgItem1(0),
      m_ImgItem2(0),m_timer1(0),m_timer2(0),m_angle1(0),m_angle2(0),m_key1(false)
{
    //创建菜单
    createMenu();

    //创建中心窗体
    createWidget();
}

cartoon::~cartoon()
{
    
}

//创建菜单
void cartoon::createMenu()
{
    //增加菜单
    m_gameMenu = new QMenu("游戏",this);
    m_helpMenu = new QMenu("帮助",this);

    //增加子选项
    m_rorateImgAct1 = new QAction("旋转图片1",this);
    m_rorateImgAct2 = new QAction("旋转图片2",this);
    m_aboutAct = new QAction("关于",this);

    m_rorateImgAct1->setCheckable(true);
    m_rorateImgAct2->setCheckable(true);

    m_gameMenu->addAction(m_rorateImgAct1);
    m_gameMenu->addAction(m_rorateImgAct2);
    m_helpMenu->addAction(m_aboutAct);

    this->menuBar()->addMenu(m_gameMenu);
    this->menuBar()->addMenu(m_helpMenu);
}

//创建中心窗体
void cartoon::createWidget()
{
    //增加中心窗体
    m_centreWidget = new QWidget;

    //增加垂直布局
    m_vLayout = new QVBoxLayout(m_centreWidget);

    //增加舞台
    m_scene = new QGraphicsScene;
    m_scene->setSceneRect(0,0,480,480);

    //增加镜头
    m_view = new QGraphicsView(m_scene);
    m_view->setFixedSize(485,485);

    //将镜头放到垂直布局中
    m_vLayout->addWidget(m_view);

    //将中心窗体设置到主窗体中
    this->setCentralWidget(m_centreWidget);

    QPixmap t_pixmap(":/images/ministar.bmp");
    qreal t_ImgWidth = t_pixmap.width();
    qreal t_ImgHeight = t_pixmap.height();

    //增加道具
    QGraphicsPixmapItem *t_item1 = new QGraphicsPixmapItem(t_pixmap);
    t_item1->setPos(0,0);

    QGraphicsPixmapItem *t_item2 = new QGraphicsPixmapItem(t_pixmap);
    t_item2->setPos(t_ImgWidth,0);

    QGraphicsPixmapItem *t_item3 = new QGraphicsPixmapItem(t_pixmap);
    t_item3->setPos(0,t_ImgHeight);

    QGraphicsPixmapItem *t_item4 = new QGraphicsPixmapItem(t_pixmap);
    t_item4->setPos(t_ImgWidth,t_ImgHeight);

    m_ImgItem1 = new QGraphicsPixmapItem(QPixmap(":/images/mine.jpg"));
    m_ImgItem1->setPos(m_scene->width()/2,m_scene->height()/2);
    //m_ImgItem1->setRotation(60.0);

    m_ImgItem2 = new QGraphicsPixmapItem(QPixmap(":/images/question.jpg"));
    m_ImgItem2->setPos(m_scene->width()*3/4,m_scene->height()*3/4);
    //m_ImgItem2->setRotation(90.0);

    m_ImgItem2->setOffset(-m_ImgItem2->pixmap().width()/2,-m_ImgItem2->pixmap().height()/2);

    //将道具放到舞台中
    m_scene->addItem(t_item1);
    m_scene->addItem(t_item2);
    m_scene->addItem(t_item3);
    m_scene->addItem(t_item4);
    m_scene->addItem(m_ImgItem1);
    m_scene->addItem(m_ImgItem2);


    m_timer1 = new QTimer;
    m_timer1->setInterval(100);

    m_timer2 = new QTimer;
    m_timer2->setInterval(100);

    m_timer1->start();
    //m_timer2->start();

    connect(m_timer1,SIGNAL(timeout()),this,SLOT(rorateImg1()));
    connect(m_timer2,SIGNAL(timeout()),this,SLOT(rorateImg2()));

    connect(m_rorateImgAct1,SIGNAL(triggered()),this,SLOT(setKey1()));
    connect(m_rorateImgAct2,SIGNAL(triggered()),this,SLOT(setTimer()));

}

void cartoon::rorateImg1()
{
    if(m_key1)
    {
        m_angle1 += 10.0;

        if(m_angle1 > 360.0)
        {
            m_angle1 -= 360.0;
        }

        m_ImgItem1->setRotation(m_angle1);
    }
}

void cartoon::rorateImg2()
{
    m_angle2 += 10.0;

    if(m_angle2 > 360.0)
    {
        m_angle2 -= 360.0;
    }

    m_ImgItem2->setRotation(m_angle2);
}

void cartoon::setKey1()
{
    m_key1 = m_rorateImgAct1->isChecked();
}

void cartoon::setTimer()
{
    if(m_rorateImgAct2->isChecked())
    {
        m_timer2->start();
    }
    else
    {
        m_timer2->stop();
    }
}
