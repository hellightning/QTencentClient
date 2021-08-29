#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>

class ClientAdapter;

typedef int QtId;
// QtId: 发送者ID，QString 发送者昵称，QString 消息体
typedef std::tuple<QtId, QString> Message;
namespace Ui {
class ChatForm;
}

class ChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = nullptr);
    ~ChatForm();

private slots:
    void on_sendMessageButton_clicked();

    void on_closeFormButton_clicked();

private:
    Ui::ChatForm *ui;
    void init_list_widget(QList<Message>);
    void update_list_widget(Message);
};

#endif // CHATFORM_H
