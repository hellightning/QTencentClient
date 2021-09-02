/**
 * @file MyItemWidget.h
 * @brief 自定义好友列表控件
 */
#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include "QDebug"


namespace Ui {
class ItemWidget;
}

class MyItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyItemWidget(QWidget *parent = 0);
    ~MyItemWidget();

    /**
     * @brief SetNickAndIcon 设置头像昵称
     * @param nick           nickname
     */
    void SetNickAndIcon(QString nick);
    /**
     * @brief setQtId 设置Qid
     */
    void setQtId(int);
    /**
     * @brief getQid 获取UI界面qid
     * @return
     */
    int getQid();
    /**
     * @brief getNickName 获取昵称
     * @return
     */
    QString getNickName();
    /**
     * @brief setHasMsg 设置有未读消息标志
     */
    void setHasMsg();
    /**
     * @brief clearMsgIcon 清除未读消息标志
     */
    void clearMsgIcon();

private slots:
    /**
     * @brief setNoneMsg 清楚未读消息标志
     */
    void setNoneMsg();
    /**
     * @brief item_on_double_clicked 当前被双击
     */
    void item_on_double_clicked();
signals:
    /**
     * @brief double_cliceked_to_friendsform 当前控件被双击
     * @param item
     */
    void double_cliceked_to_friendsform(MyItemWidget* item);

private:
    Ui::ItemWidget *ui;

};

#endif // ITEMWIDGET_H
