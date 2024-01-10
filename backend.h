#ifndef BACKEND_H
#define BACKEND_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>


namespace Ui {
class backend;
}

class backend : public QWidget
{
    Q_OBJECT

public:
    explicit backend(QWidget *parent = nullptr);
    ~backend();

private:
    void paintEvent(QPaintEvent *event);

private slots:
    void clientButton_clicked();
    void menuButton_clicked();
    void dealButton_clicked();
    void recordButton_clicked();
    void closeButton_clicked();

private:
    Ui::backend *ui;
};

#endif // BACKEND_H
