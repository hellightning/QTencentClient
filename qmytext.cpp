#include "qmytext.h"
#include <QDebug>

QmyText::QmyText(){}
//实现带有GUI父类的构造函数
QmyText::QmyText(QWidget *parent) : QTextEdit(parent) {}

//重载按键行为
void QmyText::keyPressEvent(QKeyEvent *e) {
    if (e->type() == QEvent::KeyPress) {

            if (e->key() == Qt::Key_Enter) {
                qDebug() << "You press A.";
            }
            //调用父类的事件处理机制
            else QTextEdit::keyPressEvent(e);
        }
}
