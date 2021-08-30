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

    void SetData(QString,int);
    int getQid();
    QString getNickName();
    void setHasMsg();

private slots:
    void setNoneMsg();


private:
    Ui::ItemWidget *ui;

};

#endif // ITEMWIDGET_H
