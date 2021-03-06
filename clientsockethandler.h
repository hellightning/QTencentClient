/**
 * @file clientsockethandler.h
 * @brief Client的Socket单例
 */
#ifndef CLIENTSOCKETHANDLER_H
#define CLIENTSOCKETHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include "clientlib.h"
#include <QFile>
#include <QFileInfo>

class ClientAdapter;

class ClientSocketHandler : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 获取单例对象的指针
     * @return
     */
    static ClientSocketHandler* get_instance();
    /**
     * @brief 发送文件的请求
     * @param from_id 发送者id
     * @param to_id 接收者id
     * @param filename  文件路径
     */
    void make_send_file_request(QtId from_id,QtId to_id,QString filename);
    /**
     * @brief set_adapter 设置adapter
     */
    void set_adapter(ClientAdapter*);
    /**
     * @brief 发送消息的请求
     * @param author 消息发送者
     * @param msg 消息本体
     */
    void make_send_message_request(User author, SMessage msg);
    /**
     * @brief 发送登录请求
     * @param userid 用户ID
     * @param pwd 密码
     */
    void make_sign_request(QtId userid, QString pwd);
    /**
     * @brief 发送注册请求
     * @param nickname 昵称
     * @param pwd 密码
     */
    void make_register_request(QString nickname, QString pwd);
    /**
     * @brief 获取用户信息的请求
     * @param userid 用户ID
     */
    void make_get_friends_request(QtId userid);
    /**
     * @brief 添加好友的请求
     * @param userid 用户ID
     * @param friendid 对方ID
     */
    void make_add_friend_request(QtId userid, QtId friendid);
    /**
     * @brief 心跳包
     */
    void send_heart_beat_request();

protected:
    /**
     * @brief timerEvent 计时器事件
     */
    virtual void timerEvent(QTimerEvent* e);

private:
    /**
     * @brief ClientSocketHandler Socket的构造函数
     * @param parent 父物体
     */
    explicit ClientSocketHandler(QObject *parent = nullptr);
    static ClientSocketHandler* instance; // 单例对象
    QTcpSocket* tcp_socket; // socket对象
    ClientAdapter* adapter; // adapter对象
    int socket_reconnect_timer; // 重连接的计时器
    QString ip; // ip地址
    int port; // 端口号

private slots:
    /**
      * 接收消息的槽
      */
    void slot_readyread();
signals:
};

/**
 * @brief ClientSocketHandler::get_instance 获取单例对象的指针
 * @return 单例对象的指针
 */
inline ClientSocketHandler *ClientSocketHandler::get_instance(){
    if(instance == nullptr){
        instance = new ClientSocketHandler();
    }
    return instance;
}

#endif // CLIENTSOCKETHANDLER_H
