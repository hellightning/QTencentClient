#include "newmsgitem.h"
#include "ui_msgitem.h"
#include <QSizePolicy>

newMsgItem::newMsgItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgItem)
{
    ui->setupUi(this);
    //ui ->MsgBoard ->setFixedWidth(150);
}

newMsgItem::~newMsgItem()
{
    delete ui;
}

void newMsgItem::setData(QString nickName, QString msg) {

    ui ->nickName ->setText(nickName);
    ui ->MsgBoard ->setText(msg);

    ui -> MsgBoard->setAlignment(Qt::AlignTop);
    ui -> MsgBoard->setWordWrap(true);
    ui -> MsgBoard->adjustSize();

}

int newMsgItem::getHeight() {
    return ui ->MsgBoard ->height() + (ui -> nickName ->height());
}
