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
};

struct OneOrder{
    int order_num;
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
    OneOrder getOneOrder(int num) { return order_items_[num]; };
    int getTotalOrderNum() { return total_order_; }

public slots:
    void newConnection();
    void readDiffFromClient();
    void handleDisconnect();

private:
    static QTcpServer* m_server;
    static QTcpSocket* m_client;
    DbManager& db_manager = DbManager::getDbInstance();
    OneOrder order_items_[20];
    int total_order_;
};

#endif // TCPSERVERS_H
