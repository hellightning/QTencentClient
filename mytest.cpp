#include "mytest.h"
#include <clientadapter.h>
#include <clientsockethandler.h>
#include <future>
#include <QWaitCondition>
#include "friendlistform.h"
#include <QTest>
#include <QtTest/QTest>
#include "friendlistform.h"

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

//    QTest::qWait(10000);
}
void mytest::test()
{
//    ClientAdapter adapter;
//    adapter.sign_in(10, "233");
//    QTest::qWait(2000);
//    adapter.send_message(10, "hello self");
//    QTest::qWait(2000);
}

void mytest::adapterTest()
{
    ClientAdapter adapter;
//    adapter.update_register_status(SUCCESS, 114514, "");
//    QTest::qWait(1000);
//    adapter.update_register_status(SUCCESS, 5, "");
    QTest::qWait(2000);
    adapter.update_register_status(SUCCESS, 5, "");
    QTest::qWait(2000);
//    adapter.update_register_status(FAILED, -1, "233");
//    QTest::qWait(1000);
//    adapter.update_sign_status(SUCCESS, "qwq", "");
//    QTest::qWait(1000);
//    adapter.update_sign_status(FAILED, "qwq", "qwq");
//    QTest::qWait(1000);
//    QList<std::tuple<QtId, QString>> friends;
//    friends.append(std::make_tuple(2, "hhq"));
//    friends.append(std::make_tuple(3, "hhh"));
//    friends.append(std::make_tuple(10, "emm"));
//    adapter.update_friend_list_status(SUCCESS, friends, "");
//    QTest::qWait(1000);
//    adapter.update_friend_list_status(FAILED, friends, "233");
//    QTest::qWait(1000);
//    Message msg;
//    msg // << std::make_tuple(5, "czx")
//        << std::make_tuple(10, "2323")
//        << std::make_tuple(10, "222")
//        << std::make_tuple(10, "2ce");
//    adapter.update_receive_message_status(SUCCESS, msg, "");
//    QTest::qWait(1000);
//    adapter.send_message(10, "2mm");
//    QTest::qWait(1000);
//    adapter.open_chatform(10);
//    QTest::qWait(1000);
//    adapter.close_chatform(10);
//    QTest::qWait(1000);
//    adapter.update_receive_message_status(SUCCESS, msg, "");
//    QTest::qWait(1000);
////    adapter.open_chatform(5);
//    QTest::qWait(1000);
//    adapter.open_chatform(10);
//    QTest::qWait(1000);
////    adapter.close_chatform(5);
//    QTest::qWait(1000);
//    adapter.close_chatform(10);
//    QTest::qWait(1000);
//    adapter.update_receive_message_status(FAILED, msg, "233");

}
