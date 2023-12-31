#ifndef CLIENTDBVIEW_H
#define CLIENTDBVIEW_H

#include <QWidget>
#include <QSqlTableModel>
#include <QMessageBox>
namespace Ui {
class clientdbview;
}

class clientdbview : public QWidget
{
    Q_OBJECT

public:
    explicit clientdbview(QWidget *parent = nullptr);
    ~clientdbview();
    bool isconnect(QString const&dbName);
    QSqlTableModel *model;
private slots:
    void clientview_clicked();
    void clientselect_clicked();
    void clientadd_clicked();
    void clientupdate_clicked();
    void clientdelete_clicled();
private:
    Ui::clientdbview *ui;
};

#endif // CLIENTDBVIEW_H
