#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <QMainWindow>
#include <QMenu>          //菜单
#include <QMenuBar>       //菜单栏
#include <QToolBar>       //工具栏
#include <QAction>        //子选项
#include <QTextEdit>      //多行文本框
#include <QStatusBar>     //状态栏
#include <QKeySequence>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include "aboutdialog.h"

class noteBook : public QMainWindow
{
    Q_OBJECT
    
public:
    noteBook(QWidget *parent = 0);
    ~noteBook();

    virtual void closeEvent(QCloseEvent * event);

private:

    //菜单
    QMenu *m_fileMenu;          //文件
    QMenu *m_editMenu;          //编辑
    QMenu *m_helpMenu;          //帮助

    //子选项
    QAction *m_newAction;          //新建文件
    QAction *m_openAction;         //打开文件
    QAction *m_saveAction;         //保存文件
    QAction *m_saveasAction;       //另存文件
    QAction *m_exitAction;         //退出

    QAction *m_cutAction;          //剪切
    QAction *m_copyAction;         //复制
    QAction *m_pasteAction;        //粘贴

    QAction *m_aboutAction;        //关于

    //工具栏
    QToolBar *m_fileToolBar;       //文件
    QToolBar *m_editToolBar;       //编辑

    //文本框
    QTextEdit *m_textEdit;

    //状态栏
    QStatusBar *m_statusBar;

    //关于对话框
    aboutDialog m_aboutDialog;

    //文件名
    QString m_fileName;

private:

    //创建界面
    void createInterface();

    //创建连接
    void createConnect();


public slots:

    void textChanges();   //文本框正在被修改的响应函数

    void newFile();       //新建文件
    void openFile();      //打开文件
    void saveFile();      //保存文件
    void saveasFile();    //另存文件


};

#endif // NOTEBOOK_H
