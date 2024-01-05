#ifndef REGISTERING_H
#define REGISTERING_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "dbmanager.h"
#include "tcpclient.h"

namespace Ui {
class Registering;
}

class Registering : public QWidget
{
    Q_OBJECT

public:
    explicit Registering(QWidget *parent = nullptr);
    ~Registering();

private slots:
    void registerButton_clicked();
    void returnButton_clicked();

private:
    Ui::Registering *ui;
    DbManager instance = DbManager::getDbInstance();
};

#endif // REGISTERING_H
