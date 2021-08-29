#include "friendlistform.h"
#include "ui_friendlistform.h"
#include "clientadapter.h"

FriendListForm::FriendListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendListForm)
{
    ui->setupUi(this);
}

FriendListForm::~FriendListForm()
{
    delete ui;
}

void FriendListForm::set_qtid(QtId)
{

}

void FriendListForm::set_nickname(QString)
{

}

void FriendListForm::set_friend_list(QList<QtId>)
{

}

void FriendListForm::emphasis_friend_item(QtId)
{

}

void FriendListForm::on_friendListWidget_itemDoubleClicked(QListWidgetItem *item)
{

}


void FriendListForm::on_floatActionButton_clicked()
{

}

