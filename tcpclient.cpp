#include "tcpclient.h"
#include <iostream>

QTcpSocket* TcpClient::server;

// 单例模式
TcpClient& TcpClient::getInstance(){
    static TcpClient instance;
    return instance;
}

TcpClient::TcpClient() {
    Init();
}

// RAII
TcpClient::~TcpClient(){
    delete server;
}

void TcpClient::Init(){
    // 创建客户端Socket
    server = new QTcpSocket();
    // 连接服务器端
    server->connectToHost(QHostAddress("127.0.0.1"), 8000);
    connect(server, &QTcpSocket::readyRead, this, &TcpClient::readFromServer);

    // 判断连接状态
    if(server == NULL){
        std::cout << "connect failed" << std::endl;
    }else{
        std::cout << "connect success" << std::endl;
    }

}

void TcpClient::WriteToServer(const QString& s,const QString& type){
    // 发送数据
    server->write((type+" ").toUtf8());
    server->write(s.toUtf8());
}

void TcpClient::readFromServer(){
    QByteArray data = server->readAll();
    QString s = data;
    qDebug() << "readFromServer:" << s;
    if(s == "TRUE"){
        isLogin_ = true;
    }
}

