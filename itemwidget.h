#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include "QDebug"


namespace Ui {
class ItemWidget;
}

class MyItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyItemWidget(QWidget *parent = 0);
    ~MyItemWidget();

    //设置数据

    void SetNickAndIcon(QString);
    void setQtId(int);
    int getQid();
    QString getNickName();
    void setHasMsg();
    void clearMsgIcon();

private slots:
    void setNoneMsg();
    void item_on_double_clicked();
signals:
    void double_cliceked_to_friendsform(MyItemWidget*);

private:
    Ui::ItemWidget *ui;

};

#endif // ITEMWIDGET_H
