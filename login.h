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
    void registerButton_clicked();
private:
    void paintEvent(QPaintEvent *event);
    Ui::Login *ui;
};

#endif // LOGIN_H
