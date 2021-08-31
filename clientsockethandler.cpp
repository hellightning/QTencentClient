#include "clientsockethandler.h"
#include "clientadapter.h"
#include <QHostAddress>
void ClientSocketHandler::set_adapter(ClientAdapter* _adapter)
{
    adapter = _adapter;
}

ClientSocketHandler::ClientSocketHandler(QObject *parent) : QObject(parent)
{
    tcp_socket = new QTcpSocket();
    QHostAddress hostaddr;
    hostaddr.setAddress("192.168.43.9");
    tcp_socket->connectToHost(QHostAddress("192.168.43.9") ,11451);
    tcp_socket->waitForConnected(1000);
    connect(tcp_socket,&QTcpSocket::readyRead,this, &ClientSocketHandler::slot_readyread);
}




/* clientadapter调用函数部分
 * 发送消息到server端
 */

/**
 * @brief make_send_message_request 发送"发送消息请求"
 * @param author    请求者id及昵称
 * @param msg   消息对象id及消息
 */
void ClientSocketHandler::make_send_message_request(User author, SMessage msg){
    auto check = tcp_socket->state();
    if(check == 0){
        Status stat = FAILED;
        QList<SMessage> message;
        message.clear();
        QString msg = "add friend command error!\n please add later :)";
        adapter->update_receive_message_status(stat,message,msg);
    }
    else{
    QByteArray message;
    QDataStream message_stream(&message,QIODevice::WriteOnly);
    message_stream << "SEND_MESSAGE";
    message_stream << std::get<0>(author);
    message_stream << std::get<0>(msg);
    message_stream << std::get<1>(msg);
    tcp_socket->write(message);
    }
}
/*
 *  发送 发送消息请求，参数为发送者id，接收者id，消息本体
 */

/**
 * @brief make_sign_request 发送"登录请求"
 * @param userid    请求者id
 * @param pwd   密码
 */
void ClientSocketHandler::make_sign_request(QtId userid, QString pwd){
    auto check = tcp_socket->state();
    if(check == 0){
        Status stat = FAILED;
        QString nickname = "";
        QString msg = "sign command error!\n please sign later :)";
        adapter-> update_sign_status(stat,nickname,msg);
    }
    else{
    qDebug() << "making sign request";
    QByteArray message;
    QDataStream message_stream(&message,QIODevice::WriteOnly);
    message_stream << "SIGN_IN";
    message_stream << userid;
    message_stream << pwd;
    tcp_socket->write(message);
    tcp_socket->flush();
    qDebug() << "message SENT.";
    }
}
/*
 *  发送 登录请求，参数为用户id，密码
 */
/**
 * @brief make_register_request 发送"注册请求"
 * @param nickname  请求者昵称
 * @param pwd   密码
 */
void ClientSocketHandler::make_register_request(QString nickname, QString pwd){
    auto check = tcp_socket->state();
    if(check == 0){
        Status stat = FAILED;
        QtId id = -1;
        QString msg = "register command error!\n please register later :)";
        adapter->update_register_status(stat,id,msg);
    }
    else{
    QByteArray message;
    QDataStream message_stream(&message,QIODevice::WriteOnly);
    message_stream << "REGISTER";
    message_stream << nickname;
    message_stream << pwd;
    qDebug() << message;
    tcp_socket->write(message);
    }
}
/*
 *  发送 注册请求，参数为用户昵称，密码
 */
/**
 * @brief make_get_friends_request  发送"获取好友列表请求"
 * @param userid    请求者id
 */
void ClientSocketHandler::make_get_friends_request(QtId userid){
    auto check = tcp_socket->state();
    if(check == 0){
        Status stat = FAILED;
        QList<std::tuple<QtId,QString>> friends;
        friends.clear();
        QString msg = "get friend list command error!\n please get later :)";
        adapter-> update_friend_list_status(stat,friends,msg);
    }
    else{
    QByteArray message;
    QDataStream message_stream(&message,QIODevice::WriteOnly);
    message_stream << "GET_FRIEND_LIST";
    message_stream << userid;
    tcp_socket->write(message);
    }
}
/*
 *  发送 获取好友列表请求，参数为用户id
 */
/**
 * @brief make_add_friend_request   发送"添加好友请求"
 * @param userid    请求者id
 * @param friendid  添加对象id
 */
void ClientSocketHandler::make_add_friend_request(QtId userid, QtId friendid){
    auto check = tcp_socket->state();
    if(check == 0){
        Status stat = FAILED;
        std::tuple<QtId, QString> mFriend;
        mFriend = std::make_tuple(-1, "");
        QString msg = "add friend command error!\n please add later :)";
        adapter-> update_add_friend_status(stat,mFriend,msg);

    }
    else{
    QByteArray message;
    QDataStream message_stream(&message,QIODevice::WriteOnly);
    message_stream << "ADD_FRIEND";
    message_stream << userid;
    message_stream << friendid;
    tcp_socket->write(message);
    }
}
/*
 *  发送 添加好友请求，参数为请求者id，好友id
 */





