#include "mytest.h"
#include <clientadapter.h>
#include <clientsockethandler.h>
#include <future>
#include <QWaitCondition>
#include <QTest>
#include <QtTest/QTest>

mytest::mytest(QObject *parent) : QObject(parent)
{

}

void mytest::test()
{
    ClientAdapter adapter;
    adapter.sign_in(10, "233");
    QTest::qWait(2000);
    adapter.send_message(10, "hello self");
    QTest::qWait(2000);
}
