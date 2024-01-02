#include "menu.h"
#include "ui_menu.h"
#include "backend.h"
#include "dbmanager.h"

menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    ui->menutableView->setModel(menu_db_manager.model);
}

menu::~menu()
{
    delete ui;
}

void menu::on_menureturnButton_clicked()
{
    backend * back=new backend;
    back->show();
    delete this;
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
