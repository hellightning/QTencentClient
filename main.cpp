#include "signinform.h"

#include <QApplication>
#include "clientadapter.h"
#include "registerform.h"
#include "clientsockethandler.h"

#include "mytest.h"

ClientSocketHandler* ClientSocketHandler::instance = nullptr;

QTEST_MAIN(mytest);

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    //RegisterForm w;
//    //w.show();
//    ClientAdapter adapter;

//    return a.exec();
//}
