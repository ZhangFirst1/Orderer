#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "tcpservers.h"
#include "backend.h"
#include "dbmanager.h"

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
        // 初始化服务器端与数据库
        DbManager& db_manager = DbManager::getDbInstance();
        TcpServers& instance = TcpServers::getInstance();
        backend* back = new backend();
        back->show();
        delete this;
    }
}

//重写 paintEvent 函数，在这里绘制背景图
void AdminLogin::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);

    // 获取当前窗口的大小
    QSize widgetSize = size();

    // 从文件加载背景图（这里需要替换为你的实际路径）
    QPixmap backgroundImage(":/background/cloud1.jpg");

    // 绘制背景图并进行自适应大小处理
    painter.drawPixmap(0, 0, widgetSize.width(), widgetSize.height(), backgroundImage);
}
