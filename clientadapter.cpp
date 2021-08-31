#include "clientadapter.h"
#include "signinform.h"
#include "registerform.h"
#include "friendlistform.h"
#include "clientsockethandler.h"
#include <QWidget>
#include <QtConcurrent/QtConcurrent>

ClientAdapter::ClientAdapter(QObject *parent) : QObject(parent)
{
    sign_in_form = new SignInForm();
    //sign_in_form->show();
    sign_in_form->set_adapter(this);

    io_handler = new IOHandler();

    ClientSocketHandler::get_instance()->set_adapter(this);
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
            qDebug() << id;
        }
    } else {
        if (register_form != nullptr) {
            register_form->failed_msg(errmsg);
        }
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
        friend_list_form->show();
        auto handler = ClientSocketHandler::get_instance();
        handler->make_get_friends_request(cliend_id);
    } else {
        if (sign_in_form != nullptr) {
            sign_in_form->failed_sign(errmsg);
        }
    }

}

void ClientAdapter::update_friend_list_status(Status stat, QList<std::tuple<QtId, QString> > friends, QString errmsg)
{

    if (stat == SUCCESS) {
        foreach (auto& frd, friends) {
            auto& [id, nname] = frd;
            qtid_to_nickname[id] = nname;
        }
        friend_list_form->set_friend_list(friends);
    } else {
        friend_list_form->show_error(errmsg);
    }

}

void ClientAdapter::update_add_friend_status(Status stat, std::tuple<QtId, QString> mFriend, QString errmsg)
{

    if (stat == SUCCESS) {
        auto& [id, nname] = mFriend;
        qtid_to_nickname[id] = nname;
        friend_list_form->add_friend(mFriend);
    } else {
        friend_list_form->show_error(errmsg);
    }

}

void ClientAdapter::update_receive_message_status(Status stat, QList<SMessage> msg, QString errmsg)
{
    for (auto& val : msg) {
        auto& [id, msg_item] = val;
        if (stat == SUCCESS) {
            qtid_to_msglist[id].append(val);
            if (qtid_to_chatform[id] != nullptr) {
//                qtid_to_chatform[id]->update_list_widget(val);
            } else {
                // 序列化，TODO
                friend_list_form->emphasis_friend_item(id);
            }
        } else {
            qDebug() << errmsg;
        }
    }
}

void ClientAdapter::send_message(QtId friendId, QString msg)
{
    auto handler = ClientSocketHandler::get_instance();
    handler->make_send_message_request(
                std::make_tuple(cliend_id, nick_name),
                std::make_tuple(friendId, msg));
    qtid_to_msglist[friendId].append(std::make_tuple(cliend_id, msg));
}

void ClientAdapter::open_register_form()
{
    if (register_form == nullptr) {
        register_form = new RegisterForm();
        register_form->show();
        register_form->set_adapter(this);
    }
}

void ClientAdapter::sign_in(QtId userid, QString pwd)
{
    auto handler = ClientSocketHandler::get_instance();
    this->cliend_id = userid;
    handler->make_sign_request(userid, pwd);
}

void ClientAdapter::make_register(QString nickname, QString pwd)
{
    auto handler = ClientSocketHandler::get_instance();
    handler->make_register_request(nickname, pwd);
}

void ClientAdapter::add_friend(QtId friendID)
{
    auto handler = ClientSocketHandler::get_instance();
    handler->make_add_friend_request(cliend_id, friendID);
}

void ClientAdapter::open_chatform(QtId friendID)
{
    if (qtid_to_chatform[friendID] == nullptr) {
        qtid_to_chatform[friendID] = new ChatForm(nullptr);
        QtConcurrent::run(QThreadPool::globalInstance(), [this](int friendID){
            auto res = io_handler->unserialize_storage(friendID);
            auto nick = qtid_to_nickname[friendID];
            QList<SMessage> lst;
            qDebug() << "open_chatform" << res.message;
            if (res.qtid != -1) {
                foreach(auto& v, res.message) {
                    lst.append(std::make_tuple(v.first, v.second));
                }
                qtid_to_chatform[friendID]->init_list_widget(friendID,lst);
            }
            qDebug() << "open" << res.qtid << " " << qtid_to_msglist[res.qtid].size();
            lst.append(qtid_to_msglist[res.qtid]);
            for(auto& e : lst) qDebug() << "con" << std::get<0>(e) << std::get<1>(e);
        }, friendID);

    } else {
        Qt::WindowFlags flags = qtid_to_chatform[friendID]->windowFlags();
        qtid_to_chatform[friendID]->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
        qtid_to_chatform[friendID]->show();
    }
}

void ClientAdapter::close_chatform(QtId friendID)
{
    if(qtid_to_chatform[friendID] != nullptr) {
        qtid_to_chatform[friendID] = nullptr;
    }
    QtConcurrent::run(QThreadPool::globalInstance(), [this](QtId friendID) {
        qDebug() << "close_chatform" << qtid_to_msglist[friendID].size();
        message_list lst;
        lst.qtid = friendID;
        lst.nickname = qtid_to_nickname[friendID];
        for(auto& [id, msg] : qtid_to_msglist[friendID]) {
            lst.message.append(qMakePair(id, msg));
        }
        qDebug() << "close:" << lst.message;
        io_handler->serialize_storage(lst);
        qtid_to_msglist[friendID].clear();
    }, friendID);

}
