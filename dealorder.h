#ifndef DEALORDER_H
#define DEALORDER_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLineEdit>
#include <QValidator>
#include <Qt>
#include <QLayout>
#include <QLabel>
#include "tcpservers.h"
#include "dbmanager.h"


namespace Ui {
class dealorder;
}

class dealorder : public QWidget
{
    Q_OBJECT
    // 声明详细类是订单处理的友元类
    friend class orderdetails;
public:
    explicit dealorder(QWidget *parent = nullptr);
    ~dealorder();
    QWidget* createdealRowWidget(const QString &deallabelText1, const QString &deallabelText2, const QString &time, const int& index);
    void creatAll();

    int dealtotal_num_ = 0; // 订单总数
    OneOrder dealitem_[50];
private slots:
    void on_dealorderreturnButton_clicked();

private:
    Ui::dealorder *ui;
    TcpServers& instance = TcpServers::getInstance();
    DbManager& DbInstance = DbManager::getDbInstance();
    static unsigned long long over_orders;    // 已经处理完成的订单编号
};

#endif // DEALORDER_H
