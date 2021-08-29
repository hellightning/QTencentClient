#include "signinform.h"

#include <QApplication>
#include "clientadapter.h"
#include "registerform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //RegisterForm w;
    //w.show();
    ClientAdapter adapter;
    return a.exec();
}
