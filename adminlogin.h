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
    // 管理员是否已经登录
    bool IsAdmin(){ return isAdmin; }

private slots:
    void backButton_click();
    void loginButton_click();

private:
    Ui::AdminLogin *ui;
    bool isAdmin;
};

#endif // ADMINLOGIN_H
