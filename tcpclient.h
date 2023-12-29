#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>

class TcpClient
{
public:
    TcpClient();
    ~TcpClient();
    void Init();
    static void WriteToServer(const QString s);
    static void ReadFromServer(QString& s);

private:
    static QTcpSocket* server;
};

#endif // TCPCLIENT_H
