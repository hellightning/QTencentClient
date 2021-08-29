#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>
class ClientAdapter;

typedef int QtId;
namespace Ui {
class RegisterForm;
}

class RegisterForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = nullptr);
    ~RegisterForm();
    QString get_nickname();
    QString get_password();
    void set_adapter(ClientAdapter*);

private slots:
    void on_confirmPushButton_clicked();

private:
    Ui::RegisterForm *ui;
    ClientAdapter *adapter;
    bool check_password();
    void show_qtid(QtId);
    void show_alert(QString Msg);
};

#endif // REGISTERFORM_H
