#ifndef MYTEST_H
#define MYTEST_H

#include <QObject>
#include <QtTest/QtTest>



class mytest : public QObject
{
    Q_OBJECT
public:
    explicit mytest(QObject *parent = nullptr);

signals:

private slots:
    //void test();
    void UItest();
    void test();
    void adapterTest();

};

#endif // MYTEST_H
