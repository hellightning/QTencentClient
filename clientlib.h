#ifndef CLIENTLIB_H
#define CLIENTLIB_H

#include <tuple>
#include <QObject>

#include <QXmlStreamReader>
#include <QFile>
#include <iostream>

using server_config = std::tuple<QString, int>;
using QtId = int;
using SMessage = std::tuple<QtId, QString>;
using Message = QList<SMessage>;
using User = std::tuple<QtId, QString>;

struct message_list {
    int qtid;
    QString nickname;
    QList<QPair<int, QString>> message;
};

inline server_config read_network_config_file() {
    QFile file(":/Config/config.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return std::make_tuple("", -1);
    }
    QXmlStreamReader reader(&file);
    reader.readNext();
    QString ip, port;
    while (!reader.atEnd()) {
        if (reader.isStartElement()) {
            if (reader.name() == "ip") {
                ip = reader.readElementText().trimmed();
            }
            if (reader.name() == "port") {
                port = reader.readElementText().trimmed();
            }
        }
        reader.readNext();
    }
    return std::make_tuple(ip, port.toInt());
}

#endif // CLIENTLIB_H
