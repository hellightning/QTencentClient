#include "registerform.h"
#include "ui_registerform.h"
#include "clientadapter.h"

RegisterForm::RegisterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this);
}

RegisterForm::~RegisterForm()
{
    delete ui;
}

QString RegisterForm::get_nickname()
{

}

QString RegisterForm::get_password()
{

}

void RegisterForm::on_confirmPushButton_clicked()
{

}

bool RegisterForm::check_password()
{

}

void RegisterForm::show_qtid(QtId)
{

}

