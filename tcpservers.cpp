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
    memset(order_items_, 0, sizeof order_items_);
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
    QString content = s.section(' ', 1);
    qDebug() << "Receive From Client:" << s;
    // 判断登录状态
    if(type == "LOGIN"){
        QString username = s.section(' ', 1, 1);
        QString pwd = s.section(' ', 2, 2);
        QByteArray text;

        if(db_manager.verifyUser(username, pwd)){
            text = "TRUE ";
        }
        else{
            text = "FALSE ";
        }
        m_client->write(text);
    }else if(type == "MENU"){
        sendMenuToClient();
    }else if(type == "ORDER"){
        handleOrder(content);
    }else{
        qDebug() << "暂未实现";
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

void TcpServers::handleOrder(QString& content){
    qDebug() << "handleOrder" << content;
    QString cnt_string = content.section("@", 0, 0);
    QString user_name = content.section("@", 1, 1);
    QString date = content.section("@", 2, 2);
    int cnt = cnt_string.toInt();
    order_items_[total_order_].order_num = cnt;
    content.remove(0, cnt_string.size()+user_name.size()+date.size()+3);

    // 处理分割后的信息
    for(int i=0; i < cnt; i++){
        // 菜名 价格 库存
        QString row_now = content.section("$", i, i);
        QString dish_name = row_now.section("#", 0, 0);
        double price = row_now.section("#", 1, 1).toDouble();
        int store = row_now.section("#", 2, 2).toInt();
        // db_manager.handleOrder(dish_name, store);
        order_items_[total_order_].order[i].name = dish_name;
        order_items_[total_order_].order[i].price = price;
        order_items_[total_order_].order[i].store = store;
        order_items_[total_order_].date = date;
        order_items_[total_order_].user_name = user_name;
        updateSales(dish_name, store);
    }
    total_order_++;
}

void TcpServers::sendOrderDoneToClinet(){
    QByteArray text = "ORDER_DONE ";
    m_client->write(text);
}

void TcpServers::updateSales(const QString& dishname, const int& sale){
    sales[dishname] += sale;
}
