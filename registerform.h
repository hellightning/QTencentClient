/**
 * @file registerform.h
 * @brief 登录界面的托管类
 * @details 维护了登陆界面的UI
 */
#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>
class ClientAdapter;

typedef int QtId;
namespace Ui {
class RegisterForm;
}
/**
 * @brief 登录界面类
 */
class RegisterForm : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param 父物体
     */
    explicit RegisterForm(QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~RegisterForm();
    /**
     * @brief 获取昵称
     * @return 昵称
     */
    QString get_nickname();
    /**
     * @brief 获取密码
     * @return 密码
     */
    QString get_password();
    /**
     * @brief set_adapter 设置adapter
     * @param adapter adapter
     */
    void set_adapter(ClientAdapter* adapter);
    /**
     * @brief show_qtid 展示QtId
     * @param id qtid值
     */
    void show_qtid(QtId id);
    /**
     * @brief failed_msg 失败时候显示
     * @param msg 信息
     */
    void failed_msg(QString msg);

private slots:
    /**
     * @brief on_confirmPushButton_clicked 按下提交按钮的事件槽函数
     */
    void on_confirmPushButton_clicked();

    /**
     * @brief on_cancelPushButton_clicked 按下取消按钮的事件槽函数
     */

    void on_cancelPushButton_clicked();

private:
    Ui::RegisterForm *ui; // ui指针
    ClientAdapter *adapter; // adapter指针
    /**
     * @brief check_password 检查密码是否合规
     * @return 检查结果
     */
    bool check_password();
    /**
     * @brief show_alert_fail 弹出失败的提示框
     * @param warningMsg 提示信息
     */
    void show_alert_fail(QString warningMsg);
    /**
     * @brief show_alert_succ 弹出成功的提示框
     * @param Msg 提示信息
     */
    void show_alert_succ(QString Msg);
};

#endif // REGISTERFORM_H
