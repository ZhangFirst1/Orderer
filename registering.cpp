#include "registering.h"
#include "ui_registering.h"

Registering::Registering(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Registering)
{
    ui->setupUi(this);
    connect(ui->registerButton, &QPushButton::clicked,this, &Registering::registerButton_clicked);
    connect(ui->returnButton, &QPushButton::clicked,this, &Registering::returnButton_clicked);
}

Registering::~Registering()
{
    delete ui;
}

void Registering::registerButton_clicked()
{
    QString account = ui->accountEdit->text();
    QString passwd1 = ui->passwdEdit->text();
    QString passwd2 = ui->ensureEdit->text();

    if(passwd1 != passwd2)
    {
        QMessageBox::warning(this,"警告","两次密码不一致，请重新输入");
        ui->accountEdit->clear();
        ui->passwdEdit->clear();
        ui->ensureEdit->clear();
    }else if(account=="" || passwd1==""){
        QMessageBox::warning(this,"警号","输入不能为空！");
    }
    else{
        // 启用客户端连接
        TcpClient& instance = TcpClient::getInstance();
        // 判断连接并向后台发送登录请求
        if(TcpClient::server == NULL){
            qDebug() << "NULL";
        }else{
            TcpClient::WriteToServer(ui->accountEdit->text() + " " + ui->passwdEdit->text(), "REGISTER");
        }

        // 在事件循环中等待响应
        QEventLoop loop;
        connect(TcpClient::server, SIGNAL(readyRead()), &loop, SLOT(quit()));
        loop.exec();

        if(instance.registered == true){
            instance.registered = false;
            QMessageBox::information(this,"提示","注册成功，请登录");
            this->close();
            parentWidget()->show();
        }else{
            QMessageBox::warning(this,"警告","用户已存在，请重新输入");
            ui->accountEdit->clear();
            ui->passwdEdit->clear();
            ui->ensureEdit->clear();
        }
    }
}
void Registering::returnButton_clicked()
{
    this->close();
    parentWidget()->show();
}
