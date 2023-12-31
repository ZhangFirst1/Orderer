#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlTableModel>
#include <QDebug>

class DbManager
{
public:
    static DbManager& getDbInstance();
    void Init();
    void getClientAll();
    void queryClient(QString name);
    void addClient(int row);
    void updateClient();
    void deleteClient(int row);

    QSqlTableModel *model;
private:
    DbManager();
};

#endif // DBMANAGER_H
