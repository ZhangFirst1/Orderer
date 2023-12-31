#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>
namespace Ui {
class AdminLogin;
}

class AdminLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminLogin(QWidget *parent = nullptr);
    ~AdminLogin();

private slots:
    void backButton_click();
    void loginButton_click();

private:
    Ui::AdminLogin *ui;
};

#endif // ADMINLOGIN_H
