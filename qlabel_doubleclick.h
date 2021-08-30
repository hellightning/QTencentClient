//qlabel_doubleclick.h
#ifndef QLABEL_DOUBLECLICK_H_
#define QLABEL_DOUBLECLICK_H_

#include <QLabel>
#include <QMouseEvent>

class qlabel_doubleclick : public QLabel
{
    Q_OBJECT

public:
    qlabel_doubleclick(QWidget *parent = 0);
    ~qlabel_doubleclick();
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:
    void setQlabel();
};

#endif // QLABEL_DOUBLECLICK_H_
