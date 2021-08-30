#ifndef CLIENTSOCKETHANDLER_H
#define CLIENTSOCKETHANDLER_H

#include <QObject>
#include <QTcpSocket>

class ClientAdapter;

typedef int QtId;
typedef std::tuple<QtId, QString> User;
typedef QList<std::tuple<QtId, QString>> Message;
typedef std::tuple<QtId, QString> SMessage;

class ClientSocketHandler : public QObject
{
    Q_OBJECT
public:
    static ClientSocketHandler* get_instance();
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

private:
    QList<QByteArray> parse_message(QByteArray msg);

private:
    explicit ClientSocketHandler(QObject *parent = nullptr);
    static ClientSocketHandler* instance;
    QTcpSocket* tcp_socket;
    ClientAdapter* adapter;
private slots:
    /**
      * 接收消息的槽
      */
    void slot_readyread();
signals:
};

inline ClientSocketHandler *ClientSocketHandler::get_instance(){
    if(instance == nullptr){
        instance = new ClientSocketHandler();
    }
    return instance;
}

#endif // CLIENTSOCKETHANDLER_H
