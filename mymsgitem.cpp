#include "mymsgitem.h"
#include "ui_mymsgitem.h"
#include <QPainter>
#include <QLabel>

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

void MyMsgItem::setData(QString nickName, QString msg,QString curTime) {
    ui ->nickName ->setText(nickName.mid(1,nickName.size()-1));
    ui ->MsgBoard ->setText(msg);
    ui ->timeShow ->setText(curTime);

    int iconId = nickName.mid(0,1).toInt();
    QString imgPath = ":/Icons/icon/img" +QString::number(iconId + 1) + ".jpg";

    int myWidth = ui->msgIcon->width() - 6;
    int myHeight = ui->msgIcon->height();

    QPixmap originPath(imgPath);
    QPixmap roundCircle(myWidth,myHeight);
    roundCircle.fill(Qt::transparent);
    QPainter painter(&roundCircle);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0,0,myWidth,myHeight);    //绘制椭圆
    painter.setClipPath(path);
    painter.drawPixmap(0,0,myWidth,myHeight,originPath);

    ui->msgIcon->setPixmap(roundCircle);
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
        ui ->msgIcon -> setGeometry(700 - 50,ui ->MsgBoard ->y(),
                                     ui->MsgBoard->width(),ui -> MsgBoard->height());

    }
    //放左边
    else {
        ui ->MsgBoard ->setGeometry(50, ui->MsgBoard->y(),
                        ui->MsgBoard->width(),ui -> MsgBoard->height());
        ui ->nickName ->setGeometry(10, ui->nickName->y(),
                        ui->nickName->width(),ui -> nickName->height());
        ui ->msgIcon -> setGeometry(10,ui ->MsgBoard ->y(),
                                     ui->MsgBoard->width(),ui -> MsgBoard->height());

    }
    //修改当前自定义控件大小
    this->setFixedSize(700,getHeight() + 20);
}


