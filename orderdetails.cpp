#include "orderdetails.h"
#include "ui_orderdetails.h"
#include "dbmanager.h"
#include "dealorder.h"

orderdetails::orderdetails(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::orderdetails)
{
    ui->setupUi(this);
    //ui->ordertableView->setModel(od_db_manager.model);
}

orderdetails::~orderdetails()
{
    delete ui;
}

void orderdetails::on_odshowButton_clicked()
{

}


void orderdetails::on_odreturnButton_clicked()
{
    dealorder *do_=new dealorder();
    do_->show();
    delete this;

}

