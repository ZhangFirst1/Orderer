#include "login.h"
#include "ui_login.h"
#include "tcpclient.h"
#include "adminlogin.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::pressed, this, &Login::loginButton_clicked);
    connect(ui->adminButton, &QPushButton::pressed, this, &Login::adminButton_clicked);
}

Login::~Login()
{
    delete ui;
}

void Login::loginButton_clicked(){
    if(TcpClient::server == NULL){
        qDebug() << "NULL";
    }else{
        TcpClient::WriteToServer(ui->userEdit->text());
        TcpClient::WriteToServer(ui->pwdEdit->text());
    }

}

void Login::adminButton_clicked(){
    AdminLogin* a_login = new AdminLogin(this);
    a_login->show();
    this->hide();
}
