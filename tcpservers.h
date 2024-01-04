#ifndef TCPSERVERS_H
#define TCPSERVERS_H

#include "dbmanager.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>


struct DetailedOrder{
    QString name;
    int store;
    double price;

    void operator=(const struct DetailedOrder &d){
        name = d.name;
        store = d.store;
        price = d.price;
    }
};

struct OneOrder{
    int order_num;  // 该订单共有几个菜
    QString date;
    QString user_name;
    struct DetailedOrder order[30];
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
    void sendMenuToClient();
    void handleOrder(QString& content);
    OneOrder getOneOrder(int num) { return order_items_[num]; };    // 获取指定订单
    int getTotalOrderNum() { return total_order_; }                 // 获取订单总数
    void sendOrderDoneToClinet();                                   // 向客户端发送订单处理完成信息

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
};

#endif // TCPSERVERS_H
