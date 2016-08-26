#include "addressbook.h"

addressBook::addressBook(QWidget *parent)
    : QWidget(parent),m_nameLabel(0),m_addressLabel(0),m_nameEdit(0),m_addressEdit(0),
      m_addBtn(0),m_editBtn(0),m_removeBtn(0),m_findBtn(0),m_submitBtn(0),m_cancelBtn(0),
      m_loadBtn(0),m_saveBtn(0),m_previousBtn(0),m_nextBtn(0),m_vLayout(0),m_hLayout(0),
      m_gLayout(0),m_currentType(DEFAULT_Node)
{
    //创建界面
    createInterface();

    //创建连接
    createConnect();
}

addressBook::~addressBook()
{
    
}

//创建界面
void addressBook::createInterface()
{
    //增加标签
    m_nameLabel = new QLabel("Name: ",this);
    m_addressLabel = new QLabel("Address:",this);

    //增加文本框
    m_nameEdit = new QLineEdit;
    m_addressEdit = new QTextEdit;

    //增加按钮
    m_addBtn = new QPushButton("&Add",this);
    m_editBtn = new QPushButton("&Edit",this);
    m_removeBtn = new QPushButton("&Remove",this);
    m_findBtn = new QPushButton("&Find",this);
    m_submitBtn = new QPushButton("&Submit",this);
    m_cancelBtn = new QPushButton("&Cancel",this);
    m_loadBtn = new QPushButton("&Load...",this);
    m_saveBtn = new QPushButton("&Save...",this);
    m_previousBtn = new QPushButton("&Previous",this);
    m_nextBtn = new QPushButton("&Next",this);

    //增加布局
    m_vLayout = new QVBoxLayout;
    m_hLayout = new QHBoxLayout;
    m_gLayout = new QGridLayout(this);

    //将对应的按钮增加到相应的布局中
    m_vLayout->addWidget(m_addBtn);
    m_vLayout->addWidget(m_editBtn);
    m_vLayout->addWidget(m_removeBtn);
    m_vLayout->addWidget(m_findBtn);
    m_vLayout->addWidget(m_submitBtn);
    m_vLayout->addWidget(m_cancelBtn);
    m_vLayout->addWidget(m_loadBtn);
    m_vLayout->addWidget(m_saveBtn);

    m_hLayout->addWidget(m_previousBtn);
    m_hLayout->addWidget(m_nextBtn);

    //将所有的子控件放到网格布局中
    m_gLayout->addWidget(m_nameLabel,0,0,1,1);
    m_gLayout->addWidget(m_nameEdit,0,1,1,1);
    m_gLayout->addWidget(m_addressLabel,1,0,1,1,Qt::AlignTop);
    m_gLayout->addWidget(m_addressEdit,1,1,1,1);

    m_gLayout->addLayout(m_vLayout,1,2,1,1,Qt::AlignTop);
    m_gLayout->addLayout(m_hLayout,2,1,1,1);

    //this->setLayout(m_gLayout);

    //将文本框设置为只读的
    m_nameEdit->setReadOnly(true);
    m_addressEdit->setReadOnly(true);

    //将submit,cancel按钮隐藏
    m_submitBtn->hide();
    m_cancelBtn->hide();

    //将相应的按钮置灰
    m_editBtn->setDisabled(true);
    m_removeBtn->setDisabled(true);
    m_findBtn->setDisabled(true);
    m_saveBtn->setDisabled(true);
    m_previousBtn->setEnabled(false);
    m_nextBtn->setEnabled(false);

    //设置主窗体的标题
    this->setWindowTitle("地址薄");
}

//创建连接
void addressBook::createConnect()
{
    connect(m_addBtn,SIGNAL(clicked()),this,SLOT(addProc()));
    connect(m_editBtn,SIGNAL(clicked()),this,SLOT(editProc()));
    connect(m_removeBtn,SIGNAL(clicked()),this,SLOT(removeProc()));
    connect(m_findBtn,SIGNAL(clicked()),this,SLOT(findProc()));
    connect(m_submitBtn,SIGNAL(clicked()),this,SLOT(submitProc()));
    connect(m_cancelBtn,SIGNAL(clicked()),this,SLOT(cancelProc()));
    connect(m_loadBtn,SIGNAL(clicked()),this,SLOT(loadProc()));
    connect(m_saveBtn,SIGNAL(clicked()),this,SLOT(saveProc()));
    connect(m_previousBtn,SIGNAL(clicked()),this,SLOT(previousProc()));
    connect(m_nextBtn,SIGNAL(clicked()),this,SLOT(nextProc()));
}

