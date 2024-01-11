#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "myorder.h"
#include "tcpclient.h"


// 创建一行信息
QWidget* MainWindow::createRowWidget(const QString &labelText1, const double &labelText2, const int &labelText3, const QString &buttonText,int i)
{
    QWidget *rowWidget = new QWidget();
    QHBoxLayout *rowLayout = new QHBoxLayout(rowWidget);

    QLabel *label1 = new QLabel(labelText1);
    QLabel *label2 = new QLabel(QString::number(labelText2));
    QLabel *label3 = new QLabel(QString::number(labelText3));
    QLineEdit *le = new QLineEdit();

    curstore[i].storeLabel = label3;


    // 设置整数范围 [1, 库存量]
    le->setValidator(new QIntValidator(1, labelText3, le));
    le->setFixedHeight(20);
    le->setFixedWidth(50);
    le->setAlignment(Qt::AlignLeft);
    le->setText("1");
    // 下单按钮
    QPushButton *button = new QPushButton(buttonText);
    curstore[i].button = button;

    connect(button, &QPushButton::clicked, this, [=](){
        // 在第一次点单之前将原有数据清空
        if(this->instance.is_done_ == true){
            this->order_num_ = 0;
            memset(this->item_,0,sizeof(this->item_));
            instance.is_done_ = false;
        }

        if(le->text().toInt() > curstore[i].number)
        {
            QMessageBox::warning(this,"警告","库存不足，请重新下单");
            le->setText("1");
        }else
     {
            curstore[i].number -= le->text().toInt();
            label3->setText(QString::number(curstore[i].number));
            if(curstore[i].number==0)
            {
                button->setText("售罄");
                button->setEnabled(false);
            }


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
     }
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

    Init();

    connect(ui->myOrderButton, &QPushButton::clicked, this, &MainWindow::myOrderButton_clicked);
    connect(ui->returnButton,&QPushButton::clicked,this,&MainWindow::returnButton_clicked);
}

void MainWindow::Init(){
    if(ui->scrollArea->widget()->layout()){
        QVBoxLayout *subVBox = qobject_cast<QVBoxLayout*>(ui->scrollArea->widget()->layout());
        QLayoutItem *child;
        while ((child = subVBox->takeAt(0)) != nullptr) {
            if (QWidget *widget = child->widget()) {
                // 删除QWidget
                delete widget;
            }
        }

        delete ui->scrollArea->widget()->layout();
        ui->scrollArea->widget()->setLayout(nullptr);
        //ui->scrollArea->show();
    }

    order_num_ = 0;
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
    menuNumber = cnt;
    menu.remove(0, cnt_string.size()+1);

    QVBoxLayout *scrollLayout = new QVBoxLayout();
    for(int i=0;i<cnt;i++){
        // 菜名 价格 库存
        QString row_now = menu.section("$", i, i);
        QString dish_name = row_now.section("#", 0, 0);
        double price = row_now.section("#", 1, 1).toDouble();
        int store = row_now.section("#", 2, 2).toInt();
        //存储库存信息
        if(store){
            curstore[i].price = price;
            curstore[i].number = store;
            curstore[i].name = dish_name;

            QWidget* rowWidge1 = createRowWidget(dish_name, price , store, "下单", i);
            scrollLayout->addWidget(rowWidge1);
        }
    }
    ui->scrollArea->widget()->setLayout(scrollLayout);
}

void MainWindow::myOrderButton_clicked(){
    this->hide();
    MyOrder* order = new MyOrder(this);

    connect(order, &MyOrder::orderError, this, &MainWindow::Init);
    // 接受MyOrder类传递的删除信号
    connect(order, &MyOrder::sendData, this, [=](const int num,const QString dishname){
        this->item_[num].num -= 1;

        for(int i=0;i<menuNumber;i++){
            if(curstore[i].name == dishname)
            {
                curstore[i].number++;
                curstore[i].storeLabel->setText(QString::number(curstore[i].number));
                this->item_[num].price -= curstore[i].price;
                if(curstore[i].number > 0)
                {
                    curstore[i].button->setEnabled(true);
                    curstore[i].button->setText("下单");
                }
            }
        }
    });

    // 接受到后台订单处理完成信息
    if(instance.is_done_==false)
    {
        // 将已经点餐写入我的订单页面
        order->getTotalNum() = this->order_num_;
        for(int i=0;i<order_num_;i++){
            order->getItem()[i].name = this->item_[i].name;
            order->getItem()[i].num = this->item_[i].num;
            order->getItem()[i].price = this->item_[i].price;
            order->getItem()[i].oneprice = (this->item_[i].price / this->item_[i].num);
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

//重写 paintEvent 函数，在这里绘制背景图
void MainWindow::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);

    // 获取当前窗口的大小
    QSize widgetSize = size();

    // 从文件加载背景图（这里需要替换为你的实际路径）
    QPixmap backgroundImage(":/background/cloud2.jpg");

    // 绘制背景图并进行自适应大小处理
    painter.drawPixmap(0, 0, widgetSize.width(), widgetSize.height(), backgroundImage);
}
void MainWindow::returnButton_clicked()
{
    this->close();
    parentWidget()->show();
}


