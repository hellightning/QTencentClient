#ifndef QMYTEXT_H
#define QMYTEXT_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>

class QmyText : public QTextEdit
{
public:
    explicit QmyText(QWidget *parent = 0);
    QmyText();
protected:
    void keyPressEvent(QKeyEvent *e) override;
};

#endif // QMYTEXT_H
