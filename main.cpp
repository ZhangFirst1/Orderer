#include "login.h"
#include "clientdbview.h"
#include "mainwindow.h"
#include "backend.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //MainWindow w;
    //w.show();
    //Login l;
    //l.show();
    backend beck;
    beck.show();

    return a.exec();
}
