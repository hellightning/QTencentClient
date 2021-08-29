#include "signinform.h"

#include <QApplication>
#include "clientadapter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientAdapter adapter;
    return a.exec();
}
