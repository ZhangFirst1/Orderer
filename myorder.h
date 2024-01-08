#ifndef MYORDER_H
#define MYORDER_H

#include <QMainWindow>
#include <QLayout>
#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>
#include <QDateTime>
#include "tcpclient.h"

struct items{
    QString name;
    int num;
    double price;
    double oneprice;
};


namespace Ui {
class MyOrder;
}

class MyOrder : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyOrder(QWidget *parent = nullptr);
    ~MyOrder();
    items* getItem(){ return item_; }
    int& getTotalNum() { return total_num_; }
    void creatItem();
    QWidget *createRowWidget(const QString &labelText1, const QString &labelText2, const QString &labelText3, const int num);

private slots:
    void backButton_clicked();
    void myOrderButton_clicked();

signals:
    void sendData(const int num,const QString dishname);

private:
    int total_num_ = 0; // 我的订单中菜品总数
    items item_[50];    // 我的订单中菜品
    Ui::MyOrder *ui;
    double total = 0.0; // 总价格
    bool flag = false;
    QVBoxLayout *scrollLayout = new QVBoxLayout();
    TcpClient& instance = TcpClient::getInstance();

};

#endif // MYORDER_H
