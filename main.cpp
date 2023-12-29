#include "mainwindow.h"
#include "tcpclient.h"
#include "tcpservers.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // test
    TcpClient c;

    return a.exec();
}
