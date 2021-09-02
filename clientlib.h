/**
 * @file clientlib.h
 * @brief 客户端的约定
 * @details 定义了客户端的一些规定
 */
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

/**
 * @brief The file_byte struct 文件结构体
 */
struct file_byte {
    QtId from_id;
    QtId to_id;
    QString file_name;
    QString file_type;
    QByteArray file_byte;
};

/**
 * @brief The message_list struct 消息体
 */
struct message_list {
    int qtid;
    QString nickname;
    QList<QPair<int, QString>> message;
};

/**
 * @brief read_network_config_file 从xml中读取网络配置
 * @return 网络配置结果
 */
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
