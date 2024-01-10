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
    static QTcpSocket* server;
    static void WriteToServer(const QString& s,const QString& type);
    static void WriteToServer(const QString& type);

    bool isLogin_ = false;          // 登录状态
    bool is_done_ = false;          // 订单处理完成
    bool registered = false;        // 注册状态
    bool is_order_error = false;    // 订单处理发生错误
    bool has_order = false;         // 是否已经下单
    QString getMenuFromServer();

public slots:
    void readFromServer();
    void handleDisconnected();

public:
    static QString name;

private:
    // 使用单例模式设计
    TcpClient();
    QString menu;

};

#endif // TCPCLIENT_H
