#ifndef TCPSERVERS_H
#define TCPSERVERS_H

#include "dbmanager.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>


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

public slots:
    void newConnection();
    void readDiffFromClient();
    void handleDisconnect();

private:
    static QTcpServer* m_server;
    static QTcpSocket* m_client;
    DbManager& db_manager = DbManager::getDbInstance();
};

#endif // TCPSERVERS_H
