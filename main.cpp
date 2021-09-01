#include "signinform.h"

#include <QApplication>
#include "clientadapter.h"
#include "registerform.h"
#include "clientsockethandler.h"

#include "mytest.h"

ClientSocketHandler* ClientSocketHandler::instance = nullptr;

//QTEST_MAIN(mytest);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //RegisterForm w;
    //w.show();
//    ClientAdapter adapter;
    ClientAdapter adapter;
    ChatForm f;
    f.show();
    f.set_adapter(&adapter);
    return a.exec();
}


