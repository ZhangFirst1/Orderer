#include "registering.h"
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
    connect(ui->loginButton, &QPushButton::clicked, this, &Login::loginButton_clicked);
    connect(ui->adminButton, &QPushButton::clicked, this, &Login::adminButton_clicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &Login::registerButton_clicked);
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
        MainWindow* main_window = new MainWindow(this); //
        main_window->show();
        this->hide(); //
    }else{
        qDebug() << "error";
    }
}

void Login::adminButton_clicked(){
    AdminLogin* a_login = new AdminLogin(this);
    a_login->show();
    this->hide();
}

void Login::registerButton_clicked()
{
    this->hide();
    Registering* rs = new Registering(this);
    rs->setWindowFlag(Qt::Window);
    rs->show();
}

//重写 paintEvent 函数，在这里绘制背景图
void Login::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);

    // 获取当前窗口的大小
    QSize widgetSize = size();

    // 从文件加载背景图（这里需要替换为你的实际路径）
    QPixmap backgroundImage(":/background/cloud2.jpg");

    // 绘制背景图并进行自适应大小处理
    painter.drawPixmap(0, 0, widgetSize.width(), widgetSize.height(), backgroundImage);
}

