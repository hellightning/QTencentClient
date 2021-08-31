#include "chatform.h"
#include "ui_chatform.h"
#include "clientadapter.h"

ChatForm::ChatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);
    //ui->MsgBoard->setViewMode(QListView::viewMode(QListView::ViewMode));
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

    add_item_to_ui(adapter->qtid_to_nickname[qid],msg,qid == adapter->cliend_id);

}


void ChatForm::add_item_to_ui(QString nickName, QString realMsg,bool isMySelf) {
      MyMsgItem* pItemWidget = new MyMsgItem(this);

      pItemWidget->setData(nickName, realMsg);
      QListWidgetItem* pItem = new QListWidgetItem();

//    手动调整自定义Item大小
      pItemWidget ->setPosRight(isMySelf);
      pItem -> setSizeHint(QSize(700,pItemWidget->getHeight()+30));
//    不能换顺序

//    连接自定义控件
      ui->MsgBoard->addItem(pItem);
      ui->MsgBoard->setItemWidget(pItem, pItemWidget);
}

