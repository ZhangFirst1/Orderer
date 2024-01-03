#include "dealorder.h"
#include "ui_dealorder.h"
#include "backend.h"
#include "orderdetails.h"
#include "tcpservers.h"


QWidget * dealorder::createdealRowWidget(const QString &deallabelText1, const QString &deallabelText2, const QString& time)
{
    QWidget * dealrowWidget=new QWidget();
    QHBoxLayout *dealrowLayout = new QHBoxLayout(dealrowWidget);

    QLabel * deallabel1=new QLabel(deallabelText1);
    QLabel * deallabel2=new QLabel(deallabelText2);
    QLabel * deallabel3=new QLabel(time);

    QPushButton *button1 = new QPushButton();
    QPushButton *button2 = new QPushButton();
    button1->setText("详情");
    button2->setText("处理");

    dealrowLayout->addWidget(deallabel1);
    dealrowLayout->addWidget(deallabel2);
    dealrowLayout->addWidget(deallabel3);
    dealrowLayout->addWidget(button1);
    connect(button1, &QPushButton::clicked, this, [=]()
    {
        this->hide();
        orderdetails* od_db = new orderdetails(this);
        od_db->setWindowFlag(Qt::Window);
        od_db->show();

    });

    dealrowWidget->setLayout(dealrowLayout);
    return dealrowWidget;

}

dealorder::dealorder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dealorder)
{
    ui->setupUi(this);


    // 需要获取前台传输的订单
    int order_num = instance.getTotalOrderNum();

    QVBoxLayout * ScrollLayout =new QVBoxLayout();
    memset(dealitem_, 0, sizeof dealitem_);
    struct OneOrder one_order = instance.getOneOrder(0);
    QWidget * dealrowWidget1=createdealRowWidget(QString::number(0), one_order.user_name, one_order.date);
    ScrollLayout->addWidget(dealrowWidget1);
    ui->scrollArea->widget()->setLayout(ScrollLayout);
}

dealorder::~dealorder()
{
    delete ui;
}

void dealorder::on_dealorderreturnButton_clicked()
{
    backend * back=new backend;
    back->show();
    delete this;
}

