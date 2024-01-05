#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>



class DbManager
{
public:
    static DbManager& getDbInstance();
    void Init();
    // 用户修改
    void getClientAll();
    void queryClient(QString name);
    void addClient(int row);
    void updateClient();
    void deleteClient(int row);
    // 菜单修改
    void getMenuAll();
    void queryMenu(QString menuname);
    void addMenu(int row);
    void updateMenu();
    void deleteMenu(int row);
    // 菜单发送给客户端
    QString getMenuToClient();
    // 登录验证
    bool verifyUser(const QString& name, const QString& pwd);
    // 显示订单详情
    void getQrderdetailsAll();  
    // 做菜后修改菜品库存
    void handleOrder(QString name, int num);
    // 注册时查询用户是否存在
    bool isexisted(const QString& name);

    //用sql语句在客户表中插入数据
    void addClientSql(const QString& name, const QString& pwd);


    QSqlTableModel *model;
    QSqlQuery *query;
private:
    DbManager();
};

#endif // DBMANAGER_H
