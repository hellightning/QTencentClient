#include "clientadapter.h"
#include "signinform.h"
#include "registerform.h"
#include "friendlistform.h"

ClientAdapter::ClientAdapter(QObject *parent) : QObject(parent)
{

}

void ClientAdapter::update_register_status(QtId id)
{
    this->cliend_id = id;
}

void ClientAdapter::update_sign_status()
{

}

void ClientAdapter::update_friend_list()
{

}

void ClientAdapter::write_message()
{

}

void ClientAdapter::make_sign_request()
{

}

void ClientAdapter::make_register_request()
{

}
