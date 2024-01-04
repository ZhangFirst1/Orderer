#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QGridLayout>
#include <QLineEdit>
#include <QString>
#include <QValidator>
#include <Qt>
#include "tcpclient.h"

struct MyItems{
    QString name;
    int num;
    double price;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QWidget* createRowWidget(const QString &labelText1, const double &labelText2, const int &labelText3, const QString &buttonText);

private slots:
    void myOrderButton_clicked();

private:
    Ui::MainWindow *ui;
    int order_num_;
    MyItems item_[50];
    TcpClient& instance = TcpClient::getInstance();
};
#endif // MAINWINDOW_H
