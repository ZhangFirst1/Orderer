#include "backend.h"
#include "ui_backend.h"
#include "clientdbview.h"
#include "menu.h"

backend::backend(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::backend)
{
    ui->setupUi(this);
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
    this->hide();
    clientdbview* client_db = new clientdbview(this);
    client_db->setWindowFlag(Qt::Window);
    client_db->show();
}
void backend::menuButton_clicked()
{
    this->hide();
    menu * menu_db=new menu(this);
    menu_db->setWindowFlag(Qt::Window);
    menu_db->show();
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
