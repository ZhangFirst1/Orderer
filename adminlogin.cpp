#include "adminlogin.h"
#include "ui_adminlogin.h"

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
        delete this;

    }
}
