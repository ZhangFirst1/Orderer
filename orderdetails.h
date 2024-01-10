#ifndef ORDERDETAILS_H
#define ORDERDETAILS_H

#include <QWidget>
#include <QWidget>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QPainter>
#include "dealorder.h"


namespace Ui {
class orderdetails;
}

class orderdetails : public QWidget
{
    Q_OBJECT

public:
    explicit orderdetails(QWidget *parent = nullptr);
    explicit orderdetails(QWidget *parent = nullptr, struct OneOrder* one_order=NULL);
    ~orderdetails();
    void creatItem();

private slots:
    void on_odreturnButton_clicked();

private:
    void paintEvent(QPaintEvent *event);
    Ui::orderdetails *ui;
    int id;
    struct OneOrder* one_order_;
};

#endif // ORDERDETAILS_H
