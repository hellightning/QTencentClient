#include "chatform.h"
#include "ui_chatform.h"
#include "clientadapter.h"

ChatForm::ChatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);
}

ChatForm::~ChatForm()
{
    delete ui;
}

void ChatForm::on_sendMessageButton_clicked()
{

}


void ChatForm::on_closeFormButton_clicked()
{

}

void ChatForm::init_list_widget(QList<Message>)
{

}

void ChatForm::update_list_widget(Message)
{

}

