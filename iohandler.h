#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <QObject>

struct message_list {
    int qtid;
    QString nickname;
    QList<QPair<int, QString>> message;
};

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
