#ifndef SIGNINFORM_H
#define SIGNINFORM_H

#include <QWidget>
#include <QMouseEvent>
class ClientAdapter;
typedef int QtId;
namespace Ui {
class SignInForm;
}

class SignInForm : public QWidget
{
    Q_OBJECT

public:
    explicit SignInForm(QWidget *parent = nullptr);
    ~SignInForm();

    QtId get_qtid();
    void set_qtid(QtId);
    QString get_password();
    void set_adapter(ClientAdapter*);
    void show_alert(QString);
    void failed_sign(QString);
    void changeIcon(int);

protected:
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);

private slots:
    void on_signInPushButton_clicked();
    void on_registerPushButton_clicked();
    void on_CloseButton_clicked();
    void on_SmallButton_clicked();

private:
    Ui::SignInForm *ui;
    ClientAdapter* adapter;
    bool isDrag;
    QPoint mouse_start_point;
    QPoint window_topleft_point;
};

#endif // SIGNINFORM_H
