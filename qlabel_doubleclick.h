/**
 * @file qlabel_doubleclick.h
 * @brief 处理label的单击事件
 */
#ifndef QLABEL_DOUBLECLICK_H_
#define QLABEL_DOUBLECLICK_H_

#include <QLabel>
#include <QMouseEvent>

/**
 * @brief The qlabel_doubleclick class 可单击的label类
 */
class qlabel_doubleclick : public QLabel
{
    Q_OBJECT

public:
    /**
     * @brief qlabel_doubleclick 构造函数
     * @param parent 父对象
     */
    qlabel_doubleclick(QWidget *parent = 0);
    /**
     * @brief 析构函数
     */
    ~qlabel_doubleclick();
    /**
     * @brief mouseDoubleClickEvent
     * @param event 双击事件
     */
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:
    /**
     * @brief setQlabel 设置label的信号
     */
    void setQlabel();
};

#endif // QLABEL_DOUBLECLICK_H_
