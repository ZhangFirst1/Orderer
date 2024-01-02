#ifndef CLIENTDBVIEW_H
#define CLIENTDBVIEW_H


#include "dbmanager.h"
#include <QWidget>
#include <QSqlTableModel>
#include <QMessageBox>
namespace Ui {
class clientdbview;
}

class clientdbview : public QWidget
{
    Q_OBJECT

public:
    explicit clientdbview(QWidget *parent = nullptr);
    ~clientdbview();

    bool isconnect(QString const&dbName);


private slots:
    void clientview_clicked();
    void clientselect_clicked();
    void clientadd_clicked();
    void clientupdate_clicked();
    void clientdelete_clicked();
    void client_back_clicked();

    //void on_updateButton_clicked();

private:
    Ui::clientdbview *ui;
    DbManager db_manager = DbManager::getDbInstance();
};

#endif // CLIENTDBVIEW_H
