#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "tcpservers.h"

AdminLogin::AdminLogin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::pressed, this, &AdminLogin::backButton_click);
    connect(ui->loginButton, &QPushButton::pressed, this, &AdminLogin::loginButton_click);
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::backButton_click(){
    this->close();
    parentWidget()->show();
}

void AdminLogin::loginButton_click(){
    QString admin_name = ui->userEdit->text();
    QString admin_pwd = ui->pwdEdit->text();
    if(admin_name == "admin" && admin_pwd == "qwer"){
        isAdmin = true;
        // 初始化服务器端
        TcpServers server;

        delete this;
    }
}
