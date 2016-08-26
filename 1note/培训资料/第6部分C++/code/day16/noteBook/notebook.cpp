#include "notebook.h"

noteBook::noteBook(QWidget *parent)
    : QMainWindow(parent),m_fileMenu(0),m_editMenu(0),m_helpMenu(0),m_newAction(0),m_openAction(0),
      m_saveAction(0),m_saveasAction(0),m_exitAction(0),m_cutAction(0),m_copyAction(0),m_pasteAction(0),
      m_aboutAction(0),m_fileToolBar(0),m_editToolBar(0),m_textEdit(0),m_statusBar(0)
{

    //创建界面
    createInterface();

    //创建连接
    createConnect();
}

noteBook::~noteBook()
{
    
}

void noteBook::closeEvent(QCloseEvent *event)
{
    qDebug() << "close Event!";
}

//创建界面
void noteBook::createInterface()
{
    //增加菜单
    m_fileMenu = new QMenu("文件",this);
    m_editMenu = new QMenu("编辑",this);
    m_helpMenu = new QMenu("帮助",this);

    //增加子选项
    m_newAction = new QAction(QIcon(":/images/new.png"),"新建文件",this);
    m_openAction = new QAction(QIcon(":/images/open.png"),"打开文件...",this);
    m_saveAction = new QAction(QIcon(":/images/save.png"),"保存文件",this);
    m_saveasAction = new QAction("文件另存为...",this);
    m_exitAction = new QAction("退出",this);

    m_cutAction = new QAction(QIcon(":/images/cut.png"),"剪切",this);
    m_copyAction = new QAction(QIcon(":/images/copy.png"),"复制",this);
    m_pasteAction = new QAction(QIcon(":/images/paste.png"),"粘贴",this);

    m_aboutAction = new QAction("关于",this);

    //设置快捷键
    m_newAction->setShortcut(QKeySequence("Ctrl+N"));
    m_openAction->setShortcut(QKeySequence("Ctrl+O"));
    m_saveAction->setShortcut(QKeySequence("Ctrl+S"));

    m_cutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    m_copyAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    m_pasteAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));

    //增加工具栏
    m_fileToolBar = new QToolBar("文件",this);
    m_editToolBar = new QToolBar("编辑",this);

    //将子选项增加到相应的菜单中

    m_fileMenu->addAction(m_newAction);
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addAction(m_saveAction);
    m_fileMenu->addAction(m_saveasAction);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    m_editMenu->addAction(m_cutAction);
    m_editMenu->addAction(m_copyAction);
    m_editMenu->addAction(m_pasteAction);

    m_helpMenu->addAction(m_aboutAction);

    //将菜单增加到菜单栏并挂载到主窗体中
    this->menuBar()->addMenu(m_fileMenu);
    this->menuBar()->addMenu(m_editMenu);
    this->menuBar()->addMenu(m_helpMenu);


    //将子选项增加到相应的工具栏中
    m_fileToolBar->addAction(m_newAction);
    m_fileToolBar->addAction(m_openAction);
    m_fileToolBar->addAction(m_saveAction);

    m_editToolBar->addAction(m_cutAction);
    m_editToolBar->addAction(m_copyAction);
    m_editToolBar->addAction(m_pasteAction);

    //将工具栏挂载到主窗体中
    this->addToolBar(m_fileToolBar);
    this->addToolBar(m_editToolBar);

    //增加文本框
    m_textEdit = new QTextEdit;

    //将文本框设置为中心窗体
    this->setCentralWidget(m_textEdit);

    //增加状态栏
    m_statusBar = new QStatusBar;
    m_statusBar->showMessage("准备就绪!");

    this->setStatusBar(m_statusBar);

    this->resize(410,450);

    m_cutAction->setDisabled(true);
    m_copyAction->setDisabled(true);

    this->setWindowTitle("记事本");

}

