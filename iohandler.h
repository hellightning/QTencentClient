#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <QObject>
#include "clientlib.h"

class IOHandler : QObject
{
    Q_OBJECT
public:
    explicit IOHandler(QObject *parent = nullptr);
    friend QDataStream& operator<<(QDataStream& output, const message_list& lst);
    friend QDataStream& operator>>(QDataStream& input, message_list& lst);
    void serialize_storage(const message_list& lst);
    message_list unserialize_storage(int qtid);

};

#endif // IOHANDLER_H
