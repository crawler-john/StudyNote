#include "cartoon.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cartoon w;
    w.show();
    
    return a.exec();
}
