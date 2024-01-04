#include "orderdetails.h"
#include "ui_orderdetails.h"
#include "dealorder.h"


//创建一行信息
QWidget *createRow(const QString &labelText1, const QString &labelText2, const QString &labelText3)
{
    QWidget *rowWidget = new QWidget();
    QHBoxLayout *rowLayout = new QHBoxLayout(rowWidget);

    QLabel *label1 = new QLabel(labelText1);
    QLabel *label2 = new QLabel(labelText2);
    QLabel *label3 = new QLabel(labelText3);

    rowLayout->addWidget(label1);
    rowLayout->addWidget(label2);
    rowLayout->addWidget(label3);

    rowWidget->setLayout(rowLayout);
    return rowWidget;
}

orderdetails::orderdetails(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::orderdetails)
{
    ui->setupUi(this);
}
// 重载构造函数
orderdetails::orderdetails(QWidget *parent, struct OneOrder* one_order)
    : QWidget(parent)
    , ui(new Ui::orderdetails)
    , one_order_(new OneOrder)
{
    ui->setupUi(this);
    memset(one_order_->order, 0 , sizeof one_order_->order);
    this->one_order_->order_num = one_order->order_num;
    for(int i=0;i<30;i++){
        if(one_order->order[i].name != ""){
            this->one_order_->order[i] = one_order->order[i];
        }else{
            break;
        }
    }
}

orderdetails::~orderdetails()
{
    delete ui;
    delete one_order_;
}

void orderdetails::creatItem(){
    QVBoxLayout *scrollLayout = new QVBoxLayout();

    double total = 0.0;
    for(int i=0; i < one_order_->order_num; i++){
        qDebug() << "details after assigment" << one_order_->order[i].name;
        QWidget* rowWidge1 = createRow(one_order_->order[i].name, QString::number(one_order_->order[i].store), QString::number(one_order_->order[i].price));
        scrollLayout->addWidget(rowWidge1);
        total += one_order_->order[i].price;
    }
    ui->scrollArea->widget()->setLayout(scrollLayout);
    ui->label_price->setText(QString::number(total)+"元");
}

void orderdetails::on_odreturnButton_clicked()
{
    parentWidget()->show();
    delete this;
}

