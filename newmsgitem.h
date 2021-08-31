#ifndef NEWMSGITEM_H
#define NEWMSGITEM_H

#include <QWidget>


namespace Ui {
class newMsgItem;
}

class newMsgItem : public QWidget
{
    Q_OBJECT

public:
    explicit newMsgItem(QWidget *parent = nullptr);
    ~newMsgItem();
    void setData(QString,QString);
    int getHeight();

private:
    Ui::newMsgItem *ui;
};

#endif // NEWMSGITEM_H
