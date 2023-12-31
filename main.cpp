#include "mainwindow.h"
#include "tcpclient.h"
#include "tcpservers.h"
#include "login.h"
#include "backend.h"
#include "clientdbview.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login l;
    l.show();
    return a.exec();
}
