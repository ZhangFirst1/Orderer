#include "tcpservers.h"
#include "dbmanager.h"


QTcpServer* TcpServers::m_server;
QTcpSocket* TcpServers::m_client;

// 单例模式
TcpServers& TcpServers::getInstance(){
    static TcpServers instance;
    return instance;
}

TcpServers::TcpServers() {
    Init();
    connect(m_server, &QTcpServer::newConnection, this, &TcpServers::newConnection);
    //if(!m_client)
    //    connect(m_client, &QTcpSocket::disconnected, this, &TcpServers::handleDisconnect);
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
        connect(m_client, &QTcpSocket::readyRead, this, &TcpServers::readDiffFromClient);
    }
}

void TcpServers::handleDisconnect(){
    m_client->disconnectFromHost();
    m_client->close();
    m_client = NULL;
}

void TcpServers::ReadFromClient(QString& s){
    connect(m_client, &QTcpSocket::readyRead, [&](){
        // 接受数据
        QByteArray array = m_client->readAll();
        s = array;
    });
}

void TcpServers::readDiffFromClient(){
    DbManager db_manager = DbManager::getDbInstance();
    QByteArray array = m_client->readAll();
    QString s = array;
    QString type = s.section(' ', 0, 0);
    QString content = s.section(' ', 1, 1);
    // 判断登录状态
    if(type == "LOGIN"){
        QString username = s.section(' ', 1, 1);
        QString pwd = s.section(' ', 2, 2);
        QByteArray text;
        qDebug() << username;
        qDebug() << pwd;

        if(db_manager.verifyUser(username, pwd)){
            text = "TRUE ";
        }
        else{
            text = "FALSE ";
        }
        m_client->write(text);
    }else if(type == "MENU"){
        sendMenuToClient();
    }
}

void TcpServers::sendMenuToClient(){
    QString content = db_manager.getMenuToClient();
    QByteArray text = "MENU " + content.toUtf8();
    if(content == "NULL"){
        m_client->write("NULL");
    }else{
        m_client->write(text);
    }
}
