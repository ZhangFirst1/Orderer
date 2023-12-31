#include "backend.h"
#include "ui_backend.h"
#include "clientdbview.h"
#include "dbmanager.h"


backend::backend(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::backend)
{
    ui->setupUi(this);
    DbManager db_manager = DbManager::getDbInstance();
    connect(ui->clientButton,&QPushButton::clicked,this,&backend::clientButton_clicked);
    connect(ui->menuButton,&QPushButton::clicked,this,&backend::menuButton_clicked);
    connect(ui->dealButton,&QPushButton::clicked,this,&backend::dealButton_clicked);
    connect(ui->recordButton,&QPushButton::clicked,this,&backend::recordButton_clicked);
    connect(ui->closeButton,&QPushButton::clicked,this,&backend::closeButton_clicked);
}

backend::~backend()
{
    delete ui;
}
void backend::clientButton_clicked()
{
    clientdbview* client_db = new clientdbview();
    client_db->show();
    this->hide();
}
void backend::menuButton_clicked()
{

}
void backend::dealButton_clicked()
{

}
void backend::recordButton_clicked()
{

}
void backend::closeButton_clicked()
{
    this->close();
}
