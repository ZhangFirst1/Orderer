#ifndef MYORDER_H
#define MYORDER_H

#include <QMainWindow>
#include <QLayout>
#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>
#include <QDateTime>

struct items{
    QString name;
    int num;
    double price;
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

private slots:
    void backButton_clicked();
    void myOrderButton_clicked();

private:
    int total_num_ = 0;
    items item_[50];
    Ui::MyOrder *ui;

};

#endif // MYORDER_H
