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


struct dealitems{
    QString dishid;
    QString username;
};


namespace Ui {
class dealorder;
}

class dealorder : public QWidget
{
    Q_OBJECT

public:
    explicit dealorder(QWidget *parent = nullptr);
    ~dealorder();
    QWidget* createdealRowWidget(const QString &deallabelText1, const QString &deallabelText2, const QString &time);

private slots:
    void on_dealorderreturnButton_clicked();

private:
    Ui::dealorder *ui;
    TcpServers& instance = TcpServers::getInstance();
    int dealtotal_num_ = 0;
    dealitems dealitem_[50];
};

#endif // DEALORDER_H
