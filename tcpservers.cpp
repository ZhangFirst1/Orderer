#include "tcpservers.h"

QTcpServer* TcpServers::m_server;
QTcpSocket* TcpServers::m_client;

TcpServers::TcpServers() {
    Init();
    newConnection();
}

TcpServers::~TcpServers() {
    delete m_server;
    delete m_client;
}

void TcpServers::Init(){
    m_server = new QTcpServer();
    // 开启监听
    m_server->listen(QHostAddress::Any, 8000);
}

void TcpServers::newConnection(){
    if(m_client == NULL){
        // 处理客户端的连接请求
        m_client = m_server->nextPendingConnection();
        // 发送数据
        m_client->write("服务器连接成功");
    }
}

void TcpServers::ReadFromClient(QString& s){
    // 接受数据
    QByteArray array = m_client->readAll();
    s = array;
}
