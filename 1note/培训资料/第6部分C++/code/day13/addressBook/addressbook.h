#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>
#include <QLabel>         //标签类
#include <QLineEdit>      //单行文本框类
#include <QTextEdit>      //多行文本框
#include <QPushButton>    //按钮类
#include <QVBoxLayout>    //垂直布局类
#include <QHBoxLayout>    //水平布局类
#include <QGridLayout>    //网格布局类
#include <QDebug>         //调试类
#include <QMap>             //Qt映射容器
#include <QMessageBox>    //弹出消息对话框类

class addressBook : public QWidget
{
    Q_OBJECT
    
public:
    addressBook(QWidget *parent = 0);
    ~addressBook();

private:

    //存放人员信息的结构体
    struct addressInfo
    {
        QString m_name;
        QString m_address;
    };

    enum nodeType
    {
        DEFAULT_Node = 1,      //默认节点类型
        ADD_Node = 2,          //add节点
        EDIT_Node = 3,         //edit节点
        OTHER_Node = 4         //其它节点
    };

private:

    //节点当前的信息
    addressInfo m_currentNode;

    //节点之前的信息
    addressInfo m_oldNode;

    //当前节点的类型
    nodeType m_currentType;

    //map存放人员信息的容器,key是name,value是address
    QMap<QString,QString> m_infoMap;

private:

    //创建界面
    void createInterface();

    //创建连接
    void createConnect();

    //更新界面
    void updateInterface(nodeType t_nodeType);

private:

    //标签
    QLabel *m_nameLabel;       //名字
    QLabel *m_addressLabel;    //地址

    //文本框
    QLineEdit *m_nameEdit;     //名字
    QTextEdit *m_addressEdit;  //地址

    //按钮
    QPushButton *m_addBtn;
    QPushButton *m_editBtn;
    QPushButton *m_removeBtn;
    QPushButton *m_findBtn;
    QPushButton *m_submitBtn;
    QPushButton *m_cancelBtn;
    QPushButton *m_loadBtn;
    QPushButton *m_saveBtn;
    QPushButton *m_previousBtn;
    QPushButton *m_nextBtn;

    //布局
    QVBoxLayout *m_vLayout;     //垂直布局
    QHBoxLayout *m_hLayout;     //水平布局
    QGridLayout *m_gLayout;     //网格布局

public slots:      //自定义槽函数

    void addProc();       //点击add按钮的响应函数
    void editProc();      //点击edit按钮的响应函数
    void removeProc();    //点击remove按钮的响应函数
    void findProc();      //点击find按钮的响应函数
    void submitProc();    //点击submit按钮的响应函数
    void cancelProc();    //点击cancel按钮的响应函数
    void loadProc();      //点击load按钮的响应函数
    void saveProc();      //点击save按钮的响应函数
    void previousProc();  //点击previous按钮的响应函数
    void nextProc();      //点击next按钮的响应函数











};

#endif // ADDRESSBOOK_H
