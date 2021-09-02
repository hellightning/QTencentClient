#include "chatform.h"
#include "ui_chatform.h"
#include "clientadapter.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QGraphicsDropShadowEffect>

ChatForm::ChatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    auto shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(8);
    ui->BackgroundFrame->setGraphicsEffect(shadow_effect);
    ui->sendMessageButton->raise();
    //ui->MsgBoard->setViewMode(QListView::viewMode(QListView::ViewMode));
}

ChatForm::~ChatForm() {
    adapter ->close_chatform(currentFriendID);
    delete ui;
}


void ChatForm::set_adapter(ClientAdapter *cli) {
    adapter = cli;
}

#include <QDebug>
//currentMsg = "01:53" + "realMessage"

void ChatForm::on_sendMessageButton_clicked() {
    QString currentMsg = ui ->typeBoard->toPlainText();
    if(!currentMsg.isEmpty()) {

        QString curTime = QString("%1").arg(QTime::currentTime().hour(),2,10,QChar('0')) + ":" +
                QString("%1").arg(QTime::currentTime().minute(),2,10,QChar('0'));

        //发送请求 上传的消息总是自带时间
        adapter->send_message(currentFriendID,curTime + currentMsg);
        //刷新到UI上
        update_list_widget(std::make_tuple(adapter->cliend_id,curTime + currentMsg));
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

void ChatForm::on_get_file_succ(QString filePass,QString fileName) {
     //TODO 弹文件传输完成消息 双击打开
     add_item_to_ui(adapter->qtid_to_nickname[currentFriendID],
         "对方发送 " + fileName,false);
     qDebug() << "完成文件传输:" << filePass << " " << fileName << endl;
}


void ChatForm::add_item_to_ui(QString nickName, QString realMsg,bool isMySelf) {
      MyMsgItem* pItemWidget = new MyMsgItem(this);

      pItemWidget->setData(nickName, realMsg.mid(5,realMsg.size()-5),realMsg.mid(0,5));
      pItemWidget->setStyleSheet("border: 0px solid white");
      QListWidgetItem* pItem = new QListWidgetItem();

//    手动调整自定义Item大小
      pItemWidget ->setPosRight(isMySelf);
      pItem -> setSizeHint(QSize(700,pItemWidget->getHeight()+30));
//    不能换顺序

//    连接自定义控件
      ui->MsgBoard->addItem(pItem);
      ui->MsgBoard->setItemWidget(pItem, pItemWidget);
}


void ChatForm::on_sendFileBtn_clicked() {
    auto fileName = QFileDialog::getOpenFileName(nullptr, "打开您发送的文件",
                    QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    //TODO直接显示传输文件 不可点击
    if(!fileName.isEmpty()) {
        add_item_to_ui(adapter->qtid_to_nickname[adapter ->cliend_id],
            "已发送 " + fileName,true);
        adapter ->send_file(currentFriendID,fileName);
    }
}


void ChatForm::on_CloseButton_clicked()
{
    adapter ->close_chatform(currentFriendID);
    close();
}


void ChatForm::on_SmallButton_clicked()
{
    setWindowState(Qt::WindowMinimized);
}

void ChatForm::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        isDrag = true;
        mouse_start_point = e->globalPos();
        window_topleft_point = frameGeometry().topLeft();
    }
}

void ChatForm::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        isDrag = false;
    }
}

void ChatForm::mouseMoveEvent(QMouseEvent *e)
{
    if (isDrag) {
        QPoint dist = e->globalPos() - mouse_start_point;
        this->move(window_topleft_point + dist);
    }
}

void ChatForm::keyPressEvent(QKeyEvent *e)
{
    if (((QApplication::keyboardModifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_Enter))
            || ((QApplication::keyboardModifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_Return))) {
        if (focusWidget() == ui->typeBoard) {
            on_sendMessageButton_clicked();
        }
    }
}

