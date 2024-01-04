#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "myorder.h"
#include "tcpclient.h"


// 创建一行信息
QWidget* MainWindow::createRowWidget(const QString &labelText1, const double &labelText2, const int &labelText3, const QString &buttonText)
{
    QWidget *rowWidget = new QWidget();
    QHBoxLayout *rowLayout = new QHBoxLayout(rowWidget);

    QLabel *label1 = new QLabel(labelText1);
    QLabel *label2 = new QLabel(QString::number(labelText2));
    QLabel *label3 = new QLabel(QString::number(labelText3));
    QLineEdit *le = new QLineEdit();
    // 设置整数范围 [1, 库存量]
    le->setValidator(new QIntValidator(1, labelText3, le));
    le->setFixedHeight(20);
    le->setFixedWidth(50);
    le->setAlignment(Qt::AlignLeft);
    le->setText("1");
    // 下单按钮
    QPushButton *button = new QPushButton(buttonText);
    connect(button, &QPushButton::clicked, this, [=](){
        bool flag = false;
        qDebug() << order_num_;
        for(int i=0;i<order_num_;i++){
            if(item_[i].name == labelText1){
                this->item_[i].num += le->text().toInt();
                this->item_[i].price += labelText2 * le->text().toInt();
                flag = true;
                break;
            }
        }
        if(!flag){
            this->item_[order_num_].name = labelText1;
            this->item_[order_num_].num = le->text().toInt();
            this->item_[order_num_].price = labelText2 * le->text().toInt();
            order_num_++;
        }

        le->setText("1");
    });

    rowLayout->addWidget(label1);
    rowLayout->addWidget(label2);
    rowLayout->addWidget(label3);
    rowLayout->addWidget(le);
    rowLayout->addWidget(button);

    rowWidget->setLayout(rowLayout);
    return rowWidget;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    order_num_ = 0;
    QVBoxLayout *scrollLayout = new QVBoxLayout();
    // 从后端获取数据

    if(TcpClient::server == NULL){
        qDebug() << "NULL";
    }else{
        TcpClient::WriteToServer("MENU");
    }
    // 在事件循环中等待响应
    QEventLoop loop;
    connect(TcpClient::server, SIGNAL(readyRead()), &loop, SLOT(quit()));
    loop.exec();

    QString menu = instance.getMenuFromServer();
    QString cnt_string = menu.section("@", 0, 0);
    int cnt = cnt_string.toInt();
    menu.remove(0, cnt_string.size()+1);

    for(int i=0;i<cnt;i++){
        // 菜名 价格 库存
        QString row_now = menu.section("$", i, i);
        QString dish_name = row_now.section("#", 0, 0);
        double price = row_now.section("#", 1, 1).toDouble();
        int store = row_now.section("#", 2, 2).toInt();

        QWidget* rowWidge1 = createRowWidget(dish_name, price , store, "下单");
        scrollLayout->addWidget(rowWidge1);
    }
    ui->scrollArea->widget()->setLayout(scrollLayout);

    connect(ui->myOrderButton, &QPushButton::clicked, this, &MainWindow::myOrderButton_clicked);
}

void MainWindow::myOrderButton_clicked(){
    this->hide();
    MyOrder* order = new MyOrder(this);
    if(instance.is_done_==false)
    {
        order->getTotalNum() = this->order_num_;
        for(int i=0;i<order_num_;i++){
            order->getItem()[i].name = this->item_[i].name;
            order->getItem()[i].num = this->item_[i].num;
            order->getItem()[i].price = this->item_[i].price;
        }
    }else
    {
        this->order_num_ = 0;
        memset(this->item_,0,sizeof(this->item_));
        instance.is_done_ = false;
    }
    order->creatItem();
    order->show();
}


MainWindow::~MainWindow()
{
    delete ui;
}

