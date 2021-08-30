#include "clientsockethandler.h"
#include "clientadapter.h"

void ClientSocketHandler::set_adapter(ClientAdapter* _adapter)
{
    adapter = _adapter;
}

ClientSocketHandler::ClientSocketHandler(QObject *parent) : QObject(parent)
{

}
/* clientadapter调用函数部分
 * 发送消息到server端
 */
void ClientSocketHandler::make_send_message_request(User author, SMessage msg){

}

void ClientSocketHandler::make_sign_request(QtId userid, QString pwd){

}

void ClientSocketHandler::make_register_request(QString nickname, QString pwd){

}

void ClientSocketHandler::make_get_friends_request(QtId userid){

}

void ClientSocketHandler::make_add_friend_request(QtId userid, QtId friendid){

}

/* 接收server端消息
 * 调用对应adaper函数
 */

QList<QByteArray> ClientSocketHandler::parse_message(QByteArray msg){
    return msg.split('\n');
}


void ClientSocketHandler::slot_readyread(){
    QByteArray databyte = tcp_socket->readAll();
    QList<QByteArray> p_databyte = parse_message(databyte);
    QString tmp_message = p_databyte.at(0);
    if(tmp_message == "REGISTER_SUCCEED"){
        Status stat = SUCCESS;
        QByteArray mid = p_databyte.at(1);
        QtId id = mid.toInt();
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
        QString nickname = p_databyte.at(1);
        QString msg = "";
        adapter->update_sign_status(stat,nickname,msg);
    }
    /**
      * 接收消息识别为登录成功，返回登录状态及用户昵称
      */
    if(tmp_message == "SIGN_IN_FAILED"){
        Status stat = FAILED;
        QString nickname = p_databyte.at(1);
        QString msg = "sign command error!\n please sign later :)";
        adapter-> update_sign_status(stat,nickname,msg);
    }
    /**
      * 接收消息识别为登录失败，返回登录状态、用户昵称及失败消息
      */
    if(tmp_message == "FRIEND_LIST"){
        Status stat = SUCCESS;
        QList<std::tuple<QtId,QString>> friends;
        int num = 1,count = 0;
        while (p_databyte.at(num) != nullptr) {
            QByteArray mid = p_databyte.at(num);
            QtId id = mid.toInt();
//            QString nickname = p_databyte(num+1);
//            auto dui = std::make_tuple(id,nickname);
//            friends[count] = dui;
            count ++;
            num += 2;
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
        QByteArray mid = p_databyte.at(1);
        QtId id = mid.toInt();
        QString nickname = "";
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
        QByteArray mid = p_databyte.at(2);
        QtId id = mid.toInt();
        int num = 3,count = 0;
        while (p_databyte.at(num) != nullptr) {
            QString transport = p_databyte.at(num);
            auto dui = std::tuple(id,transport);
            message[count] = dui;
            count ++;
            num ++;
        }
        QString msg = "";
        adapter->update_receive_message_status(stat,message,msg);
    }
    /**
      * 接收消息识别为收到消息，返回状态为成功，并返回好友id及消息本体
      */
}
