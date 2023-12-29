#include "mainwindow.h"
#include "tcpclient.h"
#include "tcpservers.h"
#include "login.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Login l;
    l.show();
    return a.exec();
}
