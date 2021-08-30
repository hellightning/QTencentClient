#include "mytest.h"
#include <clientadapter.h>
#include <clientsockethandler.h>

mytest::mytest(QObject *parent) : QObject(parent)
{

}

void mytest::test()
{
    ClientAdapter adapter;
    adapter.sign_in(4, "white_album");
}
