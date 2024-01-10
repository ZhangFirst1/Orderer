#include "myorder.h"
#include "ui_myorder.h"
#include "tcpclient.h"


// 创建一行信息
QWidget *MyOrder::createRowWidget(const QString &labelText1, const QString &labelText2, const QString &labelText3, const int num)
{

    QWidget *rowWidget = new QWidget();
    QHBoxLayout *rowLayout = new QHBoxLayout(rowWidget);

    QLabel *label1 = new QLabel(labelText1);
    QLabel *label2 = new QLabel(labelText2);
    QLabel *label3 = new QLabel(labelText3);
    QPushButton *deleteButton = new QPushButton("删除");

    connect(deleteButton, &QPushButton::clicked, this, [=](){
        emit sendData(num,item_[num].name);
        item_[num].num -= 1;
        item_[num].price -= item_[num].oneprice;
        total -= item_[num].oneprice;
        label3->setText(QString::number(item_[num].price));
        ui->label_total_price->setText(QString::number(total));
        if(item_[num].num > 0)
        {
            QString curnum = QString::number(item_[num].num);
            label2->setText(curnum);
        }
        else
        {
            scrollLayout->removeWidget(rowWidget);
            delete rowWidget;
            this->total_num_--;
        }

    });

    rowLayout->addWidget(label1);
    rowLayout->addWidget(label2);
    rowLayout->addWidget(label3);
    rowLayout->addWidget(deleteButton);
    flag = false;

    rowWidget->setLayout(rowLayout);
    return rowWidget;
}

MyOrder::MyOrder(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyOrder)
{
    ui->setupUi(this);
    memset(item_, 0, sizeof item_);

    // 已经下单 再次创建时禁用下单按钮
    if(instance.has_order){
        ui->orderButton->setEnabled(false);
        ui->orderButton->setText("美味制作中");
    }

    connect(ui->backButton, &QPushButton::clicked, this, &MyOrder::backButton_clicked);
    connect(ui->orderButton, &QPushButton::clicked, this, &MyOrder::myOrderButton_clicked);
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
    for(int i=0; i < total_num_; i++){
        if(this->item_[i].num != 0){
            QWidget* rowWidge1 = createRowWidget(item_[i].name, QString::number(item_[i].num), QString::number(item_[i].price), i);
            scrollLayout->addWidget(rowWidge1);
            total += item_[i].price;
        }
    }
    ui->scrollArea->widget()->setLayout(scrollLayout);
    ui->label_total_price->setText(QString::number(total)+"元");
}

void MyOrder::myOrderButton_clicked(){
    QMessageBox::StandardButton box;
    box = QMessageBox::question(this, "提示", "确定要下单嘛?", QMessageBox::Yes|QMessageBox::No);
    if(box==QMessageBox::Yes){
        // 下单一次后在处理完成前 禁止下单
        ui->orderButton->setEnabled(false);
        ui->orderButton->setText("美味制作中");
        instance.has_order = true;
        // 加工数据传给后台
        QString order;
        QDateTime dateTime= QDateTime::currentDateTime();
        order += QString::number(total_num_) + "@" + TcpClient::name + "@" + dateTime.toString() + "@";
        for(int i=0; i<total_num_; i++){
            order += item_[i].name + "#" + QString::number(item_[i].price) + "#" + QString::number(item_[i].num) + "$";
        }
        TcpClient::WriteToServer(order, "ORDER");

        TcpClient& instance = TcpClient::getInstance();

        QEventLoop loop;
        connect(TcpClient::server, SIGNAL(readyRead()), &loop, SLOT(quit()));
        loop.exec();

        if(instance.is_order_error){
            // 发生错误
            QMessageBox::warning(this, "警告", "库存不足，请重新下单");

            // 更新MainWindows页面
            emit orderError();
        }else{
            // 订单处理成功
            if(instance.is_done_ == true){
                instance.has_order = false;
                ui->orderButton->setEnabled(true);
                ui->orderButton->setText("下单");
                QMessageBox::information(this, "取餐提醒", "请取单");

                delete ui->scrollArea->widget();
                ui->label_total_price->setText("0元");

                // 更新MainWindows页面
                emit orderError();
            }
        }
    }
}

//重写 paintEvent 函数，在这里绘制背景图
void MyOrder::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);

    // 获取当前窗口的大小
    QSize widgetSize = size();

    // 从文件加载背景图（这里需要替换为你的实际路径）
    QPixmap backgroundImage(":/background/cloud2.jpg");

    // 绘制背景图并进行自适应大小处理
    painter.drawPixmap(0, 0, widgetSize.width(), widgetSize.height(), backgroundImage);
}
