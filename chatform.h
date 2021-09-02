/**
 * @file charform.h
 * @brief 聊天ui界面实例
 * @details 与Adapter沟通
 */
#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include "mymsgitem.h"
#include <QTime>
#include <QTextEdit>
#include <QMouseEvent>
#include <QKeyEvent>

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
    /**
     * @brief set_adapter 将ClientAdapter注入到聊天窗口中
     * @param adapter adapter的指针
     */
    void set_adapter(ClientAdapter* adapter);
    /**
     * @brief init_list_widget 在打开聊天窗口时在UI刷新聊天记录
     * @param qtid             当前好友的id
     * @param msgList          具体的聊天内容 SMessage是由发送者id和具体内容组成的
     */
    void init_list_widget(QtId qtid,QList<SMessage> msgList);
    /**
     * @brief update_list_widget 在UI更新一条聊天记录
     * @param msg                SMessage
     */
    void update_list_widget(SMessage msg);
    /**
     * @brief on_get_file_succ 获取文件成功 在UI刷新通知
     * @param filename         文件名
     * @param filepath         文件路径
     */
    void on_get_file_succ(QString filename,QString filepath);

private slots:
    /**
     * @brief on_sendMessageButton_clicked 发送按钮槽
     */
    void on_sendMessageButton_clicked();
    /**
     * @brief on_sendFileBtn_clicked       发送文件按钮槽
     */
    void on_sendFileBtn_clicked();
    /**
     * @brief on_CloseButton_clicked       关闭按钮槽
     */
    void on_CloseButton_clicked();
    /**
     * @brief on_SmallButton_clicked      最小化
     */
    void on_SmallButton_clicked();

protected:
    /**
     * @brief mousePressEvent 鼠标点击行为
     * @param e
     */
    virtual void mousePressEvent(QMouseEvent* e);
    /**
     * @brief mouseReleaseEvent 鼠标放开
     * @param e
     */
    virtual void mouseReleaseEvent(QMouseEvent* e);
    /**
     * @brief mouseMoveEvent 鼠标行为
     * @param e
     */
    virtual void mouseMoveEvent(QMouseEvent* e);
    /**
     * @brief keyPressEvent 键盘敲击行为
     * @param e
     */
    virtual void keyPressEvent(QKeyEvent* e);

private:
    Ui::ChatForm *ui;   //ui
    ClientAdapter* adapter; //adapter
    QtId currentFriendID;   //当前好友id
    bool isDrag;            //是否拖拽
    QPoint mouse_start_point;//鼠标点击点
    QPoint window_topleft_point;//鼠标放开点
    /**
     * @brief add_item_to_ui 向ui加一条消息
     * @param nickName       昵称
     * @param realMsg        消息
     * @param isMySelf       是否是自己发送消息
     */
    void add_item_to_ui(QString nickName, QString realMsg,bool isMySelf);
};

#endif // CHATFORM_H
