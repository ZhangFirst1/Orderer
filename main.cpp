#include "login.h"
#include "clientdbview.h"

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
    // clientdbview* client_db = new clientdbview;
    // client_db->show();

    return a.exec();
}
