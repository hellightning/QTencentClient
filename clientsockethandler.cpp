#include "clientsockethandler.h"
#include "clientadapter.h"
#include <QHostAddress>
#include <QTimerEvent>
void ClientSocketHandler::set_adapter(ClientAdapter* _adapter)
{
    adapter = _adapter;
}

ClientSocketHandler::ClientSocketHandler(QObject *parent) : QObject(parent)
{
    tcp_socket = new QTcpSocket();
    QHostAddress hostaddr;
    auto [_ip, _port] = read_network_config_file();
    tcp_socket->connectToHost(QHostAddress(_ip) ,_port);
    ip = _ip; port = _port;
    qDebug() << ip << " " << port << " ";
    tcp_socket->waitForConnected(1000);
    connect(tcp_socket,&QTcpSocket::readyRead,this, &ClientSocketHandler::slot_readyread);
    socket_reconnect_timer = startTimer(5000);
}




/* clientadapter调用函数部分
 * 发送消息到server端
 */

void ClientSocketHandler::make_send_file_request(QtId from_id, QtId to_id, QString filename){
    auto check = tcp_socket->state();
    if(check == 0){
        Status stat = FAILED;
        file_byte mfile = {-1,-1,"","",QByteArray()};
        QString errmsg = "receive file command error!\nplease try later :)";
        adapter->update_receive_file_status(stat,mfile,errmsg);
    }
    else{
        QByteArray message;
        QDataStream message_stream(&message,QIODevice::WriteOnly);
        message_stream << "SEND_FILE";
        message_stream << from_id;
        message_stream << to_id;
        QFile qfile(filename);
        qfile.open(QIODevice::ReadOnly);
        QFileInfo info(qfile);
        if (qfile.size() > (1 << 8) * sizeof(quint64)) {
            adapter->update_receive_file_status(FAILED, {-1,-1,"","",QByteArray()}, "FILE IS TOO BIG");
            return;
        }
        message_stream << qfile.size();
        message_stream << info.completeSuffix();
        message_stream << info.baseName();
        qDebug() << "client have send file" << filename << info.suffix() << info.completeSuffix();
        QByteArray file_it(qfile.readAll());
        message_stream << file_it;
        qDebug() << file_it;
        tcp_socket->write(message);
    }
}
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
    qDebug() << message;
    }
}

void ClientSocketHandler::send_heart_beat_request()
{
    QByteArray msg;
    QDataStream msg_stream(&msg, QIODevice::WriteOnly);
    msg_stream << "HEART_BEAT";
    tcp_socket->write(msg);
    qDebug() << msg;
}

void ClientSocketHandler::timerEvent(QTimerEvent * e)
{
    if (e->timerId() == socket_reconnect_timer) {
        if (tcp_socket->state() == QAbstractSocket::UnconnectedState) {
            tcp_socket->connectToHost(QHostAddress(ip) ,port);
            tcp_socket->waitForConnected(1000);
            qDebug() << QString("Lost connection with server and reconnect..%1").arg(tcp_socket->state());
            if (tcp_socket->ConnectedState == QAbstractSocket::ConnectedState) {
                make_sign_request(adapter->cliend_id, adapter->password);
            }
        } else {
            send_heart_beat_request();
        }
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
    if(tmp_message.startsWith("REGISTER_FAILED")){
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
        int count1 = 0;
        message_stream >> count1;
        qDebug() << count1;
        QList<SMessage> biao;
        for (int i = 0; i < count1; ++i) {
            message_stream >> id;
            message_stream >> nickname;

            int count2 = 0;
            message_stream >> count2;
            for(int j = 0;j< count2; ++j){
                QString message;
                message_stream >> message;
                auto dui1 = std::make_tuple(id,message);
                biao.append(dui1);
            }
            auto dui = std::make_tuple(id,nickname);
            friends.append(std::make_tuple(id, nickname));
        }
        QString msg = "";
        if(count1 != 0){
            adapter->update_friend_list_status(stat,friends,msg);
            adapter->update_receive_message_status(SUCCESS,biao,"");
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
        qDebug() << id << nickname;
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
    if(tmp_message.startsWith("SEND_FILE")){
        Status stat = SUCCESS;
        file_byte mfile;
        QtId from_id;
        QtId to_id;
        unsigned long long file_size;
        QString file_type;
        QString file_name;
        QByteArray file_it;
        message_stream >> from_id;
        message_stream >> to_id;
        message_stream >> file_size;
        message_stream >> file_type;
        message_stream >> file_name;
        message_stream >> file_it;
        qDebug() << file_it;
        mfile.from_id = from_id;
        mfile.to_id = to_id;
        mfile.file_name = file_name;
        mfile.file_type = file_type;
        mfile.file_byte = file_it;
        QString errmsg = "";
        adapter->update_receive_file_status(stat,mfile,errmsg);
    }
}
