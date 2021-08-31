#include "itemwidget.h"
#include "ui_itemwidget.h"
#include <QLabel>


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

void MyItemWidget::SetData(QString qstrFileName, int iFileSize)
{

      ui->nickName->setText(qstrFileName);
      ui->qtId->setText(QString::number(iFileSize));
//    QPixmap pixmapPic(qstrPic);
//    int iWidth = ui->label_pic->width();
//    int iHeight = ui->label_pic->height();
//    QPixmap pixmapPicFit = pixmapPic.scaled(iWidth, iHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//饱满填充
//    ui->label_pic->setPixmap(pixmapPicFit);
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
