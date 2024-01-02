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
    //菜单修改
    void getMenuAll();
    void queryMenu(QString menuname);
    void addMenu(int row);
    void updateMenu();
    void deleteMenu(int row);
    // 菜单发送给客户端
    QString getMenuToClient();
    // 登录验证
    bool verifyUser(const QString& name, const QString& pwd);

    //显示订单详情
    void getQrderdetailsAll();

    QSqlTableModel *model;
private:
    DbManager();
};

#endif // DBMANAGER_H
