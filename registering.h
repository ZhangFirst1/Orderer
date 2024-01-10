#ifndef REGISTERING_H
#define REGISTERING_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPainter>
#include "dbmanager.h"

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
    void paintEvent(QPaintEvent *event);
    Ui::Registering *ui;
    DbManager instance = DbManager::getDbInstance();
};

#endif // REGISTERING_H
