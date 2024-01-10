#include "menu.h"
#include "ui_menu.h"
#include "dbmanager.h"

menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    menu_db_manager.getMenuAll();
    ui->menutableView->setModel(menu_db_manager.model);
}

menu::~menu()
{
    delete ui;
}

void menu::on_menureturnButton_clicked()
{
    this->close();
    parentWidget()->show();
}

void menu::on_menushowButton_clicked()
{
    menu_db_manager.getMenuAll();
}

void menu::on_menusureButton_clicked()
{
    menu_db_manager.updateMenu();
}

void menu::on_menuaddButton_clicked()
{
    int rowNum=menu_db_manager.model->rowCount();
    menu_db_manager.addMenu(rowNum);
}

void menu::on_menudeleteButton_clicked()
{
    //获取选择的行
    int curRow = ui->menutableView->currentIndex().row();
    menu_db_manager.deleteMenu(curRow);
    //删除该行
    int ok = QMessageBox::warning(this,tr("delete warning!"),tr("Are you sure to delete this row?"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        //如果不删除，则撤销
        menu_db_manager.model->revertAll();
    }
    else
    {
        menu_db_manager.model->submitAll();
    }
}

void menu::on_menuqueryButton_clicked()
{
    QString menuname = ui->menulineEdit->text();
    menu_db_manager.queryMenu(menuname);
}

//重写 paintEvent 函数，在这里绘制背景图
void menu::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);

    // 获取当前窗口的大小
    QSize widgetSize = size();

    // 从文件加载背景图（这里需要替换为你的实际路径）
    QPixmap backgroundImage(":/background/cloud1.jpg");

    // 绘制背景图并进行自适应大小处理
    painter.drawPixmap(0, 0, widgetSize.width(), widgetSize.height(), backgroundImage);
}
