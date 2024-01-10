#include "statisticaltable.h"
#include "ui_statisticaltable.h"
#include <algorithm>
#include <QtCharts>
#include <QtWidgets>


StatisticalTable::StatisticalTable(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StatisticalTable)
{
    ui->setupUi(this);
    instance.getSales(sales);

    // 按照销量排序
    std::vector<std::pair<QString, int>> vec(sales.begin(), sales.end());
    vec.push_back(std::make_pair("红烧排骨",10));
    vec.push_back(std::make_pair("宫保鸡丁",30));
    vec.push_back(std::make_pair("鱼香肉丝",20));

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

    // 饼状图
    QPieSeries* series = new QPieSeries();
    for(int row = 0; row < vec.size(); row++){
        series->append(vec[row].first, vec[row].second);
    }
    series->setVisible(true);
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("销量统计");
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView* chartview = new QChartView(ui->salesChart);
    chartview->setChart(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(ui->salesChart);
    layout->addWidget(chartview);

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

//重写 paintEvent 函数，在这里绘制背景图
void StatisticalTable::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);

    // 获取当前窗口的大小
    QSize widgetSize = size();

    // 从文件加载背景图（这里需要替换为你的实际路径）
    QPixmap backgroundImage(":/background/cloud1.jpg");

    // 绘制背景图并进行自适应大小处理
    painter.drawPixmap(0, 0, widgetSize.width(), widgetSize.height(), backgroundImage);
}
