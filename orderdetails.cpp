#include "orderdetails.h"
#include "ui_orderdetails.h"
#include "dealorder.h"

orderdetails::orderdetails(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::orderdetails)
{
    ui->setupUi(this);
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
    parentWidget()->show();
    delete this;
}

