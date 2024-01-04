#ifndef TCPSERVERS_H
#define TCPSERVERS_H

#include "dbmanager.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>
#include <map>


struct DetailedOrder{
    QString name;
    int store;
    double price;
    // 重载赋值
    void operator=(const struct DetailedOrder &d){
        name = d.name;
        store = d.store;
        price = d.price;
    }
};

struct OneOrder{
    int order_num;                  // 该订单共有几个菜
    QString date;                   // 日期
    QString user_name;              // 用户名
    struct DetailedOrder order[30]; // 菜单
};

class TcpServers: public QObject
{
    Q_OBJECT
private:
    // 单例模式
    TcpServers();
public:
    static TcpServers& getInstance();
    ~TcpServers();
    void Init();
    static void ReadFromClient(QString& s);
    void sendMenuToClient();                                        // 向前台发菜单
    void handleOrder(QString& content);                             // 处理订单
    OneOrder getOneOrder(int num) { return order_items_[num]; };    // 获取指定订单
    int getTotalOrderNum() { return total_order_; }                 // 获取订单总数
    void getSales(std::map<QString, int> &sale) { sale = this->sales;}   // 获取销量
    void sendOrderDoneToClinet();                                   // 向客户端发送订单处理完成信息
    void updateSales(const QString& dishname, const int& sale);     // 更新销量

public slots:
    void newConnection();
    void readDiffFromClient();
    void handleDisconnect();

private:
    static QTcpServer* m_server;
    static QTcpSocket* m_client;
    DbManager& db_manager = DbManager::getDbInstance();
    OneOrder order_items_[20];      // 接收到的订单信息
    int total_order_ = 0;           // 共有几个订单
    std::map<QString, int> sales;
};

#endif // TCPSERVERS_H
