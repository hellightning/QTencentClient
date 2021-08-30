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

//void mytest::test()
//{
//    ClientAdapter adapter;
//    adapter.sign_in(4, "white_album");
//}

void mytest::UItest()
{
    //RegisterForm w;
    //w.show();

    //ClientAdapter adapter;
    FriendListForm w;
    w.show();
    QList<std::tuple<int,QString>> llist;
    llist.append(std::tuple<int,QString>(1,"Faller"));
    llist.append(std::tuple<int,QString>(2,"LR"));

    w.set_friend_list(llist);
    w.emphasis_friend_item(2);
    qDebug() << w.getSize() << endl;

    QTest::qWait(10000);
void mytest::test()
{
    ClientAdapter adapter;
    adapter.sign_in(10, "233");
    QTest::qWait(2000);
    adapter.send_message(10, "hello self");
    QTest::qWait(2000);
}
