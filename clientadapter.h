/**
 * @file clientadapter.h
 * @brief 从Client到UI的Adpater
 * @version 0.1.0
 * @date 2021/08/29
 * @author lire
 */
#ifndef CLIENTADAPTER_H
#define CLIENTADAPTER_H
#include <QObject>
#include <QFuture>
#include "chatform.h"
#include "iohandler.h"
#include "clientlib.h"

class RegisterForm;
class SignInForm;
class FriendListForm;

enum Status {
    SUCCESS,
    FAILED
};

class ClientAdapter : public QObject
{
    Q_OBJECT
public:
    explicit ClientAdapter(QObject *parent = nullptr);
    // static ClientAdapter* get_instance();

    ////////////////////////////////////////////////////
    /// Server -> UI
    ////////////////////////////////////////////////////

    /**
     * @brief 更新注册状态
     * @param stat 状态
     * @param id 用户id，不成功返回-1
     * @param errmsg 不成功返回的信息
     */
    void update_register_status(Status stat, QtId id, QString errmsg = "");
    /**
     * @brief 更新登陆状态
     * @param stat 状态
     * @param nickname 昵称
     * @param errmsg 不成功返回的信息
     */
    void update_sign_status(Status stat, QString nickname, QString errmsg = "");

    /**
     * @brief 更新好友列表
     * @param stat 状态
     * @param friends 好友列表
     * @param errmsg 错误信息
     */
    void update_friend_list_status(Status stat, QList<std::tuple<QtId, QString>> friends, QString errmsg = "");
    /**
     * @brief 添加好友
     * @param stat 状态
     * @param mFriend 好友信息
     * @param errmsg 错误信息
     */
    void update_add_friend_status(Status stat, std::tuple<QtId, QString> mFriend, QString errmsg = "");

    /**
     * @brief 接收到消息
     * @param stat 状态
     * @param msg 消息
     * @param errmsg 错误信息
     */
    void update_receive_message_status(Status stat, QList<SMessage> msg, QString errmsg);

    /**
     * @brief 接收到文件
     * @param stat 状态
     * @param mfile 文件
     * @param errmsg 错误信息
     */
    void update_receive_file_status(Status stat, file_byte mfile, QString errmsg);

    ///////////////////////////////////////////////////
    /// UI -> Server
    ///////////////////////////////////////////////////

    /**
     * @brief 发送消息的请求
     * @param author 消息发送者
     * @param msg 消息本体
     */
    void send_message(QtId friendId, QString msg);
    /**
     * @brief 打开注册界面
     */
    void open_register_form();
    /**
     * @brief 发送登录请求
     * @param userid 用户ID
     * @param pwd 密码
     */
    void sign_in(QtId userid, QString pwd);
    /**
     * @brief 发送注册请求
     * @param nickname 昵称
     * @param pwd 密码
     */
    void make_register(QString nickname, QString pwd);
    /**
     * @brief 添加好友的请求
     * @param userid 用户ID
     * @param friendid 对方ID
     */
    void add_friend(QtId friendID);

    /**
     * @brief 双击之后打开
     * @param friendID 好友ID
     */
    void open_chatform(QtId friendID);
    /**
     * @brief 关闭消息界面
     * @param friendID 好友ID
     */
    void close_chatform(QtId friendID);
    /**
     * @brief 取消注册
     */
    void cancel_register();
    /**
     * @brief 发送文件
     * @param 好友ID
     * @param 文件目录
     */
    void send_file(QtId friendID, QString fileDir);

public:
    QtId cliend_id = 114514; // 客户端id
    QString nick_name; // 昵称
    QString password; // 密码
    QHash<QtId, ChatForm*> qtid_to_chatform; // qtid到窗口的hash
    QHash<QtId, QString> qtid_to_nickname; // qtid到昵称的hash
    FriendListForm* friend_list_form = nullptr; // 好友列表的窗体

private:
    bool is_signed = false; // 是否登录


    QHash<QtId, QList<SMessage>> qtid_to_msglist; // qtid到消息的队列

    RegisterForm* register_form = nullptr; // qtid到注册状态的队列
    SignInForm* sign_in_form = nullptr;  // qtid到登陆状态的队列

    IOHandler* io_handler = nullptr; // 文件管理类的指针

    QFutureWatcher<void>* file_rs_watcher; // 文件异步观察

signals:


private slots:


};

#endif // CLIENTADAPTER_H
