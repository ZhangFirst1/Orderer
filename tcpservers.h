#ifndef TCPSERVERS_H
#define TCPSERVERS_H
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>

class TcpServers: public QTcpServer
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

public slots:
    void newConnection();
    void readDiffFromClient();

private:
    static QTcpServer* m_server;
    static QTcpSocket* m_client;
};

#endif // TCPSERVERS_H
