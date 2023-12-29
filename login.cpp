#include "login.h"
#include "ui_login.h"
#include "tcpclient.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked(){
    if(TcpClient::server == NULL){
        qDebug() << "NULL";
    }else{
        TcpClient::WriteToServer(ui->userEdit->text());
        TcpClient::WriteToServer(ui->pwdEdit->text());
    }
}
