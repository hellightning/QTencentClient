/**
 * @file mytest.h
 * @brief 单元测试类
 * @details 执行参院测试
 */
#ifndef MYTEST_H
#define MYTEST_H

#include <QObject>
#include <QtTest/QtTest>

class mytest : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief mytest 测试类的构造函数
     * @param parent 服务台
     */
    explicit mytest(QObject *parent = nullptr);

signals:

private slots:
    //void test();
    /**
     * @brief UItest UI的测试函数
     */
    void UItest();
    /**
     * @brief test 通用测试函数
     */
    void test();
    /**
     * @brief adapterTest adapter测试函数
     */
    void adapterTest();

};

#endif // MYTEST_H
