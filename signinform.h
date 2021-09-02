/**
 * @file signinform.h
 * @brief 登录界面的托管类
 * @details 维护了登陆界面的UI
 */
#ifndef SIGNINFORM_H
#define SIGNINFORM_H

#include <QWidget>
#include <QMouseEvent>
class ClientAdapter;
typedef int QtId;
namespace Ui {
class SignInForm;
}
/**
 * @brief 登录UI类
 */
class SignInForm : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief SignInForm 构造函数
     * @param parent 父物体
     */
    explicit SignInForm(QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~SignInForm();

    /**
     * @brief get_qtid 获取qtid
     * @return 获取qtid
     */
    QtId get_qtid();
    /**
     * @brief set_qtid 设置qtid
     * @return 设置qtid
     */
    void set_qtid(QtId);
    /**
     * @brief get_password 获取password
     * @return password结果
     */
    QString get_password();
    /**
     * @brief set_adapter 设置adapter
     * @param adapter adapter
     */
    void set_adapter(ClientAdapter*);
    /**
     * @brief show_alert 显示警告框
     * @param msg 消息
     */
    void show_alert(QString msg);
    /**
     * @brief failed_sign 登陆失败的回调
     * @param msg 消息
     */
    void failed_sign(QString msg);
    /**
     * @brief changeIcon 改变Icon
     * @param icon icon的id
     */
    void changeIcon(int icon);

protected:
    /**
     * @brief mousePressEvent 按下鼠标的回调
     * @param e 事件
     */
    virtual void mousePressEvent(QMouseEvent* e);
    /**
     * @brief mouseReleaseEvent 松开鼠标的回调
     * @param e 事件
     */
    virtual void mouseReleaseEvent(QMouseEvent* e);
    /**
     * @brief mouseMoveEvent 移动鼠标的回调
     * @param e 事件
     */
    virtual void mouseMoveEvent(QMouseEvent* e);

private slots:
    /**
     * @brief on_signInPushButton_clicked 按下登录按键的槽函数
     */
    void on_signInPushButton_clicked();
    /**
     * @brief on_registerPushButton_clicked 按下注册按键的槽函数
     */
    void on_registerPushButton_clicked();
    /**
     * @brief on_CloseButton_clicked 按下关闭按键的槽函数
     */
    void on_CloseButton_clicked();
    /**
     * @brief on_SmallButton_clicked 按下最小化按键的槽函数
     */
    void on_SmallButton_clicked();

private:
    Ui::SignInForm *ui; // ui的指针
    ClientAdapter* adapter; // adapter的指针
    bool isDrag; // 是否在被拖拽
    QPoint mouse_start_point; // 鼠标开始位置
    QPoint window_topleft_point; // 鼠标结束位置
};

#endif // SIGNINFORM_H
