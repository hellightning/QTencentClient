/**
 * @file iohandler.h
 * @brief IO处理工具类
 * @details 封装了IO处理的相关函数
 */
#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <QObject>
#include "clientlib.h"

/**
 * @brief The IOHandler class IO处理工具类
 */
class IOHandler : QObject
{
    Q_OBJECT
public:
    /**
     * @brief IOHandler IO处理类
     * @param parent 父物体
     */
    explicit IOHandler(QObject *parent = nullptr);
    /**
     * @brief operator << 流操作重载
     * @param output 输出流
     * @param lst 消息队列
     */
    friend QDataStream& operator<<(QDataStream& output, const message_list& lst);
    /**
     * @brief operator >> 流操作重载
     * @param input 输入流
     * @param lst 消息队列
     */
    friend QDataStream& operator>>(QDataStream& input, message_list& lst);
    /**
     * @brief serialize_storage 序列化存储
     * @param lst 目标存储的类
     */
    void serialize_storage(const message_list& lst);
    /**
     * @brief unserialize_storage 反序列化得到元素
     * @param qtid 元素id
     * @return  目标存储的类
     */
    message_list unserialize_storage(int qtid);
    /**
     * @brief store_file 存储文件的工具函数
     * @param file 文件
     * @return 是否成功
     */
    bool store_file(const file_byte& file);
    /**
     * @brief get_file_path 获取文件路径
     * @param file_name 文件名
     * @param file_type 文件扩展名
     * @return 路径
     */
    QString get_file_path(const QString& file_name, const QString& file_type) const;

};

#endif // IOHANDLER_H
