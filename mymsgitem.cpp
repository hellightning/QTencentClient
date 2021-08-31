#include "mymsgitem.h"
#include "ui_mymsgitem.h"

MyMsgItem::MyMsgItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyMsgItem)
{
    ui->setupUi(this);
    //设置边距
}

MyMsgItem::~MyMsgItem()
{
    delete ui;
}

void MyMsgItem::setData(QString nickName, QString msg) {
    ui ->nickName ->setText(nickName);
    ui ->MsgBoard ->setText(msg);
}

int MyMsgItem::getHeight() {
    return ui -> MsgBoard ->height() + (ui ->nickName ->height());
}

#include <QDebug>
void MyMsgItem::setPosRight(bool isRight) {

    ui ->MsgBoard ->setMargin(10);
    ui ->MsgBoard ->setWordWrap(true);
    ui ->MsgBoard ->adjustSize();
    //设置一个最大宽度
    ui ->MsgBoard ->setMaximumWidth(230);
    //放右边
    if(isRight == true) {
        ui ->MsgBoard ->setGeometry(700 - (ui->MsgBoard->width()) - 50, ui->MsgBoard->y(),
                        ui->MsgBoard->width(),ui -> MsgBoard->height());
        ui ->nickName ->setGeometry(700 - 70 -(ui ->nickName->width()),ui->nickName->y(),
                        ui->nickName->width(),ui -> nickName->height());
    }
    //放左边
    else {
        ui ->MsgBoard ->setGeometry(50, ui->MsgBoard->y(),
                        ui->MsgBoard->width(),ui -> MsgBoard->height());
        ui ->nickName ->setGeometry(10, ui->nickName->y(),
                        ui->nickName->width(),ui -> nickName->height());

    }
    //修改当前自定义控件大小
    this->setFixedSize(700,getHeight() + 20);
}


