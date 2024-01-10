#ifndef STATISTICALTABLE_H
#define STATISTICALTABLE_H

#include <QWidget>
#include <map>
#include "tcpservers.h"


namespace Ui {
class StatisticalTable;
}

class StatisticalTable : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticalTable(QWidget *parent = nullptr);
    ~StatisticalTable();

private slots:
    void backButton_clicked();

private:
    void paintEvent(QPaintEvent *event);
    Ui::StatisticalTable *ui;
    std::map<QString, int> sales;
    TcpServers& instance = TcpServers::getInstance();
};

#endif // STATISTICALTABLE_H
