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
    //db.setDatabaseName("./sqlite/users.db");
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

//增加菜品
void DbManager::addMenu(int row)
{
    model->insertRow(row);
}
// 删除菜品
void DbManager::deleteMenu(int row)
{
    model->removeRow(row);
}
// 查询菜品
void DbManager::queryMenu(QString menuname){
    model->setFilter(QString("dishname='%1'").arg(menuname));
    model->select();
}
// 查询所有菜品
void DbManager::getMenuAll(){
    model->setTable("menu");
    model->select();
}
//更新菜品
void DbManager::updateMenu(){
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

// 验证用户登录
bool DbManager::verifyUser(const QString& name, const QString& pwd){
    model->setTable("client");
    model->setFilter(QString("account = '%1' AND passwd = '%2'").arg(name, pwd));
    model->select();

    if (model->rowCount() > 0) {
        return true;
    } else {
        qDebug() << "verifyUser error";
        return false;
    }
}


//将菜单发送给客户端
QString DbManager::getMenuToClient(){
    model->setTable("menu");
    model->select();
    // 获取所有行
    int rowCount = model->rowCount();
    int colCount = model->columnCount();

    QString result;
    result += QString::number(rowCount) + "@";
    for(int i=0; i < rowCount; i++){
        QSqlRecord record = model->record(i);
        for(int j=0; j < colCount; j++){
            result += record.value(j).toString() + "#";
        }
        result += "$";
    }
    if(rowCount == 0){
        return "NULL";
    }
    return result;
}

// 做菜后修改菜品库存
bool DbManager::handleOrder(QString name, int num){
    model->setTable("menu");
    model->setFilter(QString("dishname = '%1'").arg(name));
    model->select();

    if (model->rowCount() > 0) {
        // 获取第一行记录
        QSqlRecord record = model->record(0);

        // 获取菜品数量列的当前值
        int currentQuantity = record.value("store").toInt();

        if(currentQuantity < num) return false;

        // 指定需要减去的数量
        int specifiedQuantity = num;

        // 更新记录中的菜品数量
        model->setData(model->index(0, model->fieldIndex("store")), currentQuantity - specifiedQuantity);

        // 提交所有的更改到数据库
        if (model->submitAll()) {
            qDebug() << "Update successful.";
        }
    }
    return true;
}

// 注册时查询用户是否存在
bool DbManager::isexisted(const QString& name){
    //model->setTable("client");
    model->setFilter(QString("account = '%1'").arg(name));
    model->select();

    if (model->rowCount() > 0) {
        return true;
    } else {
        return false;
    }
}
void DbManager::addClientSql(const QString &name, const QString &pwd)
{
    QSqlQuery sql_query;
    QString sql = "insert into client values (?, ?)";
    sql_query.prepare(sql);
    sql_query.addBindValue(name);
    sql_query.addBindValue(pwd);
    sql_query.exec();
}
