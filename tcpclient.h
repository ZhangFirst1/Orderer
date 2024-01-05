#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>


class TcpClient: public QTcpSocket
{
    Q_OBJECT

public:
    static TcpClient& getInstance();
    ~TcpClient();
    void Init();
    static void WriteToServer(const QString& s,const QString& type);
    static void WriteToServer(const QString& type);
    static QTcpSocket* server;
    bool isLogin_ = false;
    bool is_done_ = false;
    bool registered = false;
    QString getMenuFromServer();

public slots:
    void readFromServer();

public:
    static QString name;

private:
    // 使用单例模式设计
    TcpClient();
    QString menu;

};

#endif // TCPCLIENT_H
