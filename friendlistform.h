/**
 * @file friendlist.h
 * @brief 好友列表界面实例
 */
#ifndef FRIENDLISTFORM_H
#define FRIENDLISTFORM_H

#include <QWidget>
#include<QListWidget>
#include <QMouseEvent>
#include "itemwidget.h"
#include "clientlib.h"

class ClientAdapter;

namespace Ui {
class FriendListForm;
}

class FriendListForm : public QWidget
{
    Q_OBJECT

public:
    explicit FriendListForm(QWidget *parent = nullptr);
    ~FriendListForm();
    /**
     * @brief set_qtid 刷新id
     * @param qid      当前id
     */
    void set_qtid(QtId qid);
    /**
     * @brief set_nickandicon  设置昵称头像
     * @param nick             昵称QString
     */
    void set_nickandicon(QString nick);
    /**
     * @brief set_friend_list 传送好友列表
     * @param msg             好友列表信息
     */
    void set_friend_list(QList<std::tuple<QtId, QString>> msg);
    /**
     * @brief emphasis_friend_item 标红当前好友
     * @param friendid             好友id
     */
    void emphasis_friend_item(QtId friendid);
    /**
     * @brief show_error           报错
     * @param msg                  error信息
     */
    void show_error(QString msg);
    /**
     * @brief add_friend           添加好友UI
     * @param itmlist
     */
    void add_friend(std::tuple<QtId, QString> itmlist);
    /**
     * @brief set_adapter          设置Adapter
     * @param adapter
     */
    void set_adapter(ClientAdapter* adapter);


protected:
    /**
     * @brief mousePressEvent     鼠标点击
     * @param e
     */
    virtual void mousePressEvent(QMouseEvent* e);
    /**
     * @brief mouseReleaseEvent  鼠标释放
     * @param e
     */
    virtual void mouseReleaseEvent(QMouseEvent* e);
    /**
     * @brief mouseMoveEvent    鼠标移动
     * @param e
     */
    virtual void mouseMoveEvent(QMouseEvent* e);

private slots:
    /**
     * @brief on_friendListWidget_itemDoubleClicked 点击当前好友控件
     * @param item                                  控件指针
     */
    void on_friendListWidget_itemDoubleClicked(MyItemWidget* item);
    /**
     * @brief on_pushButton_clicked 点击加好友
     */
    void on_pushButton_clicked();
    /**
     * @brief on_closebutton_clicked  点击关闭
     */
    void on_closebutton_clicked();
    /**
     * @brief on_minimizebutton_clicked
     */
    void on_minimizebutton_clicked();

private:
    /**
     * @brief add_Item_toUI 增加好友ui
     */
    void add_Item_toUI(QString,int);


private:
    Ui::FriendListForm *ui; //ui
    ClientAdapter *adapter; //adapter
    bool isDrag;            //是否拖拽
    QPoint mouse_start_point; //鼠标开始点
    QPoint window_topleft_point; //鼠标释放点
};

#endif // FRIENDLISTFORM_H
