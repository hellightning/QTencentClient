#ifndef CLIENTSOCKETHANDLER_H
#define CLIENTSOCKETHANDLER_H

#include <QObject>
#include <QTcpSocket>

class ClientSocketHandler : public QObject
{
    Q_OBJECT
public:
    static ClientSocketHandler* get_instance();
private:
    explicit ClientSocketHandler(QObject *parent = nullptr);
    static ClientSocketHandler* instance;
    QTcpSocket* tcp_socket;

signals:
};

inline ClientSocketHandler *ClientSocketHandler::get_instance(){
    if(instance == nullptr){
        instance = new ClientSocketHandler();
    }
    return instance;
}

#endif // CLIENTSOCKETHANDLER_H
