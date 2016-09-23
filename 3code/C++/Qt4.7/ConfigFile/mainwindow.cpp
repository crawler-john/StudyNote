#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ConfigFile.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CConfigFile  *pConfigFile = new CConfigFile();
    if(pConfigFile != NULL)
    {
        int priority = 0;
        bool flag = GETITEMPARAM("ScreenDisp/DateTimeThread", "threadpriority", priority);
        qDebug("%d\n",priority);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
