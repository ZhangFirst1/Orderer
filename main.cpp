#include "mainwindow.h"
#include "tcpclient.h"
#include "tcpservers.h"
#include "login.h"
#include "backend.h"
<<<<<<< HEAD
#include "clientdbview.h"
=======
#include "adminlogin.h"

>>>>>>> c5e30eb98c240ff15347b85d8e5fbb0afcf67826
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

<<<<<<< HEAD
=======
    //MainWindow w;
    //w.show();

>>>>>>> c5e30eb98c240ff15347b85d8e5fbb0afcf67826
    Login l;
    l.show();
    return a.exec();
}
