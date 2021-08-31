#include "iohandler.h"
#include <QStandardPaths>
#include <QDir>
#include <QDataStream>
#include <QDebug>

QString PROJECT_STORAGE_DIR = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/data/");



QDataStream& operator<<(QDataStream& output, const message_list& lst) {
    output << lst.qtid << lst.nickname << lst.message;
    return output;
}

QDataStream& operator>>(QDataStream& input, message_list& lst) {
    input >> lst.qtid >> lst.nickname >> lst.message;
    return input;
}

IOHandler::IOHandler(QObject *parent)  : QObject(parent)
{

}

void IOHandler::serialize_storage(const message_list &lst)
{
    QDir dir(PROJECT_STORAGE_DIR);
        if (!dir.exists()){
            dir.mkdir(PROJECT_STORAGE_DIR);
    }
    QString path = PROJECT_STORAGE_DIR + QString("user_%1.qnm").arg(lst.qtid);
    QFile file(path);
    qDebug() << "serialize" << lst.message;
    if (!file.exists()) {
        file.open(QFile::WriteOnly | QFile::Truncate);
    //    qDebug() << path;
        qDebug() << path;
        QDataStream out(&file);
        out << lst;
    } else {
        file.open(QFile::WriteOnly | QFile::Append);
        QDataStream out(&file);
        out << lst.message;
    }

}

message_list IOHandler::unserialize_storage(int qtid) {
    QString path = PROJECT_STORAGE_DIR + QString("user_%1.qnm").arg(qtid);
    QFile file(path);
    if (!file.exists()) {
        return message_list{-1, "", {}};
    }
    if (!file.open(QIODevice::ReadOnly))
        return message_list{-1, "", {}};;
    QDataStream is(&file);
    message_list lst;
    is >> lst;
    return lst;
}


