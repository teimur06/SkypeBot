#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QDir().setCurrent(QFileInfo(argv[0]).absolutePath());
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
