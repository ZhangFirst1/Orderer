#ifndef TCPSERVERS_H
#define TCPSERVERS_H
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>

class TcpServers
{
public:
    TcpServers();
    ~TcpServers();
    void Init();
    static void ReadFromClient(QString& s);
    void newConnection();

private:
    static QTcpServer* m_server;
    static QTcpSocket* m_client;
};

#endif // TCPSERVERS_H
