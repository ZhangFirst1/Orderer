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

    // QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName("mydb.db");
    // if(!db.open())
    // {
    //     qDebug() << "fail to connect to root SQLite";
    // }else
    // {
    //     qDebug() << "connect to DB successfully";
    //     QSqlQuery sql_query;
    //     QString sql = "create table menu (dishname varchar(255) primary key, price varchar(255), store verchar(255))";
    //     int i = sql_query.exec(sql);
    //     qDebug() << i;
    // }

    return a.exec();
}
