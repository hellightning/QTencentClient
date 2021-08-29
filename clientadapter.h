/**
 * @file cilentadapter.h
 * @brief 从Client到UI的Adpater
 * @version 0.1.0
 * @date 2021/08/29
 * @author lire
 *
 * @b 修改记录：
 * @li  0828
 *     - 构建了类
 * @li 0829
 *     - 添加实现
 */
#ifndef CLIENTADAPTER_H
#define CLIENTADAPTER_H
#include <QObject>
#include "chatform.h"
#include "iohandler.h"

class RegisterForm;
class SignInForm;
class FriendListForm;

enum Status {
    SUCCESS,
    FAILED
};

typedef int QtId;
typedef std::tuple<QtId, QString> User;

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
    void update_receive_message_status(Status stat, Message msg, QString errmsg);

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

private:
    bool is_signed = false; // 是否登录
    QtId cliend_id = 114514; // 客户端id
    QString nick_name;
//     static ClientAdapter* instance; 不做单例也行
    QHash<QtId, ChatForm*> qtid_to_chatform; // qtid的信息
    QHash<QtId, QString> qtid_to_nickname;

    RegisterForm* register_form = nullptr;
    SignInForm* sign_in_form = nullptr;
    FriendListForm* friend_list_form = nullptr;
    IOHandler* io_handler = nullptr;
signals:

};

#endif // CLIENTADAPTER_H
