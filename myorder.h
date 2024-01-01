#ifndef MYORDER_H
#define MYORDER_H

#include <QMainWindow>
#include <QLayout>
#include <QMainWindow>
#include <QLabel>

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

private:
    void backButton_clicked();
    int total_num_ = 0;
    items item_[50];

private:
    Ui::MyOrder *ui;

};

#endif // MYORDER_H
