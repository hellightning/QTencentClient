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
    return ui -> friendsPool -> count();
}

//设置Qtid
void FriendListForm::set_qtid(QtId id) {
    ui ->qtIdLabel ->setText(QString("%1").arg(id));
}

//设置昵称
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

//将tarQtid的好友标红 有未读消息 双击后取消
void FriendListForm::emphasis_friend_item(QtId tarQtid) {
   MyItemWidget* selected = nullptr;
   for(int i = 0;i < ui ->friendsPool->count();++i) {
       int curQtid = (dynamic_cast<MyItemWidget*>
                    (ui ->friendsPool->itemWidget(ui->friendsPool->item(i)))->getQid());
       if(tarQtid == curQtid) {
           selected = dynamic_cast<MyItemWidget*>
                   (ui ->friendsPool->itemWidget(ui->friendsPool->item(i)));
           selected ->setHasMsg();
           return;
       }
   }
   show_error("未找到的好友");
}

void FriendListForm::on_friendListWidget_itemDoubleClicked(MyItemWidget *item) {
    qDebug() << item << adapter;
    //除去未读消息标志
    item ->clearMsgIcon();
    //打开聊天窗口
    adapter ->open_chatform(item->getQid());
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
    //连接信号槽
    connect(pItemWidget,SIGNAL(double_cliceked_to_friendsform(MyItemWidget*)),
        this,SLOT(on_friendListWidget_itemDoubleClicked(MyItemWidget*)));

    pItemWidget->SetData(nickName, qtID);
    QListWidgetItem* pItem = new QListWidgetItem();

    //手动调整自定义Item大小
    pItem->setSizeHint(QSize(350, 60));

    //连接自定义控件
    ui->friendsPool->addItem(pItem);
    ui->friendsPool->setItemWidget(pItem, pItemWidget);
}

//添加一个好友
void FriendListForm::add_friend(std::tuple<QtId, QString> mFriend) {
    add_Item_toUI(std::get<1>(mFriend),std::get<0>(mFriend));
}

void FriendListForm::set_adapter(ClientAdapter *cli) {
    adapter = cli;
}

void FriendListForm::on_floatActionButton_clicked() {
    //TO DO 添加好友查找好友
    if(!(ui ->friendListEdit->toPlainText().isEmpty())) {
        adapter ->add_friend(ui -> friendListEdit ->toPlainText().toInt());
    }
}

