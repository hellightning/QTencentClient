#include "signinform.h"
#include "ui_signinform.h"
#include "clientadapter.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsBlurEffect>
#include <QPixmap>
#include <QPainter>

SignInForm::SignInForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignInForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    auto shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(8);
    ui->MainFrame->setGraphicsEffect(shadow_effect);

    auto shadow_effect2 = new QGraphicsDropShadowEffect(this);
    shadow_effect2->setOffset(0, 0);
    shadow_effect2->setColor(Qt::gray);
    shadow_effect2->setBlurRadius(40);
    ui->Niwatari->setGraphicsEffect(shadow_effect2);
    //changeIcon(3);
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
    //TODO
    changeIcon(adapter ->qtid_to_nickname[id].mid(0,1).toInt());
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

//切换头像
void SignInForm::changeIcon(int iconId) {

    iconId %= 10;
    iconId += 10;
    iconId %= 10;

    QString imgPath = ":/Icons/icon/img" +QString::number(iconId + 1) + ".jpg";

    int myWidth = ui ->Niwatari ->width() - 6;
    int myHeight = ui ->Niwatari ->height();

    QPixmap originPath(imgPath);
    QPixmap roundCircle(myWidth,myHeight);
    roundCircle.fill(Qt::transparent);
    QPainter painter(&roundCircle);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0,0,myWidth,myHeight);    //绘制椭圆
    painter.setClipPath(path);
    painter.drawPixmap(0,0,myWidth,myHeight,originPath);

    ui->Niwatari->setPixmap(roundCircle);
}

void SignInForm::on_registerPushButton_clicked(){
    //需要跳转到注册界面
    adapter->open_register_form();
}

void SignInForm::on_CloseButton_clicked() {
    close();
}


void SignInForm::on_SmallButton_clicked() {
    setWindowState(Qt::WindowMinimized);
}

void SignInForm::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        isDrag = true;
        mouse_start_point = e->globalPos();
        window_topleft_point = frameGeometry().topLeft();
    }
}

void SignInForm::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        isDrag = false;
    }
}

void SignInForm::mouseMoveEvent(QMouseEvent *e)
{
    if (isDrag) {
        QPoint dist = e->globalPos() - mouse_start_point;
        this->move(window_topleft_point + dist);
    }
}

