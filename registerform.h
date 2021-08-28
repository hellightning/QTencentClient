#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>

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

private slots:
    void on_confirmPushButton_clicked();

private:
    Ui::RegisterForm *ui;
    bool check_password();
    void show_qtid(QtId);
};

#endif // REGISTERFORM_H
