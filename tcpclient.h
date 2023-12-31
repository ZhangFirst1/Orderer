#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>

enum type{
    LOGIN,
};

class TcpClient: public QTcpSocket
{
    Q_OBJECT

public:
    static TcpClient& getInstance();
    ~TcpClient();
    void Init();
    static void WriteToServer(const QString& s,const QString& type);

public slots:
    void readFromServer();

public:
    static QTcpSocket* server;
    bool isLogin_;

private:
    // 使用单例模式设计
    TcpClient();


};

#endif // TCPCLIENT_H
