#ifndef SIGNINFORM_H
#define SIGNINFORM_H

#include <QWidget>

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
    void set_qtid();
    QString get_password();
    void show_alert(QString);

private slots:
    void on_signInPushButton_clicked();

    void on_pushButton_2_clicked();

    void on_registerPushButton_clicked();

private:
    Ui::SignInForm *ui;

};

#endif // SIGNINFORM_H
