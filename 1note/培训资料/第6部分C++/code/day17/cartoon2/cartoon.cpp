#include "cartoon.h"

cartoon::cartoon(QWidget *parent)
    : QMainWindow(parent),m_gameMenu(0),m_helpMenu(0),m_rorateImgAct1(0),m_rorateImgAct2(0),
      m_aboutAct(0),m_centreWidget(0),m_vLayout(0),m_view(0),m_scene(0)
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
    m_scene = new myScene;

    //增加镜头
    m_view = new QGraphicsView(m_scene);

    //将镜头放到垂直布局中
    m_vLayout->addWidget(m_view);

    //将中心窗体设置到主窗体中
    this->setCentralWidget(m_centreWidget);

    QPixmap t_pixmap(":/images/ministar.bmp");
    qreal t_ImgWidth = t_pixmap.width();
    qreal t_ImgHeight = t_pixmap.height();

    for(int i = 0; i < 5; i++)
    {
        vector<myItem*> tmp;

        for(int j = 0; j < 5; j++)
        {
            myItem *t_item = new myItem(i,j,t_pixmap);
            t_item->setPos(j*t_ImgWidth,i*t_ImgHeight);
            tmp.push_back(t_item);

            m_scene->addItem(t_item);
        }

        m_scene->m_itemVec.push_back(tmp);
    }

    m_scene->setSceneRect(0,0,5*t_ImgWidth,5*t_ImgHeight);
    m_view->setFixedSize(m_scene->width()+5,m_scene->height()+5);

    int t_mineNum = 5;

    srand(time(0));

    while(t_mineNum)
    {
        int t_x = rand()%5;
        int t_y = rand()%5;

        if(m_scene->m_itemVec[t_x][t_y]->m_mineNum != -1)
        {
            m_scene->m_itemVec[t_x][t_y]->m_mineNum = -1;

            t_mineNum--;
        }
    }




}




