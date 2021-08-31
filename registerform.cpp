#include "registerform.h"
#include "ui_registerform.h"
#include "clientadapter.h"
#include <QMessageBox>
#include <QDebug>

RegisterForm::RegisterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this);
}

RegisterForm::~RegisterForm() { delete ui; }

void RegisterForm::set_adapter(ClientAdapter* cli) {
    adapter = cli;
}

QString RegisterForm::get_nickname() {

    return ui -> nickNameTextEdit ->text();
    //return ui ->text();
}

QString RegisterForm::get_password() {
    return ui -> passwordSetter ->text();
}

//确定事件点击
void RegisterForm::on_confirmPushButton_clicked() {
    qDebug() << "Clicked" << endl;
    if(ui ->nickNameTextEdit ->text().isEmpty()) {
        show_alert("昵称不能为空");
    } else if(!check_password()) {
        //do nothing!
    } else {
        //向服务器申请注册当前账号
        adapter->make_register(ui->nickNameTextEdit->text(),ui->passwordSetter->text());
        ui ->confirmPushButton -> setEnabled(false);
    }
}

//密码不符格式时，弹出警告阻塞
bool RegisterForm::check_password() {
    QString passwordOne = ui ->passwordSetter ->text();
    if(passwordOne.isEmpty() || ui ->passwordConfirm->text().isEmpty()) {
       show_alert("密码不能为空");
    }
    else if(passwordOne.size() < 4) {
        show_alert("密码长度小于4");
        return false;
    }
    else if(QString::compare(passwordOne,ui ->passwordConfirm->text()) != 0) {
        show_alert("两次输入密码不一致");
        return false;
    }
    return true;
}

void RegisterForm::show_alert(QString warningMsg) {
    int ret = QMessageBox::warning(this,"警告",warningMsg,QMessageBox::Yes);
    if(ret == QMessageBox::Yes) {
       //do nothing
    }
}

void RegisterForm::failed_msg(QString str) {
    show_alert(QString("注册失败%1").arg(str));
}

void RegisterForm::show_qtid(QtId id) {
    show_alert(QString("%1").arg(id));
}

