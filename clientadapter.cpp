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

void ClientAdapter::update_register_status(Status stat, QtId id, QString errmsg)
{
    if (stat == SUCCESS) {
        this->cliend_id = id;
        if (register_form != nullptr) {
            register_form->show_qtid(id);
            register_form = nullptr;
        }
        if (sign_in_form != nullptr) {
            sign_in_form->set_qtid(id);
        }
    } else {

    }
}

void ClientAdapter::update_sign_status(Status stat, QString nickname, QString errmsg)
{
    if (stat == SUCCESS) {
        if (sign_in_form != nullptr) {
            delete sign_in_form;
        }
        this->nick_name = nickname;
        friend_list_form = new FriendListForm();
        friend_list_form->set_qtid(cliend_id);
        friend_list_form->set_nickname(nickname);
    } else {
        if (register_form != nullptr) {
            register_form->failed_register();
        }
    }
}

void ClientAdapter::update_friend_list_status(Status stat, QList<std::tuple<QtId, QString> > friends, QString errmsg)
{
    if (stat == SUCCESS) {

    } else {

    }
}

void ClientAdapter::update_add_friend_status(Status stat, std::tuple<QtId, QString> mFriend, QString errmsg)
{
    if (stat == SUCCESS) {

    } else {

    }
}

void ClientAdapter::update_receive_message_status(Status stat, Message msg, QString errmsg)
{
    if (stat == SUCCESS) {

    } else {

    }
}

void ClientAdapter::send_message(QtId friendId, QString msg)
{
//    auto handler = ClientSocketHandler::get_instance();
//    handler->make_send_message_request(
//                std::make_tuple(cliend_id, nick_name),
//                std::make_tuple(friendId, qtid_to_nickname[friendId], msg));
}

void ClientAdapter::sign_in(QtId userid, QString pwd)
{
//    auto handler = ClientSocketHandler::get_instance();
//    this->cliend_id = userid;
//    handler->make_sign_request(userid, pwd);
}

void ClientAdapter::make_register(QString nickname, QString pwd)
{
//    auto handler = ClientSocketHandler::get_instance();
//    this->nick_name = nickname;
//    handler->make_register_request(nickname, pwd);
}

void ClientAdapter::add_friend(QtId friendID)
{
//    auto handler = ClientSocketHandler::get_instance();
//    handler->make_add_friend_request(cliend_id, friendID);
}

void ClientAdapter::open_chatform(QtId friendID)
{

}
