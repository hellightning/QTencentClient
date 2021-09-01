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

bool IOHandler::store_file(const file_byte& file) {
    QDir dir(PROJECT_STORAGE_DIR);
        if (!dir.exists()){
            dir.mkdir(PROJECT_STORAGE_DIR);
    }
    QDir dir2(PROJECT_STORAGE_DIR + "files/");
        if (!dir2.exists()){
            dir2.mkdir(PROJECT_STORAGE_DIR + "files/");
    }
    QString store_path = PROJECT_STORAGE_DIR + QString("files/%1.%2").arg(file.file_name).arg(file.file_type);
    QFile qfile(store_path);
    if (qfile.exists()) {
        for (int i = 1; ;++i) {
            store_path = PROJECT_STORAGE_DIR + QString("files/%1_%2.%3").arg(file.file_name).arg(i).arg(file.file_type);
            qfile.setFileName(store_path);
            if (!qfile.exists())
                break;
        }
    }
    if(!qfile.open(QIODevice::ReadWrite)) {
        return false;
    }
    qfile.write(file.file_byte);
    return true;
}


