#include "tcpclient.h"
#include <iostream>

QTcpSocket* TcpClient::server;

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
    // 判断连接状态
    if(server == NULL){
        std::cout << "connect failed" << std::endl;
    }else{
        std::cout << "connect success" << std::endl;
    }
}

void TcpClient::WriteToServer(const QString s){
    // 发送数据
    server->write(s.toUtf8());
}

void TcpClient::ReadFromServer(QString& s){
    // 接受数据
    QByteArray array = server->readAll();
    s = array;
}

