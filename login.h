#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void loginButton_clicked();
    void adminButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
