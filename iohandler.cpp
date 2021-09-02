#include "iohandler.h"
#include <QStandardPaths>
#include <QDir>
#include <QDataStream>
#include <QDebug>

QString PROJECT_STORAGE_DIR = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/data/");
QString FILE_STORAGE_DIR = PROJECT_STORAGE_DIR + "files/";



QDataStream& operator<<(QDataStream& output, const message_list& lst) {
    foreach(auto& e, lst.message) {
        output << e;
    }
    return output;
}

QDataStream& operator>>(QDataStream& input, message_list& lst) {
    while(!input.atEnd()) {
        QPair<int, QString> v;
        input >> v;
        lst.message.append(v);
    }
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
    qDebug() << path << " " << file.exists();
    if (!file.exists()) {
        file.open(QFile::WriteOnly | QFile::Truncate);
    //    qDebug() << path;
        std::string str;
        for(auto& s : lst.message) {
            str += std::to_string(s.first);
            str += "~";
            str += s.second.toStdString();
            str += "\n";
        }
        file.write(str.c_str());
    } else {
        file.open(QFile::WriteOnly | QFile::Append);
        std::string str;
        for(auto& s : lst.message) {
            str += std::to_string(s.first);
            str += "~";
            str += s.second.toStdString();
            str += "\n";
        }
        file.write(str.c_str());
    }

}

message_list IOHandler::unserialize_storage(int qtid) {
    QString path = PROJECT_STORAGE_DIR + QString("user_%1.qnm").arg(qtid);
    QFile file(path);
    if (!file.exists()) {
        qDebug() << "not exists";
        return message_list{-1, "", {}};
    }
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "cannot open";
        return message_list{-1, "", {}};
    }
    char* buffer = new char[1024];
    file.read(buffer, 1024);

    QString str(buffer);
    QList<QPair<int, QString>> s_e;
    auto lst = str.split("\n");
    for(auto& v : lst) {
        auto e = v.split("~");
        if (e.size() >= 2) {
            auto s = e[0].toInt();
            auto s2 = e[1];
            s_e.push_back(qMakePair(s, s2));
        }
    }
    qDebug() << s_e;
//    auto str = std::string(std::move(buffer));
//    size_t pos = str.find('\n');
//    size_t s_size = str.size();
//    while (pos != std::string::npos) {
//        auto x = str.substr(0, pos);
//        str = str.substr(pos + 1, s_size);
//        pos = str.find('\n');
//    }
    return {0, "", s_e};
}

bool IOHandler::store_file(const file_byte& file) {
    QDir dir(PROJECT_STORAGE_DIR);
        if (!dir.exists()){
            dir.mkdir(PROJECT_STORAGE_DIR);
    }
    QDir dir2(FILE_STORAGE_DIR);
        if (!dir2.exists()){
            dir2.mkdir(FILE_STORAGE_DIR);
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
    qDebug() << "handle result: " << file.file_byte;
    qfile.write(file.file_byte);
    return true;
}

QString IOHandler::get_file_path(const QString &file_name, const QString &file_type) const
{
    return FILE_STORAGE_DIR;
}


