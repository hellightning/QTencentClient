#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include "mymsgitem.h"
#include <QTime>
<<<<<<< HEAD
#include <QTextEdit>
=======
#include <QMouseEvent>
#include <QKeyEvent>
>>>>>>> 105c0b07fedb26c5c13485af4b32b30c3be8e428

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
    void on_get_file_succ(QString,QString);

private slots:
    void on_sendMessageButton_clicked();
    void on_sendFileBtn_clicked();

    void on_CloseButton_clicked();

    void on_SmallButton_clicked();

protected:
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);

    virtual void keyPressEvent(QKeyEvent* e);

private:
    Ui::ChatForm *ui;
    ClientAdapter* adapter;
    QtId currentFriendID;
    bool isDrag;
    QPoint mouse_start_point;
    QPoint window_topleft_point;
    void add_item_to_ui(QString nickName, QString realMsg,bool isMySelf);
};

#endif // CHATFORM_H
