#include "dealorder.h"
#include "ui_dealorder.h"
#include "backend.h"
#include "orderdetails.h"

QWidget * dealorder::createdealRowWidget(const QString &deallabelText1, const QString &deallabelText2,const QString &dealbuttonText)
{
    QWidget * dealrowWidget=new QWidget();
    QHBoxLayout *dealrowLayout = new QHBoxLayout(dealrowWidget);

    QLabel * deallabel1=new QLabel(deallabelText1);
    QLabel * deallabel2=new QLabel(deallabelText2);

    QPushButton *button = new QPushButton(dealbuttonText);
    button->setText("详情");

    dealrowLayout->addWidget(deallabel1);
    dealrowLayout->addWidget(deallabel2);
    dealrowLayout->addWidget(button);
    connect(button, &QPushButton::clicked, this, [=]()
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

    QVBoxLayout * ScrollLayout =new QVBoxLayout();
    memset(dealitem_, 0, sizeof dealitem_);
    for(int i=0; i < 5; i++){
        QWidget * dealrowWidget1=createdealRowWidget("111","111","222");
        ScrollLayout->addWidget(dealrowWidget1);

    }
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

