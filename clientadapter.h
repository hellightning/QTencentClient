#ifndef CLIENTADAPTER_H
#define CLIENTADAPTER_H
#include <QObject>
#include "chatform.h"

typedef int QtId;
class ClientAdapter : public QObject
{
    Q_OBJECT
public:
    explicit ClientAdapter(QObject *parent = nullptr);
    // static ClientAdapter* get_instance();
    void update_register_status(QtId);
    void update_sign_status();
    void update_friend_list();
    void write_message();
    void make_sign_request();
    void make_register_request();
private:
    bool is_signed = false;
    QtId cliend_id = 114514;
//     static ClientAdapter* instance; 不做单例也行
    QHash<QtId, ChatForm*> qtid_to_chatform;

signals:

};

#endif // CLIENTADAPTER_H
