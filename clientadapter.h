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

class RegisterForm;
class SignInForm;
class FriendListForm;

typedef int QtId;
class ClientAdapter : public QObject
{
    Q_OBJECT
public:
    explicit ClientAdapter(QObject *parent = nullptr);
    // static ClientAdapter* get_instance();
    /**
     * @brief 更新注册状态
     * @param 用户id
     */
    void update_register_status(QtId);
    /**
     * @brief 更新登陆状态
     */
    void update_sign_status();
    /**
     * @brief 更新好友列表
     */
    void update_friend_list();
    /**
     * @brief 显示消息
     */
    void write_message();
    /**
     * @brief 发送登录请求
     */
    void make_sign_request(int, QString);
    /**
     * @brief 发送注册请求
     */
    void make_register_request(QString, QString);

private:
    bool is_signed = false; // 是否登录
    QtId cliend_id = 114514; // 客户端id
//     static ClientAdapter* instance; 不做单例也行
    QHash<QtId, ChatForm*> qtid_to_chatform; // qtid的信息

    RegisterForm* register_form = nullptr;
    SignInForm* sign_in_form = nullptr;
    FriendListForm* friend_list_form = nullptr;

signals:

};

#endif // CLIENTADAPTER_H
