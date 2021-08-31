#ifndef MYMSGITEM_H
#define MYMSGITEM_H

#include <QWidget>

namespace Ui {
class MyMsgItem;
}

class MyMsgItem : public QWidget
{
    Q_OBJECT

public:
    explicit MyMsgItem(QWidget *parent = nullptr);
    ~MyMsgItem();
    void setData(QString,QString,QString);
    int getHeight();
    void setPosRight(bool isRight);

private:
    Ui::MyMsgItem *ui;
};

#endif // MYMSGITEM_H
