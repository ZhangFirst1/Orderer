#include "dbmanager.h"

DbManager& DbManager::getDbInstance(){
    static DbManager instance;
    return instance;
}

DbManager::DbManager() {
    Init();
    model = new QSqlTableModel();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void DbManager::Init(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydb.db");
    if(!db.open())
    {
        qDebug() << "fail to connect to root SQLite";
    }else
    {
        qDebug() << "connect to DB successfully";
    }
}

// 增加用户
void DbManager::addClient(int row){
    model->insertRow(row);
}
// 删除用户
void DbManager::deleteClient(int row){
    model->removeRow(row);
}
// 查询用户
void DbManager::queryClient(QString name){
    model->setFilter(QString("account='%1'").arg(name));
    model->select();
}
// 查询所有用户
void DbManager::getClientAll(){
    model->setTable("client");
    model->select();
}
// 更改用户
void DbManager::updateClient(){
    //开始事务操作
    model->database().transaction();
    if(model->submitAll())
    {
        model->database().commit();
    }
    else
    {
        model->database().rollback();//回滚
    }
}

