#include "server/mainwindow_server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow_ w(argc, argv);
    w.show();
    return a.exec();
}
