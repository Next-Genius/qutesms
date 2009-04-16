#include <QtGui/QApplication>
#include "smshttp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::addResourceSearchPath(QDir::currentPath()+"/icons");
    //setWindowTitle("QuteSms");
    smshttp w;
    w.show();
    return a.exec();
}
