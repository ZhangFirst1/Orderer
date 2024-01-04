#include "statisticaltable.h"
#include "ui_statisticaltable.h"
#include <algorithm>


StatisticalTable::StatisticalTable(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StatisticalTable)
{
    ui->setupUi(this);
    instance.getSales(sales);

    // 按照销量排序
    std::vector<std::pair<QString, int>> vec(sales.begin(), sales.end());

    std::sort(vec.begin(), vec.end(), [](const auto&a, const auto& b) {
        return a.second > b.second;
    });

    ui->salesWidget->setRowCount(vec.size());
    ui->salesWidget->setColumnCount(2);

    for(int row = 0; row < vec.size(); row++){
        QTableWidgetItem* itemString = new QTableWidgetItem(vec[row].first);
        QTableWidgetItem* itemValue = new QTableWidgetItem(QString::number(vec[row].second));

        ui->salesWidget->setItem(row, 0, itemString);
        ui->salesWidget->setItem(row, 1, itemValue);
    }

    ui->salesWidget->setHorizontalHeaderLabels(QStringList() << "菜品" << "销量");
    connect(ui->backButton, &QPushButton::clicked, this, &StatisticalTable::backButton_clicked);
}

StatisticalTable::~StatisticalTable()
{
    delete ui;
}

void StatisticalTable::backButton_clicked(){
    this->close();
    parentWidget()->show();
}
