#include "clientdbview.h"
#include "ui_clientdbview.h"

clientdbview::clientdbview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::clientdbview)
{
    ui->setupUi(this);
    connect(ui->clientviewButton,&QPushButton::clicked,this,&clientdbview::clientview_clicked);
    connect(ui->selectButon,&QPushButton::clicked,this,&clientdbview::clientselect_clicked);
    connect(ui->addButton,&QPushButton::clicked,this,&clientdbview::clientadd_clicked);
    connect(ui->updateButton,&QPushButton::clicked,this,&clientdbview::clientupdate_clicked);
    connect(ui->deleteButton,&QPushButton::clicked,this,&clientdbview::clientdelete_clicled);
    if(this->isconnect("mydb.db"))
    {
        model = new QSqlTableModel(this);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        ui->tableView->setModel(model);
    }
}

clientdbview::~clientdbview()
{
    delete ui;
}
bool clientdbview::isconnect(QString const&dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if(!db.open())
    {
        qDebug() << "fail to connect to root SQLite";
        return false;
    }else
    {
        qDebug() << "yes";
        return true;
    }
}
void clientdbview::clientview_clicked()
{
    model->setTable("client");
    model->select();
}
void clientdbview::clientselect_clicked()
{
    QString account = ui->lineEdit->text();
    model->setFilter(QString("account='%1'").arg(account));
    model->select();
}
void clientdbview::clientadd_clicked()
{
    //获取表的行数
    int rowNum = model->rowCount();
    model->insertRow(rowNum);
}
void clientdbview::clientupdate_clicked()
{
    //开始事务操作
    model->database().transaction();
    if(model->submitAll())
    {
        model->database().commit();
    }
    else
    {
        model->database().rollback();//回滚
        //QMessageBox::warning(this,tr("tableModel"),tr("reeor:%1").arg(model->lastError().text()));
    }
}
void clientdbview::clientdelete_clicled()
{
    //获取选择的行
    int curRow = ui->tableView->currentIndex().row();
    //删除该行
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("delete warning!"),tr("Are you sure to delete this row?"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        //如果不删除，则撤销
        model->revertAll();
    }
    else
    {
        model->submitAll();
    }
}
