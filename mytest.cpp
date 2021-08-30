#include "mytest.h"
#include <clientadapter.h>

mytest::mytest(QObject *parent) : QObject(parent)
{

}

void mytest::test()
{
    ClientAdapter adapter;
    adapter.sign_in(233, "qwq");
    adapter.send_message(114, "233");
    adapter.send_message(114, "236");
    adapter.send_message(114, "223");
    adapter.send_message(114, "213");
    QList<SMessage> mmsg;
    mmsg << std::make_tuple(114, "hhh");
    adapter.update_receive_message_status(SUCCESS,
          mmsg, "");
    adapter.close_chatform(114);
    adapter.open_chatform(114);
}
