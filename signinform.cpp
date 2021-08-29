#include "signinform.h"
#include "ui_signinform.h"
#include "clientadapter.h"

SignInForm::SignInForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignInForm)
{
    ui->setupUi(this);
}

void SignInForm::set_adapter(ClientAdapter *cli) {
     adapter = cli;
}
SignInForm::~SignInForm()
{
    delete ui;
}

QtId SignInForm::get_qtid()
{

}

void SignInForm::set_qtid()
{

}

QString SignInForm::get_password()
{

}

void SignInForm::show_alert(QString)
{

}

void SignInForm::on_signInPushButton_clicked()
{

}



void SignInForm::on_registerPushButton_clicked()
{

}