//创建连接
void noteBook::createConnect()
{
    connect(m_aboutAction,SIGNAL(triggered()),&m_aboutDialog,SLOT(show()));

    //激活cut,copy子选项
    connect(m_textEdit,SIGNAL(copyAvailable(bool)),m_cutAction,SLOT(setEnabled(bool)));
    connect(m_textEdit,SIGNAL(copyAvailable(bool)),m_copyAction,SLOT(setEnabled(bool)));

    //实现cut,copy,paste功能
    connect(m_cutAction,SIGNAL(triggered()),m_textEdit,SLOT(cut()));
    connect(m_copyAction,SIGNAL(triggered()),m_textEdit,SLOT(copy()));
    connect(m_pasteAction,SIGNAL(triggered()),m_textEdit,SLOT(paste()));

    connect(m_textEdit,SIGNAL(textChanged()),this,SLOT(textChanges()));

    connect(m_newAction,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(m_openAction,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(m_saveAction,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(m_saveasAction,SIGNAL(triggered()),this,SLOT(saveasFile()));
    connect(m_exitAction,SIGNAL(triggered()),this,SLOT(close()));





}

void noteBook::textChanges()
{
    qDebug() << "textChanges!";

    if(m_fileName.isEmpty())
    {
        this->setWindowTitle("新建文本文件.txt*");
    }
    else
    {
        QDir t_dir(m_fileName);

        QString t_singleName = t_dir.dirName();

        this->setWindowTitle(t_singleName + "*");
    }

    //将文本框设置为正在被修改状态
    m_textEdit->document()->setModified(true);

}

//新建文件
void noteBook::newFile()
{
    qDebug() << "new File!";

    if(m_textEdit->document()->isModified())
    {
        if(!m_fileName.isEmpty() || !m_textEdit->toPlainText().isEmpty())
        {
            QMessageBox::StandardButton t_choiceBtn = QMessageBox::information(this,"提示!","文件内容已经被修改,是否保存?",
                                                                               QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);

            if(t_choiceBtn == QMessageBox::Save)
            {
                saveFile();
            }
            else if( t_choiceBtn == QMessageBox::Cancel)
            {
                return;
            }
        }
    }

    //清空文本框的信息
    m_textEdit->clear();

    //将文件名设置为空
    m_fileName = "";

    //设置文本框的状态为未修改状态
    m_textEdit->document()->setModified(false);

    //设置窗体的标题
    this->setWindowTitle("新建文本文件.txt");
}

//打开文件
void noteBook::openFile()
{
    qDebug() << "open File!";
}

//保存文件
void noteBook::saveFile()
{
    qDebug() << "save File!";

    //判断是否为新文件
    if(m_fileName.isEmpty())
    {
        m_fileName = QFileDialog::getSaveFileName(this,"保存文件...","","ALL File(*.*);;TXT File(*.txt)");

        if(m_fileName.isEmpty())
        {
            qDebug() << "get file name failed!";
            return;
        }
    }
    else if(!m_fileName.isEmpty() && !m_textEdit->document()->isModified())
    {
        return;
    }

    QFile t_writeFile(m_fileName);

    t_writeFile.open(QIODevice::WriteOnly|QIODevice::Text);

    if(!t_writeFile.isOpen())
    {
        qDebug() << "open file : " << m_fileName << " failed!";
        return;
    }

    QTextStream t_textStream(&t_writeFile);

    t_textStream << m_textEdit->toPlainText();

    t_writeFile.close();

    //设置文本框的状态为已修改完成状态
    m_textEdit->document()->setModified(false);

    QDir t_dir(m_fileName);

    QString t_singleName = t_dir.dirName();

    this->setWindowTitle(t_singleName);

}

//另存文件
void noteBook::saveasFile()
{
    qDebug() << "save as File!";

    m_fileName = QFileDialog::getSaveFileName(this,"文件另存为...","","ALL File(*.*);;TXT File(*.txt)");

    if(m_fileName.isEmpty())
    {
        qDebug() << "get file name failed!";
        return;
    }

    QFile t_writeFile(m_fileName);

    t_writeFile.open(QIODevice::WriteOnly|QIODevice::Text);

    if(!t_writeFile.isOpen())
    {
        qDebug() << "open file : " << m_fileName << " failed!";
        return;
    }

    QTextStream t_textStream(&t_writeFile);

    t_textStream << m_textEdit->toPlainText();

    t_writeFile.close();

    //设置文本框的状态为已修改完成状态
    m_textEdit->document()->setModified(false);

    QDir t_dir(m_fileName);

    QString t_singleName = t_dir.dirName();

    this->setWindowTitle(t_singleName);
}
