#include "myorder.h"
#include "ui_myorder.h"

// 创建一行信息
QWidget *createRowWidget(const QString &labelText1, const QString &labelText2, const QString &labelText3)
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

MyOrder::MyOrder(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyOrder)
{
    ui->setupUi(this);

    connect(ui->backButton, &QPushButton::clicked, this, &MyOrder::backButton_clicked);
}

MyOrder::~MyOrder()
{
    delete ui;
}

void MyOrder::backButton_clicked(){
    this->close();
    parentWidget()->show();
}

void MyOrder::creatItem(){
    QVBoxLayout *scrollLayout = new QVBoxLayout();
    memset(item_, 0, sizeof item_);
    double total = 0.0;
    for(int i=0; i < total_num_; i++){
        QWidget* rowWidge1 = createRowWidget(item_[i].name, QString::number(item_[i].num), QString::number(item_[i].price));
        scrollLayout->addWidget(rowWidge1);
        total += item_[i].price;
    }
    ui->scrollArea->widget()->setLayout(scrollLayout);
    ui->label_total_price->setText(QString::number(total)+"元");
}
