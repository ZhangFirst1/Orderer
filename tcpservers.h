#ifndef TCPSERVERS_H
#define TCPSERVERS_H
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>

class TcpServers: public QObject
{
    Q_OBJECT
public:
    TcpServers();
    ~TcpServers();
    void Init();
    static void ReadFromClient(QString& s);

public slots:
    void newConnection();

private:
    static QTcpServer* m_server;
    static QTcpSocket* m_client;
};

#endif // TCPSERVERS_H
