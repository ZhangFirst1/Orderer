#include "login.h"
#include "clientdbview.h"
#include "mainwindow.h"
#include "backend.h"
#include "dbmanager.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //MainWindow w;
    //w.show();
    Login l;
    l.show();
    //backend beck;
    //beck.show();
    //DbManager instance = DbManager::getDbInstance();
    //QSqlQuery sql_query;
    //QString sql = "create table client (account varchar(255) primary key, passwd varchar(255))";
    //sql_query.exec(sql);
    return a.exec();
}
