
/**
 * @file mymsgitem.h
 * @brief 自定义消息控件
 */

#ifndef MYMSGITEM_H
#define MYMSGITEM_H
#include <QWidget>

namespace Ui {
class MyMsgItem;
}

class MyMsgItem : public QWidget
{
    Q_OBJECT

public:
    explicit MyMsgItem(QWidget *parent = nullptr);
    ~MyMsgItem();
    /**
     * @brief setData 设置消息数据
     * @param time    当前时间
     * @param nick    昵称
     * @param realMsg 消息本体
     */
    void setData(QString time,QString nick,QString realMsg);
    /**
     * @brief getHeight 获取控件UI高度
     * @return
     */
    int getHeight();
    /**
     * @brief setPosRight 是否把消息放到右边
     * @param isRight     消息当前的发送者是否是自己
     */
    void setPosRight(bool isRight);

private:
    Ui::MyMsgItem *ui; //ui
};

#endif // MYMSGITEM_H
