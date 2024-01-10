#ifndef MENU_H
#define MENU_H

#include "dbmanager.h"
#include <QWidget>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QPainter>

namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_menureturnButton_clicked();
    void on_menushowButton_clicked();
    void on_menusureButton_clicked();
    void on_menuaddButton_clicked();
    void on_menudeleteButton_clicked();
    void on_menuqueryButton_clicked();

private:
    void paintEvent(QPaintEvent *event);
    Ui::menu *ui;
    DbManager menu_db_manager = DbManager::getDbInstance();
};

#endif // MENU_H
