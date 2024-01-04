#include "dealorder.h"
#include "ui_dealorder.h"
#include "orderdetails.h"
#include "tcpservers.h"


QWidget * dealorder::createdealRowWidget(const QString &deallabelText1, const QString &deallabelText2, const QString& time)
{
    QWidget * dealrowWidget=new QWidget();
    QHBoxLayout *dealrowLayout = new QHBoxLayout(dealrowWidget);

    QLabel * deallabel1=new QLabel(deallabelText1);
    QLabel * deallabel2=new QLabel(deallabelText2);
    QLabel * deallabel3=new QLabel(time);
    QLabel * deallabel4=new QLabel("待处理");

    QPushButton *button1 = new QPushButton();
    QPushButton *button2 = new QPushButton();
    button1->setText("详情");
    button2->setText("处理");

    dealrowLayout->addWidget(deallabel1);
    dealrowLayout->addWidget(deallabel2);
    dealrowLayout->addWidget(deallabel3);
    dealrowLayout->addWidget(button1);
    dealrowLayout->addWidget(button2);
    dealrowLayout->addWidget(deallabel4);

    connect(button1, &QPushButton::clicked, this, [=]()
    {
        this->hide();
        orderdetails* od_db = new orderdetails(this, &this->dealitem_[dealtotal_num_-1]);
        qDebug() << "Before transmit:" << this->dealitem_[dealtotal_num_-1].order[0].name;
        qDebug() << "Before transmit:" << this->dealitem_[dealtotal_num_-1].order[1].name;
        qDebug() << "Address:" << &this->dealitem_[dealtotal_num_-1];
        od_db->setWindowFlag(Qt::Window);
        od_db->creatItem();
        od_db->show();
    });

    connect(button2, &QPushButton::clicked, this, [=](){
        deallabel4->setText("已处理");
        instance.sendOrderDoneToClinet();
    });

    dealrowWidget->setLayout(dealrowLayout);
    return dealrowWidget;
}

dealorder::dealorder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dealorder)
{
    ui->setupUi(this);


}

dealorder::~dealorder()
{
    delete ui;
}

void dealorder::creatAll(){
    // 需要获取前台传输的订单
    dealtotal_num_ = instance.getTotalOrderNum();     // 共有几个订单
    QVBoxLayout * ScrollLayout =new QVBoxLayout();

    memset(dealitem_, 0, sizeof dealitem_);

    for(int i=0;i<dealtotal_num_;i++){
        dealitem_[i] = instance.getOneOrder(i);
        qDebug() << i << ' ' << dealitem_[i].user_name;
        // 接收到数据
        QWidget *dealrowWidget = createdealRowWidget(QString::number(i), dealitem_[i].user_name, dealitem_[i].date);
        ScrollLayout->addWidget(dealrowWidget);
    }

    ui->scrollArea->widget()->setLayout(ScrollLayout);
}

void dealorder::on_dealorderreturnButton_clicked()
{
    this->hide();
    parentWidget()->show();
}

