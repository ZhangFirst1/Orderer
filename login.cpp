#include "login.h"
#include "ui_login.h"
#include "tcpclient.h"
#include "adminlogin.h"
#include "mainwindow.h"
#include <QThread>

QString TcpClient::name;

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
    // 启用客户端连接
    TcpClient& instance = TcpClient::getInstance();
    // 判断连接并向后台发送登录请求
    if(TcpClient::server == NULL){
        qDebug() << "NULL";
    }else{
        TcpClient::WriteToServer(ui->userEdit->text() + " " + ui->pwdEdit->text(), "LOGIN");
    }

    // 在事件循环中等待响应
    QEventLoop loop;
    connect(TcpClient::server, SIGNAL(readyRead()), &loop, SLOT(quit()));
    loop.exec();

    if(instance.isLogin_ == true){
        TcpClient::name = ui->userEdit->text();
        MainWindow* main_window = new MainWindow();
        main_window->show();
        this->close();
    }else{
        qDebug() << "error";
    }
}

void Login::adminButton_clicked(){
    AdminLogin* a_login = new AdminLogin(this);
    a_login->show();
    this->hide();
}
