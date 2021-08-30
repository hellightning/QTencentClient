#include "clientsockethandler.h"
#include "clientadapter.h"
ClientSocketHandler* ClientSocketHandler::instance = nullptr;

void ClientSocketHandler::set_adapter(ClientAdapter* _adapter)
{
    adapter = _adapter;
}

ClientSocketHandler::ClientSocketHandler(QObject *parent) : QObject(parent)
{
    tcp_socket->connectToHost("ip",1);
}
/* clientadapter调用函数部分
 * 发送消息到server端
 */
void ClientSocketHandler::make_send_message_request(User author, SMessage msg){
    QByteArray message;
    QDataStream message_stream(&message,QIODevice::WriteOnly);
    message_stream << "SEND_MESSAGE";
    message_stream << std::get<0>(author);
    message_stream << std::get<0>(msg);
    message_stream << std::get<1>(msg);
    tcp_socket->write(message);
}
/*
 *  发送 发送消息请求，参数为发送者id，接收者id，消息本体
 */

void ClientSocketHandler::make_sign_request(QtId userid, QString pwd){
    QByteArray message;
    QDataStream message_stream(&message,QIODevice::WriteOnly);
    message_stream << "SIGN_IN";
    message_stream << userid;
    message_stream << pwd;
    tcp_socket->write(message);
}
/*
 *  发送 登录请求，参数为用户id，密码
 */
void ClientSocketHandler::make_register_request(QString nickname, QString pwd){
    QByteArray message;
    QDataStream message_stream(&message,QIODevice::WriteOnly);
    message_stream << "REGISTER";
    message_stream << nickname;
    message_stream << pwd;
    tcp_socket->write(message);
}
/*
 *  发送 注册请求，参数为用户昵称，密码
 */

void ClientSocketHandler::make_get_friends_request(QtId userid){
    QByteArray message;
    QDataStream message_stream(&message,QIODevice::WriteOnly);
    message_stream << "GET_FRIEND_LIST";
    message_stream << userid;
    tcp_socket->write(message);
}
/*
 *  发送 获取好友列表请求，参数为用户id
 */

void ClientSocketHandler::make_add_friend_request(QtId userid, QtId friendid){
    QByteArray message;
    QDataStream message_stream(&message,QIODevice::WriteOnly);
    message_stream << "ADD_FRIEND";
    message_stream << userid;
    message_stream << friendid;
    tcp_socket->write(message);
}
/*
 *  发送 添加好友请求，参数为请求者id，好友id
 */

/* 接收server端消息
 * 调用对应adaper函数
 */

void ClientSocketHandler::slot_readyread(){
    QByteArray message;
    tcp_socket->read(message);
    QDataStream message_stream(&message, QIODevice::ReadOnly);
    QByteArray tmp_message;
    message_stream >> tmp_message;
    if(tmp_message == "REGISTER_SUCCEED"){
        Status stat = SUCCESS;
        QtId id;
        message_stream >> id;
        QString msg = "";
        adapter->update_register_status(stat,id,msg);
    }
    /**
      * 接收消息识别为注册成功，返回注册状态及用户id
      */
    if(tmp_message == "RESGISTER_FAILED"){
        Status stat = FAILED;
        QtId id = -1;
        QString msg = "register command error!\n please register later :)";
        adapter->update_register_status(stat,-1,msg);
    }
    /**
      * 接收消息识别为注册失败，返回注册状态及失败消息
      */
    if(tmp_message == "SIGN_IN_SECCEED"){
        Status stat = SUCCESS;
        QString nickname;
        message_stream >> nickname;
        QString msg = "";
        adapter->update_sign_status(stat,nickname,msg);
    }
    /**
      * 接收消息识别为登录成功，返回登录状态及用户昵称
      */
    if(tmp_message == "SIGN_IN_FAILED"){
        Status stat = FAILED;
        QString nickname;
        message_stream >> nickname;
        QString msg = "sign command error!\n please sign later :)";
        adapter-> update_sign_status(stat,nickname,msg);
    }
    /**
      * 接收消息识别为登录失败，返回登录状态、用户昵称及失败消息
      */
    if(tmp_message == "FRIEND_LIST"){
        Status stat = SUCCESS;
        QList<std::tuple<QtId,QString>> friends;
        QString nickname;
        QtId id;
        int count = 0;
        while ((message_stream >> id) != nullptr) {
            message_stream >> nickname;
            auto dui = std::make_tuple(id,nickname);
            friends[count] = dui;
            count ++;
        }
        QString msg = "";
        if(count != 0){
            adapter->update_friend_list_status(stat,friends,msg);
        }
        else{
            stat = FAILED;
            friends.clear();
            msg = "get_friend_list command error!\n please get later :)";
            adapter-> update_friend_list_status(stat,friends,msg);
        }

    }
    /**
      * 接收消息识别为获取好友列表
      * 若好友列表不为空，则返回状态为成功，并返回好友列表
      * 若好友列表为空，则返回状态为失败，并返回失败消息
      */
    if(tmp_message == "ADD_FRIEND_SUCCEED"){
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
    if(tmp_message == "ADD_FRIEND_FAILED"){
        Status stat = FAILED;
        std::tuple<QtId, QString> mFriend;
        mFriend = std::make_tuple(-1, "");
        QString msg = "add friend command error!\n please add later :)";
        adapter-> update_add_friend_status(stat,mFriend,msg);
    }
    /**
      * 接收消息识别为添加好友，返回状态为失败，并返回失败消息
      */
    if(tmp_message == "SEND_MESSAGE"){
        Status stat = SUCCESS;
        Message message;
        QtId from_id;
        message_stream >> from_id;
        QtId to_id;
        message_stream >> to_id;
        int count = 0;
        QString transport;
        while ((message_stream >> transport) != nullptr) {
            auto dui = std::tuple(from_id,transport);
            message[count] = dui;
            count ++;
        }
        QString msg = "";
        adapter->update_receive_message_status(stat,message,msg);
    }
    /**
      * 接收消息识别为收到消息，返回状态为成功，并返回好友id及消息本体
      */
}
