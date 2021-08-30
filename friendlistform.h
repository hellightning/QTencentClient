#ifndef FRIENDLISTFORM_H
#define FRIENDLISTFORM_H

#include <QWidget>
#include<QListWidget>
#include "itemwidget.h"

class ClientAdapter;

typedef int QtId;
namespace Ui {
class FriendListForm;
}

class FriendListForm : public QWidget
{
    Q_OBJECT

public:
    explicit FriendListForm(QWidget *parent = nullptr);
    ~FriendListForm();
    //设置当前窗口用户数据
    void set_qtid(QtId);
    void set_nickname(QString);
    void set_friend_list(QList<std::tuple<QtId, QString>>);
    void emphasis_friend_item(QtId);
    void show_error(QString);
    //void add_Item_toUI(QString,int);
    void add_friend(std::tuple<QtId, QString>);
    int getSize();

private slots:
    void on_friendListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_floatActionButton_clicked();

private:
    void add_Item_toUI(QString,int);


private:
    Ui::FriendListForm *ui;
};

#endif // FRIENDLISTFORM_H
