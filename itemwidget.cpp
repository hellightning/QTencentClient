#include "itemwidget.h"
#include "ui_itemwidget.h"
#include <QLabel>
#include <QPainter>

MyItemWidget::MyItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidget)
{
    ui -> setupUi(this);
    ui -> hasMsg ->setVisible(false);
    connect(ui->backDec,SIGNAL(setQlabel()),this,SLOT(item_on_double_clicked()));

}

MyItemWidget::~MyItemWidget()
{
    delete ui;
}

int MyItemWidget::getQid() {
    return ui -> qtId -> text().toInt();
}


QString MyItemWidget::getNickName() {
    return ui -> nickName -> text();
}

void MyItemWidget::SetNickAndIcon(QString nick) {
      ui->nickName->setText(nick.mid(1,nick.size()-1));

      int iconId = nick.mid(0,1).toInt();
      QString imgPath = ":/Icons/icon/img" +QString::number(iconId + 1) + ".jpg";

      int myWidth = ui->Icon->width() - 6;
      int myHeight = ui->Icon->height();

      QPixmap originPath(imgPath);
      QPixmap roundCircle(myWidth,myHeight);
      roundCircle.fill(Qt::transparent);
      QPainter painter(&roundCircle);
      painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
      QPainterPath path;
      path.addEllipse(0,0,myWidth,myHeight);    //绘制椭圆
      painter.setClipPath(path);
      painter.drawPixmap(0,0,myWidth,myHeight,originPath);

      ui->Icon->setPixmap(roundCircle);
}

void MyItemWidget::setQtId(int _id) {
     ui ->qtId ->setText(QString::number(_id));
}

void MyItemWidget::setHasMsg() {
    ui -> hasMsg -> setVisible(true);
}

void MyItemWidget::clearMsgIcon() {
    setNoneMsg();
}

void MyItemWidget::setNoneMsg() {
    ui -> hasMsg -> setVisible(false);

}

void MyItemWidget::item_on_double_clicked() {
    setNoneMsg();
    emit double_cliceked_to_friendsform(this);
}
