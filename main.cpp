#include "mainwindow.h"
#include "tcpclient.h"
#include "tcpservers.h"
#include "login.h"
#include "backend.h"
#include "adminlogin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow w;
    //w.show();
    Login l;
    l.show();
    backend b;
    b.show();
    return a.exec();
}
