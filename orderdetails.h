#ifndef ORDERDETAILS_H
#define ORDERDETAILS_H

#include <QWidget>
#include "dbmanager.h"
#include <QWidget>
#include <QSqlTableModel>
#include <QMessageBox>

namespace Ui {
class orderdetails;
}

class orderdetails : public QWidget
{
    Q_OBJECT

public:
    explicit orderdetails(QWidget *parent = nullptr);
    ~orderdetails();

private slots:
    void on_odshowButton_clicked();
    void on_odreturnButton_clicked();

private:
    Ui::orderdetails *ui;
    //DbManager od_db_manager=new DbManager::getDbInstance();
};

#endif // ORDERDETAILS_H
