#include "clientadapter.h"
#include "signinform.h"
#include "registerform.h"
#include "friendlistform.h"

ClientAdapter::ClientAdapter(QObject *parent) : QObject(parent)
{
    sign_in_form = new SignInForm();
    sign_in_form->show();
    sign_in_form->set_adapter(this);
}

void ClientAdapter::update_register_status(QtId id)
{
    this->cliend_id = id;
}

void ClientAdapter::update_sign_status()
{
    if (sign_in_form != nullptr) {

    }
}

void ClientAdapter::update_friend_list()
{

}

void ClientAdapter::write_message()
{

}

void ClientAdapter::make_sign_request(QtId id, QString pwd)
{

}

void ClientAdapter::make_register_request(QString nickname, QString pwd)
{

}