/* 接收server端消息
 * 调用对应adaper函数
 */
/**
 * @brief ClientSocketHandler::slot_readyread 槽函数
 */
void ClientSocketHandler::slot_readyread(){
    QByteArray message = tcp_socket->readAll();
    qDebug() << "here" << message;
    QDataStream message_stream(&message, QIODevice::ReadOnly);
    QByteArray tmp_message;
    message_stream >> tmp_message;
    tmp_message = tmp_message.trimmed();
    qDebug() << tmp_message;
    if(tmp_message.startsWith("REGISTER_SUCCEED")){
        qDebug() << "register succeed";
        Status stat = SUCCESS;
        QtId id;
        message_stream >> id;
        QString msg = "";
        adapter->update_register_status(stat,id,msg);
    }
    /**
      * 接收消息识别为注册成功，返回注册状态及用户id
      */
    if(tmp_message.startsWith("RESGISTER_FAILED")){
        qDebug() << "register failed";
        Status stat = FAILED;
        QtId id = -1;
        QString msg = "register command error!\n please register later :)";
        adapter->update_register_status(stat,id,msg);
    }
    /**
      * 接收消息识别为注册失败，返回注册状态及失败消息
      */
    if(tmp_message.startsWith("SIGN_IN_SUCCEED")){
        Status stat = SUCCESS;
        QString nickname;
        message_stream >> nickname;
        QString msg = "";
        adapter->update_sign_status(stat,nickname,msg);
    }
    /**
      * 接收消息识别为登录成功，返回登录状态及用户昵称
      */
    if(tmp_message.startsWith("SIGN_IN_FAILED")){
        Status stat = FAILED;
        QString nickname;
        message_stream >> nickname;
        QString msg = "sign command error!\n please sign later :)";
        adapter-> update_sign_status(stat,nickname,msg);
    }
    /**
      * 接收消息识别为登录失败，返回登录状态、用户昵称及失败消息
      */
    if(tmp_message.startsWith("FRIEND_LIST")){
        Status stat = SUCCESS;
        QList<std::tuple<QtId,QString>> friends;
        QString nickname;
        QtId id;
        int count = 0;
        message_stream >> count;
        qDebug() << count;
        for (int i = 0; i < count; ++i) {
            message_stream >> id;
            message_stream >> nickname;
            qDebug() <<id <<" " << nickname;
            auto dui = std::make_tuple(id,nickname);
            friends.append(std::make_tuple(id, nickname));
        }
        QString msg = "";
        if(count != 0){
            adapter->update_friend_list_status(stat,friends,msg);
        }
        else{
            stat = FAILED;
            friends.clear();
            msg = "you don't have any friends\n add someone now :)";
            adapter-> update_friend_list_status(stat,friends,msg);
        }

    }
    /**
      * 接收消息识别为获取好友列表
      * 若好友列表不为空，则返回状态为成功，并返回好友列表
      * 若好友列表为空，则返回状态为失败，并返回失败消息
      */
    if(tmp_message.startsWith("ADD_FRIEND_SUCCEED")){
        Status stat = SUCCESS;
        std::tuple<QtId, QString> mFriend;
        QtId id;
        message_stream >> id;
        QString nickname;
        message_stream >> nickname;
        mFriend = std::make_tuple(id,nickname);
        QString msg = "";
        adapter->update_add_friend_status(stat,mFriend,msg);
    }
    /**
      * 接收消息识别为添加好友，返回状态为成功，并返回好友id及昵称
      */
    if(tmp_message.startsWith("ADD_FRIEND_FAILED")){
        Status stat = FAILED;
        std::tuple<QtId, QString> mFriend;
        mFriend = std::make_tuple(-1, "");
        QString msg = "add friend command error!\n please add later :)";
        adapter-> update_add_friend_status(stat,mFriend,msg);
    }
    /**
      * 接收消息识别为添加好友，返回状态为失败，并返回失败消息
      */
    if(tmp_message.startsWith("SEND_MESSAGE")){
        Status stat = SUCCESS;
        Message message;
        QtId from_id;
        message_stream >> from_id;
        QtId to_id;
        message_stream >> to_id;
        QString transport;
        message_stream >> transport;
        qDebug() << from_id << to_id << transport;
        while (transport != nullptr) {
            auto dui = std::make_tuple(from_id,transport);
            message.append(dui);
            message_stream >> transport;
        }
        QString msg = "";
        adapter->update_receive_message_status(stat,message,msg);
    }
    /**
      * 接收消息识别为收到消息，返回状态为成功，并返回好友id及消息本体
      */
}
