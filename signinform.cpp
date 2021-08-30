#include "signinform.h"
#include "ui_signinform.h"
#include "clientadapter.h"
#include <QMessageBox>

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

//当输入账号为空时 返回值为0
QtId SignInForm::get_qtid() {
    return ui ->qidTextEdit ->text().toInt();
}

//更改ui界面上的登录账号
void SignInForm::set_qtid(QtId id) {
    ui ->qidTextEdit ->setText(QString("%1").arg(id));
}

QString SignInForm::get_password() {
    return ui ->passwordTextEdit ->text();
}

void SignInForm::show_alert(QString warningMsg) {
    int ret = QMessageBox::warning(this,"警告",warningMsg,QMessageBox::Yes);
    if(ret == QMessageBox::Yes) {
       //do nothing
    }
}


void SignInForm::on_signInPushButton_clicked() {
     if(ui -> qidTextEdit ->text().isEmpty()) {
         show_alert("请输入账号");
     }
     else if(ui ->passwordTextEdit ->text().isEmpty()) {
         show_alert("密码不能为空");
     } else {
         //传给Adapter,请求服务器验证
         //qDebug() << "发送请求" << endl;
         adapter->sign_in(get_qtid(),get_password());
     }
}

void SignInForm::failed_sign(QString failedMsg) {
     show_alert(failedMsg);
}

void SignInForm::on_registerPushButton_clicked(){
    //需要跳转到注册界面
    adapter->open_register_form();
}