//更新界面
void addressBook::updateInterface(nodeType t_nodeType)
{
    m_currentType = t_nodeType;

    switch(m_currentType)
    {
        case ADD_Node:
        case EDIT_Node:
        {
            //将文本框设置为可写的
            m_nameEdit->setReadOnly(false);
            m_addressEdit->setReadOnly(false);

            //将相应的按钮置灰
            m_addBtn->setDisabled(true);
            m_editBtn->setDisabled(true);
            m_removeBtn->setDisabled(true);
            m_findBtn->setEnabled(m_infoMap.size() > 2);
            m_loadBtn->setDisabled(true);
            m_saveBtn->setDisabled(true);
            m_previousBtn->setDisabled(true);
            m_nextBtn->setDisabled(true);

            //显示submit,cancel按钮
            m_submitBtn->show();
            m_cancelBtn->show();
        }
            break;

        case OTHER_Node:
        {
            //将文本框设置为只读的
            m_nameEdit->setReadOnly(true);
            m_addressEdit->setReadOnly(true);

            //隐藏submit,cancel按钮
            m_submitBtn->hide();
            m_cancelBtn->hide();

            //设置相应的按钮
            int t_mapSize = m_infoMap.size();

            m_addBtn->setEnabled(true);
            m_editBtn->setEnabled(t_mapSize > 0);
            m_removeBtn->setEnabled(t_mapSize > 0);
            m_findBtn->setEnabled(t_mapSize > 2);
            m_loadBtn->setEnabled(true);
            m_saveBtn->setEnabled(t_mapSize > 0);
            m_previousBtn->setEnabled(t_mapSize > 1);
            m_nextBtn->setEnabled(t_mapSize > 1);
        }
            break;
        default:
            qDebug() << "没有该节点类型!";
    }
}

void addressBook::addProc()
{
    qDebug() << "addProc!";

    //将文本框的信息保存
    m_oldNode.m_name = m_nameEdit->text();
    m_oldNode.m_address = m_addressEdit->toPlainText();

    //将文本框的信息清空
    m_nameEdit->clear();
    m_addressEdit->clear();

    updateInterface(ADD_Node);
}

void addressBook::editProc()
{
    qDebug() << "editProc!";

    //将文本框的信息保存
    m_oldNode.m_name = m_nameEdit->text();
    m_oldNode.m_address = m_addressEdit->toPlainText();

    updateInterface(EDIT_Node);
}

void addressBook::removeProc()
{
    qDebug() << "removeProc!";
}

void addressBook::findProc()
{
    qDebug() << "findProc!";
}

void addressBook::submitProc()
{
    qDebug() << "submitProc!";

    //获取文本框的信息
    m_currentNode.m_name = m_nameEdit->text();
    m_currentNode.m_address = m_addressEdit->toPlainText();

    if(m_currentNode.m_name.isEmpty() || m_currentNode.m_address.isEmpty())
    {
        QMessageBox::information(this,"文本框信息为空!","请输入一个名字和地址.",QMessageBox::Ok);

        return;
    }

    if(m_currentType == ADD_Node)
    {
        if(!m_infoMap.contains(m_currentNode.m_name))
        {
            m_infoMap.insert(m_currentNode.m_name,m_currentNode.m_address);

            QMessageBox::information(this,"增加人员信息成功!",m_currentNode.m_name + " 已经增加到地址薄中.",QMessageBox::Ok);
        }
        else
        {
            QMessageBox::information(this,"增加人员信息失败!","对不起, " + m_currentNode.m_name + " 已经在地址薄中.",QMessageBox::Ok);
        }
    }
    else if(m_currentType == EDIT_Node)
    {
        if(m_currentNode.m_name != m_oldNode.m_name || m_currentNode.m_address != m_oldNode.m_address)
        {
            if(m_currentNode.m_name != m_oldNode.m_name && m_infoMap.contains(m_currentNode.m_name))
            {
                QMessageBox::information(this,"修改人员信息失败!","对不起, " + m_currentNode.m_name + " 已经在地址薄中.",QMessageBox::Ok);

                m_nameEdit->setText(m_oldNode.m_name);
                m_addressEdit->setText(m_oldNode.m_address);
            }
            else
            {
                m_infoMap.remove(m_oldNode.m_name);
                m_infoMap.insert(m_currentNode.m_name,m_currentNode.m_address);

                QMessageBox::information(this,"修改人员信息成功!",m_oldNode.m_name + " 的信息在地址薄中已经修改!",QMessageBox::Ok);
            }
        }
    }

    //更新界面
    updateInterface(OTHER_Node);


}

void addressBook::cancelProc()
{
    qDebug() << "cancelProc!";
}

void addressBook::loadProc()
{
    qDebug() << "loadProc!";
}

void addressBook::saveProc()
{
    qDebug() << "saveProc!";
}

void addressBook::previousProc()
{
    qDebug() << "previousProc!";
}

void addressBook::nextProc()
{
    qDebug() << "nextProc!";
}
