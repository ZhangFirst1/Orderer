#include "clientdbview.h"
#include "ui_clientdbview.h"


clientdbview::clientdbview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::clientdbview)
{
    ui->setupUi(this);
    connect(ui->clientviewButton, &QPushButton::clicked, this, &clientdbview::clientview_clicked);
    connect(ui->selectButon, &QPushButton::clicked, this, &clientdbview::clientselect_clicked);
    connect(ui->addButton, &QPushButton::clicked, this, &clientdbview::clientadd_clicked);
    connect(ui->updateButton, &QPushButton::clicked, this, &clientdbview::clientupdate_clicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &clientdbview::clientdelete_clicked);
    connect(ui->backButton, &QPushButton::clicked, this, &clientdbview::client_back_clicked);
    db_manager.getClientAll();
    ui->tableView->setModel(db_manager.model);
}

clientdbview::~clientdbview()
{
    delete ui;
}

void clientdbview::clientview_clicked()
{
    db_manager.getClientAll();
}
void clientdbview::clientselect_clicked()
{
    QString name = ui->lineEdit->text();
    db_manager.queryClient(name);
}
void clientdbview::clientadd_clicked()
{
    //获取表的行数
    int rowNum = db_manager.model->rowCount();
    db_manager.addClient(rowNum);

}
void clientdbview::clientupdate_clicked()
{
    db_manager.updateClient();
}
void clientdbview::clientdelete_clicked()
{
    //获取选择的行
    int curRow = ui->tableView->currentIndex().row();
    db_manager.deleteClient(curRow);
    //删除该行
    int ok = QMessageBox::warning(this,tr("delete warning!"),tr("Are you sure to delete this row?"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        //如果不删除，则撤销
        db_manager.model->revertAll();
    }
    else
    {
        db_manager.model->submitAll();
    }
}

void clientdbview::client_back_clicked(){
    this->hide();
    parentWidget()->show();
}

//重写 paintEvent 函数，在这里绘制背景图
void clientdbview::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);

    // 获取当前窗口的大小
    QSize widgetSize = size();

    // 从文件加载背景图（这里需要替换为你的实际路径）
    QPixmap backgroundImage(":/background/cloud1.jpg");

    // 绘制背景图并进行自适应大小处理
    painter.drawPixmap(0, 0, widgetSize.width(), widgetSize.height(), backgroundImage);
}
