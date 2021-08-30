#include "mytest.h"
#include <clientadapter.h>
#include <clientsockethandler.h>
#include "friendlistform.h"
#include <QtTest/QtTest>

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
}
