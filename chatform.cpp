#include "chatform.h"
#include "ui_chatform.h"
#include "clientadapter.h"

ChatForm::ChatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);
}

ChatForm::~ChatForm() {
    adapter ->close_chatform(currentFriendID);
    delete ui;
}


void ChatForm::set_adapter(ClientAdapter *cli) {
    adapter = cli;
}

void ChatForm::on_sendMessageButton_clicked() {
    QString currentMsg = ui ->typeBoard->toPlainText();
    if(!currentMsg.isEmpty()) {
        //发送请求
        adapter->send_message(currentFriendID,currentMsg);
        //刷新到UI上
        update_list_widget(std::make_tuple(adapter->cliend_id,currentMsg));
        ui ->typeBoard ->clear();
    }
}


void ChatForm::init_list_widget(QtId frinendId, QList<SMessage> msgList) {
     //TODO 刷新界面好友信息
     currentFriendID = frinendId;
     for(int i = 0;i < msgList.size();++i) {
         update_list_widget(msgList.at(i));
     }
}

//更新界面
void ChatForm::update_list_widget(SMessage currentMsg) {

    QtId qid = std::get<0>(currentMsg);
    QString msg = std::get<1>(currentMsg);

    if(qid == adapter->cliend_id) {
        //TODO 自己发送的信息
        add_item_to_ui(adapter->qtid_to_nickname[qid],msg);
    } else {
        //对方发送的信息
        add_item_to_ui(adapter->qtid_to_nickname[qid],msg);
    }
}

void ChatForm::add_item_to_ui(QString nickName, QString realMsg) {
      MyMsgItem* pItemWidget = new MyMsgItem(this);
//    //连接信号槽
      pItemWidget->setData(nickName, realMsg);
      pItemWidget -> setRight();
      QListWidgetItem* pItem = new QListWidgetItem();

//    //手动调整自定义Item大小
      pItem -> setSizeHint(QSize(400,pItemWidget->getHeight()+40));

//    //连接自定义控件
      ui->MsgBoard->addItem(pItem);
      ui->MsgBoard->setItemWidget(pItem, pItemWidget);
}

