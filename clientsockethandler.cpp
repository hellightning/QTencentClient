#include "clientsockethandler.h"
#include "clientadapter.h"

void ClientSocketHandler::set_adapter(ClientAdapter* _adapter)
{
    adapter = _adapter;
}

ClientSocketHandler::ClientSocketHandler(QObject *parent) : QObject(parent)
{

}
