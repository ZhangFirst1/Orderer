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
#include <QLabel>
#include <QPushButton>

struct MyItems{
    QString name;
    int num;
    double price; //点的一种菜品的总价和
};
struct Menustore{
    QString name;
    int number;
    double price;
    QLabel * storeLabel;
    QPushButton * button;
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


    QWidget* createRowWidget(const QString &labelText1, const double &labelText2, const int &labelText3, const QString &buttonText,int i);

signals:
    void triggerInit();

private slots:
    void myOrderButton_clicked();
    void Init();


private:
    Ui::MainWindow *ui;
    int order_num_;     // 已经点单的菜的种类
    MyItems item_[50];
    TcpClient& instance = TcpClient::getInstance();
    Menustore curstore[50];
    int menuNumber = 0; // 菜单中一共有多少道菜
    bool flag = false;  // 用于防止接收到订单完成信息后 在点击我的订单前下单后 所点内容被点击我的订单后清空的问题
};
#endif // MAINWINDOW_H
