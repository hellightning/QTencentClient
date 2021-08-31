#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include "mymsgitem.h"

class ClientAdapter;

typedef int QtId;
// QtId: 发送者ID，QString 发送者昵称，QString 消息体
typedef std::tuple<QtId, QString> SMessage;
namespace Ui {
class ChatForm;
}

class ChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = nullptr);
    ~ChatForm();

    void set_adapter(ClientAdapter*);
    void init_list_widget(QtId,QList<SMessage>);
    void update_list_widget(SMessage);

private slots:
    void on_sendMessageButton_clicked();

private:
    Ui::ChatForm *ui;
    ClientAdapter* adapter;
    QtId currentFriendID;
    void add_item_to_ui(QString nickName, QString realMsg,bool isMySelf);
};

#endif // CHATFORM_H
