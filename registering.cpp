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
        ui->passwdEdit->clear();
        ui->ensureEdit->clear();
    }else{
        bool ret = instance.isexisted(account);
        if(ret == true){
            QMessageBox::warning(this,"警告","账号已经存在,请重新输入");
            ui->accountEdit->clear();
        }
        else
        {
            QSqlQuery sql_query;
            QString sql = "insert into client values (?, ?)";
            sql_query.prepare(sql);
            sql_query.addBindValue(account);
            sql_query.addBindValue(passwd1);
            sql_query.exec();
            QMessageBox::information(this,"提示","注册成功，请登录");
            this->close();
            parentWidget()->show();
        }
    }
}
void Registering::returnButton_clicked()
{
    this->close();
    parentWidget()->show();
}
