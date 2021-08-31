#include "mymsgitem.h"
#include "ui_mymsgitem.h"

MyMsgItem::MyMsgItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyMsgItem)
{
    ui->setupUi(this);
    //设置边距
    ui->MsgBoard->setMargin(10);
}

MyMsgItem::~MyMsgItem()
{
    delete ui;
}

void MyMsgItem::setData(QString nickName, QString msg)
{
    ui ->nickName ->setText(nickName);
    ui ->MsgBoard ->setText(msg);

    ui -> MsgBoard->setAlignment(Qt::AlignTop);
    ui -> MsgBoard->setWordWrap(true);
    ui -> MsgBoard->adjustSize();

}

int MyMsgItem::getHeight()
{
    return ui ->MsgBoard ->height()+ (ui ->nickName ->height());
}

