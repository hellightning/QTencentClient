#include "clientadapter.h"
#include "signinform.h"
#include "registerform.h"
#include "friendlistform.h"
#include "clientsockethandler.h"

ClientAdapter::ClientAdapter(QObject *parent) : QObject(parent)
{
    sign_in_form = new SignInForm();
    sign_in_form->show();
    sign_in_form->set_adapter(this);
}

void ClientAdapter::update_register_status(Status stat, QtId id)
{

    this->cliend_id = id;
    if (register_form != nullptr) {
        register_form->show_qtid(id);
        register_form = nullptr;
    }
    if (sign_in_form != nullptr) {
        sign_in_form->set_qtid(id);
    }
}

void ClientAdapter::failed_register()
{
    if (register_form != nullptr) {
        register_form->failed_register();
    }
}

void ClientAdapter::update_sign_status(QString nickname)
{
    if (sign_in_form != nullptr) {
        delete sign_in_form;
    }
    this->nick_name = nickname;
    friend_list_form = new FriendListForm();
    friend_list_form->set_qtid(cliend_id);
    friend_list_form->set_nickname(nickname);
}

void ClientAdapter::update_friend_list()
{

}

void ClientAdapter::write_message()
{

}

void ClientAdapter::make_sign_request(QtId id, QString pwd)
{
    this->cliend_id = id;
}

void ClientAdapter::make_register_request(QString nickname, QString pwd)
{

}
