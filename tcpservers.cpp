#include "tcpservers.h"
#include "dbmanager.h"


QTcpServer* TcpServers::m_server;
// QTcpSocket* TcpServers::m_client = nullptr;

// 单例模式
TcpServers& TcpServers::getInstance(){
    static TcpServers instance;
    return instance;
}

TcpServers::TcpServers() {
    Init();
    connect(m_server, &QTcpServer::newConnection, this, &TcpServers::newConnection);
}

TcpServers::~TcpServers() {
    // 确保断开socket连接，停止服务器监听
    if(m_client != nullptr){
        if(m_client->state() == QAbstractSocket::ConnectedState)
            m_client->disconnectFromHost(); // 断开与客户端的连接
    }
    if(m_server->isListening()){
        m_server->close();                  // 停止网络监听
    }
    delete m_server;
    delete m_client;
    delete tmp_socket;
    socket_list.clear();
}

void TcpServers::Init(){
    memset(order_items_, 0, sizeof order_items_);
    m_server = new QTcpServer();
    // 开启监听
    m_server->listen(QHostAddress::Any, 8000);
}


void TcpServers::newConnection(){
    m_client = new QTcpSocket();
    m_client = m_server->nextPendingConnection();
    // 加入列表
    socket_list.append(m_client);
    connect(m_client, &QTcpSocket::readyRead, this, &TcpServers::readDiffFromClient);
    connect(m_client, &QTcpSocket::connected, this, &TcpServers::handleConnected);
    handleConnected();  // 运行一次槽函数显示状态
    connect(m_client, &QTcpSocket::disconnected, this, &TcpServers::handleDisconnect);
}

void TcpServers::handleDisconnect(){

    for (QList<QTcpSocket*>::iterator it = socket_list.begin(); it != socket_list.end(); ) {
        // 获取当前迭代器指向的QTcpSocket
        QTcpSocket *currentSocket = *it;

        // 判断QTcpSocket的连接状态是否为断开
        if (currentSocket->state() == QAbstractSocket::UnconnectedState) {
            // 如果连接已断开，则删除该项
            it = socket_list.erase(it);
            qDebug() << "Socket disconnected and removed from the list.";
            qDebug() << socket_list.size();
        } else {
            // 如果连接没有断开，则继续遍历下一项
            ++it;
        }
    }

    m_client->deleteLater();
}

void TcpServers::handleConnected(){
    qDebug() << "**client socket connected**";
    qDebug() << "**peer address:" << m_client->peerAddress().toString();
    qDebug() << "**peer port:" << QString::number(m_client->peerPort());
}

void TcpServers::readDiffFromClient(){
    DbManager db_manager = DbManager::getDbInstance();

    QByteArray array;
    // 遍历所有连接的Socket，若该端口收到数据则做出相应
    // 该部分可以用多线程 待更改

    for(int i = 0; i < socket_list.count(); i++){

        tmp_socket = socket_list.at(i);
        array = tmp_socket->readAll();

        if(array.length() != 0){
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
                // 为socket设置属性为用户名，标识socket
                socket_list.at(i)->setProperty("username", username);
                tmp_socket->write(text);
                qDebug() << "设置该连接的属性名为" << username;
                //m_client->write(text);

            }else if(type == "MENU"){
                sendMenuToClient();
            }else if(type == "ORDER"){
                handleOrder(content);
            }else if(type == "REGISTER"){
                QString username = s.section(' ', 1, 1);
                QString pwd = s.section(' ', 2, 2);
                QByteArray registerText;
                qDebug() << username;

                bool ret = db_manager.isexisted(username);
                if(ret==true){
                    registerText = "NO ";
                }
                else{
                    registerText = "OK ";
                    db_manager.addClientSql(username,pwd);
                }
                m_client->write(registerText);
            }

        }
    }
}

void TcpServers::sendMenuToClient(){
    QString content = db_manager.getMenuToClient();
    QByteArray text = "MENU " + content.toUtf8();
    if(content == "NULL"){
        tmp_socket->write("NULL");
    }else{
        tmp_socket->write(text);
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

    bool flag = true;
    // 第一次现判断是否所有的菜数量都足够
    for(int i=0; i < cnt;i++){
        QString row_now = content.section("$", i, i);
        QString dish_name = row_now.section("#", 0, 0);
        double price = row_now.section("#", 1, 1).toDouble();
        int store = row_now.section("#", 2, 2).toInt();

        int db_store = db_manager.queryStoreByDish(dish_name);
        if(db_store < store){   // 不满足
            flag = false;
            break;
        }
    }

    if(flag){
        for(int i=0; i < cnt; i++){
            // 菜名 价格 库存
            QString row_now = content.section("$", i, i);
            QString dish_name = row_now.section("#", 0, 0);
            double price = row_now.section("#", 1, 1).toDouble();
            int store = row_now.section("#", 2, 2).toInt();

            if(db_manager.handleOrder(dish_name, store)){
                order_items_[total_order_].order[i].name = dish_name;
                order_items_[total_order_].order[i].price = price;
                order_items_[total_order_].order[i].store = store;
                order_items_[total_order_].date = date;
                order_items_[total_order_].user_name = user_name;

                updateSales(dish_name, store);
            }
        }
        total_order_++; // 总订单数+1
    }else{
        for(auto it: socket_list){
            qDebug() << it->property("username").toString();
            if(it->property("username") == user_name){
                it->write("ORDER_ERROR");
            }
        }
    }
}

void TcpServers::sendOrderDoneToClinet(const QString& username){
    QByteArray text = "ORDER_DONE ";

    // 遍历找到要发送信息的客户端
    for(auto it: socket_list){
        qDebug() << it->property("username").toString();
        if(it->property("username") == username){
            it->write(text);
        }
    }
}

void TcpServers::updateSales(const QString& dishname, const int& sale){
    sales[dishname] += sale;
}
