#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>

// struct MyItems{
//     QString name;
//     int num;
//     double price;
// };

class TcpClient: public QTcpSocket
{
    Q_OBJECT

public:
    static TcpClient& getInstance();
    ~TcpClient();
    void Init();
    static void WriteToServer(const QString& s,const QString& type);
    static void WriteToServer(const QString& type);

public slots:
    void readFromServer();

public:
    static QTcpSocket* server;
    bool isLogin_;
    void getMenuFromServer(const QString& content);

private:
    // 使用单例模式设计
    TcpClient();


};

#endif // TCPCLIENT_H
