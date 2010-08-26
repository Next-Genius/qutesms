#include <QtGui/QApplication>
#include "smshttp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::addResourceSearchPath(QDir::currentPath()+"/icons");
    smshttp w;

    w.setWindowTitle("QuteSms");
    w.setWindowIcon(QIcon(":/icons/icon32.ico"));
    w.show();
    return a.exec();
}
