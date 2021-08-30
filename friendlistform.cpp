#include "friendlistform.h"
#include "ui_friendlistform.h"
#include "clientadapter.h"
#include <QDebug>
#include <QMessageBox>

FriendListForm::FriendListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendListForm)
{
    ui->setupUi(this);

    ui->friendsPool->setResizeMode(QListView::Adjust);
   // ui->friendsPool->setViewMode(QListView::IconMode);
}

FriendListForm::~FriendListForm()
{
    delete ui;
}


//Debug 访问ui控件
int FriendListForm::getSize() {
//    int a = dynamic_cast<MyItemWidget*>
//            (ui ->friendsPool->itemWidget(ui->friendsPool->item(0)))->getQid();
    return ui -> friendsPool -> count();
}

void FriendListForm::set_qtid(QtId id) {
    ui ->qtIdLabel ->setText(QString("%1").arg(id));
}

void FriendListForm::set_nickname(QString nick) {
    ui ->MyNicknameLabel ->setText(nick);
}


//更新UI界面 将传输的好友数据显示到UI上
void FriendListForm::set_friend_list(QList<std::tuple<QtId, QString> > dataList) {
    //TODO
    ui ->friendsPool -> clear();
    for(int i = 0;i < dataList.size();++i) {
        add_Item_toUI(std::get<1>(dataList.at(i)),std::get<0>(dataList.at(i)));
    }
}

void FriendListForm::emphasis_friend_item(QtId tarQtid) {

   MyItemWidget* selected = nullptr;

   for(int i = 0;i < ui ->friendsPool->count();++i) {
       int abcde = (dynamic_cast<MyItemWidget*>
                    (ui ->friendsPool->itemWidget(ui->friendsPool->item(i)))->getQid());
       if(tarQtid == abcde) {
           selected = dynamic_cast<MyItemWidget*>
                   (ui ->friendsPool->itemWidget(ui->friendsPool->item(i)));
           selected ->setHasMsg();
           return;
       }

   }

   show_error("未找到的好友");
}

void FriendListForm::on_friendListWidget_itemDoubleClicked(QListWidgetItem *item) {

}

void FriendListForm::show_error(QString warningMsg) {
    int ret = QMessageBox::warning(this,"警告",warningMsg,QMessageBox::Yes);
    if(ret == QMessageBox::Yes) {
       //do nothing
    }
}

//增加一个好友
void FriendListForm::add_Item_toUI(QString nickName,int qtID) {
    MyItemWidget* pItemWidget = new MyItemWidget(this);
    pItemWidget->SetData(nickName, qtID);
    QListWidgetItem* pItem = new QListWidgetItem();

    //手动调整自定义Item大小
    pItem->setSizeHint(QSize(350, 60));

    ui->friendsPool->addItem(pItem);
    ui->friendsPool->setItemWidget(pItem, pItemWidget);
}

void FriendListForm::add_friend(std::tuple<QtId, QString> mFriend) {
    add_Item_toUI(std::get<1>(mFriend),std::get<0>(mFriend));
}

void FriendListForm::on_floatActionButton_clicked()
{

}

